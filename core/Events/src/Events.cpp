#include "Events.h"

ClientArriveEvent::ClientArriveEvent(TimePoint time_point, std::string client_name)
	: BaseEvent(time_point, 1), ClientName(std::move(client_name)) {}

ClientAwaitEvent::ClientAwaitEvent(TimePoint time_point, std::string client_name)
	: BaseEvent(time_point, 3), ClientName(std::move(client_name)) {}

ClientLeaveEvent::ClientLeaveEvent(TimePoint time_point, unsigned event_id, std::string client_name)
	: BaseEvent(time_point, event_id), ClientName(std::move(client_name)) {}

ErrorEvent::ErrorEvent(TimePoint time_point, std::string error_message)
	: BaseEvent(time_point, 13), ErrorMessage(std::move(error_message)) {}

StationOccupyEvent::StationOccupyEvent(TimePoint time_point, unsigned event_id, std::string client_name, stationId station_id)
	: BaseEvent(time_point, event_id), ClientName(std::move(client_name)), StationId(station_id) {}

ShutdownEvent::ShutdownEvent(TimePoint time_point)
	: BaseEvent(time_point, 0) {}
