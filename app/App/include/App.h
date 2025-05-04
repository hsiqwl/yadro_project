#ifndef APP_H
#define APP_H
#include <vector>
#include "Parser.h"
#include "Events.h"
#include <cassert>


class App final {
public:
	App(const char* filename);

	void run();

private:
	struct Proxy {
		size_t num_stations;
		TimePoint open_time;
		TimePoint close_time;
		unsigned price;
		std::vector<Event> events_;
	};


	struct EventBuilder {
		EventBuilder(Proxy& proxy);

		void operator () (const DummyState&);
		void operator () (const NumStationsState&);
		void operator () (const WorkingTimeState&);
		void operator () (const PriceState&);
		void operator () (const EventState&);
		void operator () (const SpecialEventState&);
	private:
		Proxy& proxy_ref;
	};

	static void invokeFileChecks(const char* filename);

	Proxy proxy_;
};

inline App::EventBuilder::EventBuilder(Proxy &proxy): proxy_ref(proxy) {}


inline void App::EventBuilder::operator()(const DummyState &) {
	assert(false && "Must not reach this function while building events");
}

inline void App::EventBuilder::operator()(const NumStationsState &state) {
	proxy_ref.num_stations = std::stoi(state.num_stations);
}

inline void App::EventBuilder::operator()(const WorkingTimeState &state) {
	proxy_ref.open_time = timePointFromString(state.open_time);
	proxy_ref.close_time = timePointFromString(state.close_time);
}

inline void App::EventBuilder::operator()(const PriceState &state) {
	proxy_ref.price = std::stoi(state.price);
}

inline void App::EventBuilder::operator()(const EventState &state) {
	auto event_id = std::stoi(state.event_id);
	auto event_time = timePointFromString(state.event_time);
	switch (event_id) {
		case 1: {
			proxy_ref.events_.emplace_back(
				ClientArriveEvent{event_time, state.client_name}
				);
			break;
		}
		case 3: {
			proxy_ref.events_.emplace_back(
				ClientAwaitEvent{event_time, state.client_name}
				);
			break;
		}
		case 4: {
			proxy_ref.events_.emplace_back(
				ClientLeaveEvent{event_time, 4, state.client_name}
				);
			break;
		}
		default: {
			assert(false && "Unknown event id");
		}
	}
}

inline void App::EventBuilder::operator()(const SpecialEventState &state) {
	unsigned event_id = std::stoi(state.event_id);
	auto event_time = timePointFromString(state.event_time);
	unsigned station_id = std::stoi(state.station_id);
	proxy_ref.events_.emplace_back(StationOccupyEvent{event_time, event_id, state.client_name, station_id});
}
#endif //APP_H
