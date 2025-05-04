#include "Accountant.h"
#include <algorithm>

Accountant::Accountant(StationMonitoringSystem *station_monitoring_system,
	AccountingSystem *accounting_system,
	ClientMonitoringSystem *client_monitoring_system,
	revenueType station_price)
		: station_price_(station_price),
		  station_monitoring_system_(station_monitoring_system),
		  client_monitoring_system_(client_monitoring_system),
		  accounting_system_(accounting_system) {}


void Accountant::publishEvent(const Event &event) {
	std::ranges::for_each(listeners_,[&event](EventListener *listener) {
		listener->updateOnEvent(event);
	});
}

void Accountant::updateOnEvent(const Event &event) {
	std::visit(*this, event);
}

void Accountant::addListener(EventListener *listener) {
	listeners_.push_back(listener);
}

void Accountant::operator()(const ErrorEvent &event) {}

void Accountant::operator()(const ClientArriveEvent &event) {}

void Accountant::operator()(const ClientAwaitEvent &event) {
	if (client_monitoring_system_->clientIsBoundToStation(event.ClientName)) {
		auto station = client_monitoring_system_->getClientStation(event.ClientName);
		station_monitoring_system_->stopUsage(station, event.CreateTime);
		auto usage_duration = station_monitoring_system_->getUsageDurationSinceLastStart(station, event.CreateTime);
		station_monitoring_system_->startUsage(station, event.CreateTime);
		accounting_system_->account(station, usage_duration, station_price_);
	}
}

void Accountant::operator()(const StationOccupyEvent &event) {
	if (client_monitoring_system_->clientIsBoundToStation(event.ClientName)) {
		auto station = client_monitoring_system_->getClientStation(event.ClientName);
		station_monitoring_system_->stopUsage(station, event.CreateTime);
		auto usage_duration = station_monitoring_system_->getUsageDurationSinceLastStart(station, event.CreateTime);
		station_monitoring_system_->startUsage(station, event.CreateTime);
		accounting_system_->account(station, usage_duration, station_price_);
	}
}

void Accountant::operator()(const ShutdownEvent &event) {
	auto client_list = client_monitoring_system_->getClientList();
	std::ranges::sort(client_list);
	auto account_on_shutdown = [&] (const std::string &client_name) {
		Event new_event = ClientLeaveEvent{event.CreateTime, 11, client_name};
		updateOnEvent(new_event);
	};
	std::ranges::for_each(client_list, account_on_shutdown);
}

void Accountant::operator()(const ClientLeaveEvent &event) {
	auto station = client_monitoring_system_->getClientStation(event.ClientName);
	station_monitoring_system_->stopUsage(station, event.CreateTime);
	auto usage_duration = station_monitoring_system_->getUsageDurationSinceLastStart(station, event.CreateTime);
	station_monitoring_system_->startUsage(station, event.CreateTime);
	accounting_system_->account(station, usage_duration, station_price_);
}
