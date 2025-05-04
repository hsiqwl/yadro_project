#include "EventReport.h"
#include <sstream>

EventReport::EventReport(EventId event_id, TimePoint time_point, std::string payload)
	:ReportContent(timePointToString(time_point) +
		" " + eventIdToString(event_id) +
		" " + std::move(payload)) {}


std::string EventReport::eventIdToString(EventId event_id) {
	return std::to_string(event_id);
}
