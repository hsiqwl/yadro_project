#ifndef EVENTREPORT_H
#define EVENTREPORT_H
#include "Report.h"
#include "TimeUtilities.h"
#include <string>

using namespace TimeUtilities;

class EventReport final : public Report {
public:
	using EventId = unsigned;

	EventReport(EventId event_id, TimePoint time_point, std::string payload);

	const std::string ReportContent;
private:
	static std::string eventIdToString(EventId event_id);
};

#endif //EVENTREPORT_H
