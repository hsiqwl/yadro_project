#ifndef ORCHESTRATOR_H
#define ORCHESTRATOR_H
#include "Accountant.h"
#include "AccountingLogger.h"
#include "EventLogger.h"
#include "ClientQueueManager.h"
#include "AccountingSystem.h"
#include "Logger.h"
#include "ClientMonitoringSystem.h"
#include "ClubState.h"
#include <memory>
#include "StationMonitoringSystem.h"

struct TimePointMessage : public LogMessage {
	TimePointMessage(TimePoint time_point);

	const char* toString() const override;
private:
	std::string message;
};

struct Orchestrator final {
	Orchestrator(size_t num_stations, TimePoint open_time, TimePoint close_time, unsigned price);

	std::shared_ptr<ClubState> state_;
	std::shared_ptr<ClientMonitoringSystem> client_monitoring_system_;
	std::shared_ptr<StationMonitoringSystem> station_monitoring_system_;
	std::shared_ptr<AccountingSystem> accounting_system_;
	std::shared_ptr<Logger> logger_;
	ClientQueueManager client_queue_manager_;
	Accountant accountant_;
	EventLogger event_logger_;
	AccountingLogger accounting_logger_;
};

#endif //ORCHESTRATOR_H
