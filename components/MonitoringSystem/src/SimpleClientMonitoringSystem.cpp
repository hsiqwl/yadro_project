#include "SimpleClientMonitoringSystem.h"
#include <iostream>

bool SimpleClientMonitoringSystem::clientHasCheckedIn(const std::string &client_name) const {
	return checked_in_clients_.contains(client_name);
}

ClientMonitoringSystem::StationId SimpleClientMonitoringSystem::getClientStation(const std::string &client_name) const {
	return client_station_map_.at(client_name);
}

void SimpleClientMonitoringSystem::bindClientToStation(std::string client_name, StationId station_id) {
	client_station_map_.emplace(std::move(client_name), station_id);
}

void SimpleClientMonitoringSystem::unbindClientFromStation(const std::string &client_name) {
	client_station_map_.erase(client_name);
}

void SimpleClientMonitoringSystem::checkClientIn(std::string client_name) {
	checked_in_clients_.emplace(std::move(client_name));
}

void SimpleClientMonitoringSystem::checkClientOut(const std::string &client_name) {
	checked_in_clients_.erase(client_name);
}

bool SimpleClientMonitoringSystem::clientIsBoundToStation(const std::string &client_name) const {
	return client_station_map_.contains(client_name);
}

ClientMonitoringSystem::ClientList SimpleClientMonitoringSystem::getClientList() const {
	return {checked_in_clients_.begin(), checked_in_clients_.end()};
}

