#ifndef FLATACCOUNTINGSYSTEM_H
#define FLATACCOUNTINGSYSTEM_H
#include "AccountingSystem.h"
#include <vector>

class FlatAccountingSystem final: public AccountingSystem {
public:
  	FlatAccountingSystem(size_t num_stations);

  	void account(StationId station_id, UsageDuration use_duration, revenueType price) override;

	void reset(StationId station_id) override;

	void reset() override;

	revenueType getRevenue(StationId station_id) const override;

private:
	std::vector<revenueType> revenue_;
};

#endif //FLATACCOUNTINGSYSTEM_H
