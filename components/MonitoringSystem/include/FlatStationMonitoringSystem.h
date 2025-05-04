#ifndef FLATSTATIONMONITORINGSYSTEM_H
#define FLATSTATIONMONITORINGSYSTEM_H
#include "GamingStationMonitor.h"
#include "StationMonitoringSystem.h"
#include <vector>

class FlatStationMonitoringSystem final : public StationMonitoringSystem {
public:
  	FlatStationMonitoringSystem(TimePoint open, TimePoint close, size_t num_stations);

	void startUsage(StationId station_id, TimePoint time_point) override;

	void stopUsage(StationId station_id, TimePoint time_point) override;

	UsageDuration getUsageDuration(StationId station_id) const override;

	UsageDuration getUsageDurationSinceLastStart(StationId station_id, TimePoint time_point) const override;

	StationList getStationList() const override;

	void reset(StationId station_id) override;

	void reset() override;

private:
	std::vector<GamingStationMonitor> monitors_;
};

#endif //FLATSTATIONMONITORINGSYSTEM_H
