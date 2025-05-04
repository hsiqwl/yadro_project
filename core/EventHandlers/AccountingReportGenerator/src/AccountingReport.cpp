#include "AccountingReport.h"

std::string AccountingReport::revenueToString(revenueType revenue) {
	return std::to_string(revenue);
}

std::string AccountingReport::stationIdToString(StationId stationId) {
	return std::to_string(stationId);
}

std::string AccountingReport::usageDurationToString(UsageDuration duration) {
	auto hours = duration.hours().count();
	auto minutes = duration.minutes().count();
	std::string hoursString = std::to_string(hours);
	std::string minutesString = std::to_string(minutes);
	if (hours < 10) hoursString = "0" + hoursString;
	if (minutes < 10) minutesString = "0" + minutesString;
	return hoursString + ":" + minutesString;
}

AccountingReport::AccountingReport(StationId stationId, revenueType revenue, UsageDuration duration)
	: ReportContent(stationIdToString(stationId) + " "
		+ revenueToString(revenue) + " "
		+ usageDurationToString(duration)) {}
