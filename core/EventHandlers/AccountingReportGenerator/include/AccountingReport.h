#ifndef ACCOUNTINGREPORT_H
#define ACCOUNTINGREPORT_H
#include "Report.h"
#include "TimeUtilities.h"

using namespace TimeUtilities;

class AccountingReport final : public Report {
public:
	using StationId = unsigned;

	using revenueType = unsigned;

	AccountingReport(StationId stationId, revenueType revenue, UsageDuration duration);

	const std::string ReportContent;
private:
	static std::string stationIdToString(StationId stationId);

	static std::string usageDurationToString(UsageDuration duration);

	static std::string revenueToString(revenueType revenue);
};

#endif //ACCOUNTINGREPORT_H
