#include "EventReportGenerator.h"

#include <memory>

void EventReportGenerator::updateOnEvent(const Event &event) {
	std::visit(*this, event);
}

std::shared_ptr<Report> EventReportGenerator::generateReport() {
	return generated_;
}

void EventReportGenerator::operator()(const ErrorEvent &event) {
	generated_ = std::make_shared<EventReport>(
		event.EventId, event.CreateTime, event.ErrorMessage);
}

void EventReportGenerator::operator()(const ShutdownEvent &event) {}

void EventReportGenerator::operator()(const ClientArriveEvent &event) {
	generated_ = std::make_shared<EventReport>(
		event.EventId, event.CreateTime, event.ClientName);
}

void EventReportGenerator::operator()(const ClientAwaitEvent &event) {
	generated_ = std::make_shared<EventReport>(
		event.EventId, event.CreateTime, event.ClientName);
}

void EventReportGenerator::operator()(const ClientLeaveEvent &event) {
	generated_ = std::make_shared<EventReport>(
		event.EventId, event.CreateTime, event.ClientName);
}

void EventReportGenerator::operator()(const StationOccupyEvent &event) {
	generated_ = std::make_shared<EventReport>(
		event.EventId, event.CreateTime, event.ClientName + " " + std::to_string(event.StationId));
}




