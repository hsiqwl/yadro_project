#ifndef CLUB_STATE_H
#define CLUB_STATE_H
#include <cstddef>

class ClubState {
public:
  	using StationId = unsigned;

    virtual bool stationAvailable(StationId station_id) const = 0;

    virtual void occupyStation(StationId station_id) = 0;

    virtual void vacateStation(StationId station_id) = 0;

	virtual StationId getVacantStation() const = 0;

	virtual bool hasVacantStation() const = 0;

	virtual size_t totalStations() const = 0;

	virtual ~ClubState() {}
};

#endif //CLUB_STATE_H
