#ifndef FLATCLUBSTATE_H
#define FLATCLUBSTATE_H
#include "ClubState.h"
#include "GamingStation.h"
#include <vector>

class FlatClubState final : public ClubState {
public:
	FlatClubState(size_t num_stations);

	bool stationAvailable(StationId station_id) const override;

	void occupyStation(StationId station_id) override;

	void vacateStation(StationId station_id) override;

	StationId getVacantStation() const override;

	bool hasVacantStation() const override;

	size_t totalStations() const override;

private:
	std::vector<GamingStation> stations_;
};

#endif //FLATCLUBSTATE_H
