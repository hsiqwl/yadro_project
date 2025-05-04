#include "FlatClubState.h"
#include <cassert>
#include <algorithm>

FlatClubState::FlatClubState(size_t num_stations) : stations_(num_stations) {}

bool FlatClubState::stationAvailable(StationId station_id) const {
	assert(station_id > 0 && "station id is invalid");
	return stations_[station_id - 1].isAvailable();
}

void FlatClubState::occupyStation(StationId station_id) {
	assert(station_id > 0 && "station id is invalid");
	stations_[station_id - 1].startWorking();
}

void FlatClubState::vacateStation(StationId station_id) {
	assert(station_id > 0 && "station id is invalid");
	stations_[station_id - 1].stopWorking();
}

bool FlatClubState::hasVacantStation() const {
	return std::any_of(stations_.begin(), stations_.end(),[] (auto& station) {
		return station.isAvailable();
	});
}

ClubState::StationId FlatClubState::getVacantStation() const {
	auto vacant_station = std::find_if(stations_.begin(), stations_.end(), [] (auto& station) {
		return station.isAvailable();
	});
	auto station_id = std::distance(stations_.begin(), vacant_station);
	return static_cast<StationId>(station_id);
}

size_t FlatClubState::totalStations() const {
	return stations_.size();
}

