#ifndef ACCOUNTINGSYSTEM_H
#define ACCOUNTINGSYSTEM_H
#include "TimeUtilities.h"

using namespace TimeUtilities;

class AccountingSystem {
public:
  	using StationId = unsigned;

	using revenueType = unsigned;

  	virtual void account(StationId station_id, UsageDuration use_duration, revenueType price) = 0;

	virtual void reset(StationId station_id) = 0;

	virtual void reset() = 0;

	virtual revenueType getRevenue(StationId station_id) const = 0;

	virtual ~AccountingSystem() {}
};

#endif //ACCOUNTINGSYSTEM_H
