#ifndef PARSER_H
#define PARSER_H
#include <optional>
#include <variant>
#include <vector>
#include <regex>

struct DummyState {

};

struct NumStationsState {
	std::string num_stations;
};

struct WorkingTimeState {
	std::string open_time;
	std::string close_time;
};

struct PriceState {
	std::string price;
};

struct SpecialEventState {
	std::string event_time;
	std::string event_id;
	std::string client_name;
	std::string station_id;
};

struct EventState {
	std::string event_time;
	std::string event_id;
	std::string client_name;
};

using State = std::variant<DummyState, NumStationsState, WorkingTimeState, PriceState, SpecialEventState, EventState>;


class Parser {
public:
	Parser();

	bool parse(const std::string& input);

	bool contentEmpty() const;

	const State& getNextContent();

private:
	struct InternalParser {
		InternalParser(const std::string& input);
		std::optional<State> operator () (const DummyState& state) const;
		std::optional<State> operator () (const NumStationsState& state) const;
		std::optional<State> operator () (const WorkingTimeState& state) const;
		std::optional<State> operator () (const PriceState& state) const;
		std::optional<State> operator () (const SpecialEventState& state) const;
		std::optional<State> operator () (const EventState& state) const;
	private:
		const std::string& input_;
	};

	std::vector<State> state_history_;

	size_t content_ptr = 1;
};


inline Parser::InternalParser::InternalParser(const std::string &input)
	: input_(input){}

inline std::optional<State> Parser::InternalParser::operator()(const DummyState &) const {
	std::regex r("^\\d+$");
	std::sregex_iterator it(input_.begin(), input_.end(), r), end;
	if (it == end) return std::nullopt;
	return NumStationsState{it->str()};
}

inline std::optional<State> Parser::InternalParser::operator()(const NumStationsState &) const {
	std::string pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) ((?:[01]\\d|2[0-3]):[0-5]\\d)$";
	std::regex re(pattern);
	std::smatch match;
	if (std::regex_match(input_, match, re))
		return WorkingTimeState{match[1].str(), match[2].str()};
	return std::nullopt;
}

inline std::optional<State> Parser::InternalParser::operator()(const WorkingTimeState &) const {
	std::regex r("^\\d+$");
	std::sregex_iterator it(input_.begin(), input_.end(), r), end;
	if (it == end) return std::nullopt;
	return PriceState{it->str()};
}

inline std::optional<State> Parser::InternalParser::operator()(const PriceState &) const {
	std::string pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) (1|3|4) ([a-z0-9_-]+)$";
	std::string special_pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) 2 ([a-z0-9_-]+) (\\d+)$";
	std::regex eventRegex2(special_pattern), eventRegex(pattern);
	std::smatch match;
	if (std::regex_match(input_, match, eventRegex2))
		return SpecialEventState{match[1].str(), "2", match[2].str(), match[3].str()};
	if (std::regex_match(input_, match, eventRegex))
		return EventState{match[1].str(), match[2].str(), match[3].str()};
	return std::nullopt;
}

inline std::optional<State> Parser::InternalParser::operator()(const SpecialEventState &) const {
	std::string pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) (1|3|4) ([a-z0-9_-]+)$";
	std::string special_pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) 2 ([a-z0-9_-]+) (\\d+)$";
	std::regex eventRegex2(special_pattern), eventRegex(pattern);
	std::smatch match;
	if (std::regex_match(input_, match, eventRegex2))
		return SpecialEventState{match[1].str(), "2", match[2].str(), match[3].str()};
	if (std::regex_match(input_, match, eventRegex))
		return EventState{match[1].str(), match[2].str(), match[3].str()};
	return std::nullopt;
}

inline std::optional<State> Parser::InternalParser::operator()(const EventState &) const {
	std::string pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) (1|3|4) ([a-z0-9_-]+)$";
	std::string special_pattern = "^((?:[01]\\d|2[0-3]):[0-5]\\d) 2 ([a-z0-9_-]+) (\\d+)$";
	std::regex eventRegex2(special_pattern), eventRegex(pattern);
	std::smatch match;
	if (std::regex_match(input_, match, eventRegex2))
		return SpecialEventState{match[1].str(), "2", match[2].str(), match[3].str()};
	if (std::regex_match(input_, match, eventRegex))
		return EventState{match[1].str(), match[2].str(), match[3].str()};
	return std::nullopt;
}

#endif //PARSER_H
