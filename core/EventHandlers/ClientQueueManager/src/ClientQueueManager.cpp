#include "ClientQueueManager.h"
#include <algorithm>
#include <iostream>

ClientQueueManager::ClientQueueManager(
	ClubState *state,
	ClientMonitoringSystem *client_monitoring_system,
	StationMonitoringSystem *station_monitoring_system)
	: state_(state),
	  client_monitoring_system_(client_monitoring_system),
	  station_monitoring_system_(station_monitoring_system) {}

void ClientQueueManager::publishEvent(const Event &event) {
	std::ranges::for_each(listeners_,[&event](EventListener *listener) {
		listener->updateOnEvent(event);
	});
}

void ClientQueueManager::addListener(EventListener *listener) {
	listeners_.push_back(listener);
}

void ClientQueueManager::updateOnEvent(const Event &event) {
	std::visit(*this, event);
}

void ClientQueueManager::operator()(const ErrorEvent &event) {}

void ClientQueueManager::operator()(const ClientAwaitEvent &event) {
	if (!client_monitoring_system_->clientHasCheckedIn(event.ClientName))
		publishEvent(ErrorEvent{event.CreateTime, "ClientUnknown"});
	else if (state_->hasVacantStation())
		publishEvent(ErrorEvent {event.CreateTime, "ICanWaitNoLonger!"});\
	else if (client_queue_.size() == state_->totalStations()) {
		client_monitoring_system_->checkClientOut(event.ClientName);
		Event new_event = ClientLeaveEvent{event.CreateTime, 11, event.ClientName};
		publishEvent(new_event);
		updateOnEvent(new_event);
	} else if (client_monitoring_system_->clientIsBoundToStation(event.ClientName)) {
		auto station = client_monitoring_system_->getClientStation(event.ClientName);
		client_monitoring_system_->unbindClientFromStation(event.ClientName);
		station_monitoring_system_->stopUsage(station, event.CreateTime);
		if (!client_queue_.empty()) {
			Event new_event = StationOccupyEvent{event.CreateTime, 12,
				client_queue_.front(), station};
			client_queue_.pop_front();
			publishEvent(new_event);
			updateOnEvent(new_event);
		}
	}
	client_queue_.push_back(event.ClientName);
}

void ClientQueueManager::operator()(const ClientLeaveEvent &event) {
	if (!client_monitoring_system_->clientHasCheckedIn(event.ClientName)) {
		publishEvent(ErrorEvent{event.CreateTime, "ClientUnknown"});
		return;
	}
	if (client_monitoring_system_->clientIsBoundToStation(event.ClientName)) {
		auto station = client_monitoring_system_->getClientStation(event.ClientName);
		client_monitoring_system_->unbindClientFromStation(event.ClientName);
		station_monitoring_system_->stopUsage(station, event.CreateTime);
		state_->vacateStation(station);
		if (!client_queue_.empty()) {
			Event new_event = StationOccupyEvent{event.CreateTime, 12,
				client_queue_.front(), station};
			client_queue_.pop_front();
			publishEvent(new_event);
			updateOnEvent(new_event);
		}
	}
	client_monitoring_system_->checkClientOut(event.ClientName);
}

void ClientQueueManager::operator()(const ClientArriveEvent &event) {
	if (event.CreateTime < station_monitoring_system_->getOpenTime())
		publishEvent(ErrorEvent {event.CreateTime, "NotOpenYet"});
	else if (client_monitoring_system_->clientHasCheckedIn(event.ClientName))
		publishEvent(ErrorEvent {event.CreateTime, "YouShallNotPass"});
	else
		client_monitoring_system_->checkClientIn(event.ClientName);
}

void ClientQueueManager::operator()(const StationOccupyEvent &event) {
	if (!client_monitoring_system_->clientHasCheckedIn(event.ClientName))
		publishEvent(ErrorEvent {event.CreateTime, "ClientUnknown"});
	else if (!state_->stationAvailable(event.StationId))
		publishEvent(ErrorEvent {event.CreateTime, "PlaceIsBusy"});
	else {
		if (client_monitoring_system_->clientIsBoundToStation(event.ClientName)) {
			auto station = client_monitoring_system_->getClientStation(
				event.ClientName);
			station_monitoring_system_->stopUsage(station, event.CreateTime);
			client_monitoring_system_->unbindClientFromStation(event.ClientName);
			state_->vacateStation(station);
		}
		station_monitoring_system_->startUsage(event.StationId, event.CreateTime);
		client_monitoring_system_->bindClientToStation(event.ClientName, event.StationId);
		state_->occupyStation(event.StationId);
		client_queue_.erase(std::ranges::find(client_queue_, event.ClientName), client_queue_.end());
	}
}

void ClientQueueManager::operator()(const ShutdownEvent &event) {
	auto client_list = client_monitoring_system_->getClientList();
	std::ranges::sort(client_list);
	auto client_leave = [&] (const std::string &client_name) {
		Event new_event = ClientLeaveEvent{event.CreateTime, 11, client_name};
		publishEvent(new_event);
		updateOnEvent(new_event);
	};
	std::ranges::for_each(client_list, client_leave);
}