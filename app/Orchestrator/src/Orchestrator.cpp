#include "Orchestrator.h"
#include "FlatClubState.h"
#include "FlatAccountingSystem.h"
#include "FlatStationMonitoringSystem.h"
#include "SimpleClientMonitoringSystem.h"
#include "SimpleLogger.h"
#include "ConsoleLogStream.h"

Orchestrator::Orchestrator(size_t num_stations, TimePoint open_time, TimePoint close_time, unsigned price)
	: state_(new FlatClubState(num_stations)),
	  client_monitoring_system_(new SimpleClientMonitoringSystem()),
	  station_monitoring_system_(new FlatStationMonitoringSystem(open_time, close_time, num_stations)),
	  accounting_system_(new FlatAccountingSystem(num_stations)),
	  logger_(new SimpleLogger(std::make_shared<ConsoleLogStream>())),
	  client_queue_manager_(state_.get(), client_monitoring_system_.get(), station_monitoring_system_.get()),
	  accountant_(station_monitoring_system_.get(), accounting_system_.get(), client_monitoring_system_.get(), price),
	  event_logger_(logger_),
	  accounting_logger_(logger_, *accounting_system_, *station_monitoring_system_)
{
	client_queue_manager_.addListener(&event_logger_);
}

TimePointMessage::TimePointMessage(TimePoint time_point): message(timePointToString(time_point)) {}

const char *TimePointMessage::toString() const {
	return message.c_str();
}

