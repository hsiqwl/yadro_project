#include "SimpleLogger.h"

SimpleLogger::SimpleLogger(std::shared_ptr<LogStream> stream)
	: stream_(std::move(stream)) {}

void SimpleLogger::rebind(std::shared_ptr<LogStream> new_stream) {
	stream_ = std::move(new_stream);
}

void SimpleLogger::log(const LogMessage &msg) {
	stream_->send(msg);
}
