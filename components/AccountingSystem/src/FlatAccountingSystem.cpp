#include "FlatAccountingSystem.h"
#include <cassert>

FlatAccountingSystem::FlatAccountingSystem(size_t num_stations) : revenue_(num_stations) {}

void FlatAccountingSystem::account(StationId station_id, UsageDuration use_duration, revenueType price) {
	assert(station_id > 0 && "invalid station id");
	auto hours = use_duration.hours().count() + (use_duration.minutes().count() > 0);
	revenue_[station_id - 1] += hours * price;
}

void FlatAccountingSystem::reset(StationId station_id) {
	assert(station_id > 0 && "invalid station id");
	revenue_[station_id - 1] = 0.0f;
}

AccountingSystem::revenueType FlatAccountingSystem::getRevenue(StationId station_id) const {
	assert(station_id > 0 && "invalid station id");
	return revenue_[station_id - 1];
}

void FlatAccountingSystem::reset() {
	std::ranges::fill(revenue_, 0.0f);
}
