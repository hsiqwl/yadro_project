#ifndef ACCOUNTINGLOGGER_H
#define ACCOUNTINGLOGGER_H
#include "EventListener.h"
#include "AccountingReportGenerator.h"
#include "Logger.h"

class AccountingLogMessage final: public LogMessage {
public:
	AccountingLogMessage(std::string message);

	const char* toString() const override;
private:
	std::string message_;
};

class AccountingLogger : public EventListener {
public:
	AccountingLogger(std::shared_ptr<Logger> logger,
		const AccountingSystem& accounting_system,
		const StationMonitoringSystem& station_monitoring_system);

	void updateOnEvent(const Event &event) override;
private:
	std::shared_ptr<Logger> logger_;

	const AccountingSystem& accounting_system_;

	const StationMonitoringSystem& station_monitoring_system_;
};

#endif //ACCOUNTINGLOGGER_H
