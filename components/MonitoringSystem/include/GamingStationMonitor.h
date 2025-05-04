#ifndef GAMING_STATION_MONITOR_H
#define GAMING_STATION_MONITOR_H
#include "TimeUtilities.h"

using namespace TimeUtilities;

class GamingStationMonitor final {
public:
	void startCounter(TimePoint start_time);

    void stopCounter(TimePoint stop_time);

	UsageDuration elapsedTimeSinceLastStart(TimePoint time_point) const;

    UsageDuration elapsedTime() const;

private:
	TimePoint last_startup_time_;

    Duration elapsed_time_ = Duration::zero();
};


#endif //GAMING_STATION_MONITOR_H
