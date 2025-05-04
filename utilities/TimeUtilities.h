#ifndef TIMEUTILITIES_H
#define TIMEUTILITIES_H
#include <chrono>
#include <sstream>

namespace TimeUtilities {
	using Clock = std::chrono::system_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::minutes;
	using UsageDuration = std::chrono::hh_mm_ss<Duration>;

	inline bool operator < (const TimePoint& lhs, const TimePoint& rhs) {
		return lhs.time_since_epoch() < rhs.time_since_epoch();
	}

	inline TimePoint timePointFromString(const std::string &str) {
		size_t hours, minutes;
		char delimiter;
		std::istringstream ss(str);
		ss >> hours >> delimiter >> minutes;
		std::chrono::minutes duration = std::chrono::hours(hours) + std::chrono::minutes(minutes);
		return TimePoint(duration);
	}

	inline std::string timePointToString(TimePoint time_point) {
		auto since_epoch = time_point.time_since_epoch();
		auto pretty_time = UsageDuration(std::chrono::duration_cast<Duration>(since_epoch));
		auto hours = pretty_time.hours().count();
		auto minutes = pretty_time.minutes().count();
		std::string hoursString = ((hours < 10) ? "0" : "") + std::to_string(hours);
		std::string minutesString = ((minutes < 10) ? "0" : "") + std::to_string(minutes);
		return hoursString + ":" + minutesString;
	}
}

#endif //TIMEUTILITIES_H
