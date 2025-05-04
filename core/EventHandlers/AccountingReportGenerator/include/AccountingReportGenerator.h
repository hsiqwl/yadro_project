#ifndef ACCOUNTINGREPORTGENERATOR_H
#define ACCOUNTINGREPORTGENERATOR_H
#include "ReportGenerator.h"
#include "AccountingReport.h"
#include "EventListener.h"
#include "EventHandler.h"
#include "AccountingSystem.h"
#include "StationMonitoringSystem.h"

class AccountingReportGenerator final : public EventHandler,
										public EventListener,
										public ReportGenerator {
public:
	using StationId = AccountingSystem::StationId;
	AccountingReportGenerator(const AccountingSystem& accounting_system,
							  const StationMonitoringSystem& monitoring_system,
							  StationId station_id);

	void operator () (const ClientArriveEvent& event) override;
	void operator () (const ClientAwaitEvent& event) override;
	void operator () (const ClientLeaveEvent& event) override;
	void operator () (const ErrorEvent& event) override;
	void operator () (const StationOccupyEvent& event) override;
	void operator () (const ShutdownEvent& event) override;

	void updateOnEvent(const Event &event) override;

	std::shared_ptr<Report> generateReport() override;
private:
	const AccountingSystem& accounting_system_;

	const StationMonitoringSystem& station_monitoring_system_;

	StationId station_id_;

	std::shared_ptr<Report> generated_;
};

#endif //ACCOUNTINGREPORTGENERATOR_H
