#ifndef EVENTS_H
#define EVENTS_H
#include "TimeUtilities.h"
#include <variant>
#include <string>

using namespace TimeUtilities;

struct BaseEvent {
	const TimePoint CreateTime;

	const unsigned EventId;
};

struct ClientArriveEvent final : BaseEvent {
	ClientArriveEvent(TimePoint time_point, std::string client_name);

	const std::string ClientName;
};

struct ClientAwaitEvent final : BaseEvent {
	ClientAwaitEvent(TimePoint time_point, std::string client_name);

	const std::string ClientName;
};

struct ClientLeaveEvent final : BaseEvent {
	ClientLeaveEvent(TimePoint time_point, unsigned event_id, std::string client_name);

	const std::string ClientName;
};

struct ErrorEvent final: BaseEvent {
	ErrorEvent(TimePoint time_point, std::string error_message);

	const std::string ErrorMessage;
};

struct StationOccupyEvent final: BaseEvent {
	using stationId = unsigned;

	StationOccupyEvent(TimePoint time_point, unsigned event_id, std::string client_name, stationId station_id);

	const std::string ClientName;

	const stationId StationId;
};

struct ShutdownEvent final: BaseEvent {
	ShutdownEvent(TimePoint time_point);
};

using Event = std::variant<
              ClientArriveEvent,
      		  ClientAwaitEvent,
			  ClientLeaveEvent,
     		  ErrorEvent,
      		  StationOccupyEvent,
			  ShutdownEvent>;

#endif //EVENTS_H
