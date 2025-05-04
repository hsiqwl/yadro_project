#include "FlatStationMonitoringSystem.h"
#include <cassert>
#include <numeric>

FlatStationMonitoringSystem::FlatStationMonitoringSystem(TimePoint open, TimePoint close, size_t num_stations)
	: StationMonitoringSystem(open, close), monitors_(num_stations) {}


UsageDuration FlatStationMonitoringSystem::getUsageDuration(StationId station_id) const {
	assert(station_id > 0 && "Invalid station id");
	return monitors_[station_id - 1].elapsedTime();
}

UsageDuration FlatStationMonitoringSystem::getUsageDurationSinceLastStart(StationId station_id, TimePoint time_point) const {
	assert(station_id > 0 && "Invalid station id");
	return monitors_[station_id - 1].elapsedTimeSinceLastStart(time_point);
}

void FlatStationMonitoringSystem::startUsage(StationId station_id, TimePoint time_point) {
	assert(station_id > 0 && "Invalid station id");
	monitors_[station_id - 1].startCounter(time_point);
}

void FlatStationMonitoringSystem::stopUsage(StationId station_id, TimePoint time_point) {
	assert(station_id > 0 && "Invalid station id");
	monitors_[station_id - 1].stopCounter(time_point);
}

void FlatStationMonitoringSystem::reset(StationId station_id) {
	assert(station_id > 0 && "Invalid station id");
	monitors_[station_id - 1] = GamingStationMonitor();
}

void FlatStationMonitoringSystem::reset() {
	std::ranges::fill(monitors_, GamingStationMonitor());
}

StationMonitoringSystem::StationList FlatStationMonitoringSystem::getStationList() const {
	std::vector<StationId> station_ids(monitors_.size());
	std::iota(station_ids.begin(), station_ids.end(), 1);
	return station_ids;
}
