#ifndef STATIONMONITORINGSYSTEM_H
#define STATIONMONITORINGSYSTEM_H
#include "TimeUtilities.h"
#include <vector>
using namespace TimeUtilities;

class StationMonitoringSystem {
public:
	StationMonitoringSystem(TimePoint open, TimePoint close) : open_(open), close_(close) {}

  	using StationId = unsigned;

	using StationList = std::vector<StationId>;

    virtual void startUsage(StationId station_id, TimePoint time_point) = 0;

    virtual void stopUsage(StationId station_id, TimePoint time_point) = 0;

    virtual UsageDuration getUsageDuration(StationId station_id) const = 0;

	virtual UsageDuration getUsageDurationSinceLastStart(StationId station_id, TimePoint time_point) const = 0;

	virtual StationList getStationList() const = 0;

	virtual void reset(StationId station_id) = 0;

    virtual void reset() = 0;

	TimePoint getOpenTime() const {
		return open_;
	}

	TimePoint getCloseTime() const {
		return close_;
	}

	virtual ~StationMonitoringSystem() = default;

private:
	TimePoint open_;
	TimePoint close_;
};

#endif //STATIONMONITORINGSYSTEM_H
