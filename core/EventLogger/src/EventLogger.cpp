#include "EventLogger.h"

EventLogger::EventLogger(std::shared_ptr<Logger> logger)
	: logger_(std::move(logger)) {}

void EventLogger::updateOnEvent(const Event &event) {
	EventReportGenerator generator;
	generator.updateOnEvent(event);
	auto report = generator.generateReport();
	if (report == nullptr) return;
	auto& event_report = *static_cast<EventReport*>(report.get());
	EventLogMessage msg(event_report.ReportContent);
	logger_->log(msg);
}

const char *EventLogMessage::toString() const {
	return message_.c_str();
}

EventLogMessage::EventLogMessage(std::string message): message_(std::move(message)) {}

