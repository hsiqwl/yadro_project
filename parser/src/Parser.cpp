#include "Parser.h"

Parser::Parser() {
	state_history_.emplace_back(DummyState{});
}

bool Parser::contentEmpty() const {
	return content_ptr == state_history_.size();
}

const State &Parser::getNextContent() {
	return state_history_[content_ptr++];
}

bool Parser::parse(const std::string &input) {
	auto current_state = state_history_.back();
	auto internal = InternalParser(input);
	auto next_state = std::visit(internal, current_state);
	if (!next_state.has_value())
		return false;
	state_history_.push_back(next_state.value());
	return true;
}




