#include "GamingStationMonitor.h"

void GamingStationMonitor::startCounter(TimePoint start_time) {
	last_startup_time_ = start_time;
}

void GamingStationMonitor::stopCounter(TimePoint stop_time) {
	elapsed_time_ += std::chrono::duration_cast<Duration>(stop_time - last_startup_time_);
}

UsageDuration GamingStationMonitor::elapsedTime() const {
	return UsageDuration{elapsed_time_};
}

UsageDuration GamingStationMonitor::elapsedTimeSinceLastStart(TimePoint time_point) const {
	return UsageDuration{std::chrono::duration_cast<Duration>(time_point - last_startup_time_)};
}
