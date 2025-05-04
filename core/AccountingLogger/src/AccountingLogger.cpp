#include "AccountingLogger.h"
#include <algorithm>

AccountingLogger::AccountingLogger(std::shared_ptr<Logger> logger,
	const AccountingSystem &accounting_system,
	const StationMonitoringSystem &station_monitoring_system)
		: logger_(std::move(logger)),
		  accounting_system_(accounting_system),
		  station_monitoring_system_(station_monitoring_system) {}

void AccountingLogger::updateOnEvent(const Event &event) {
	if (!std::holds_alternative<ShutdownEvent>(event))
		return;
	auto stationList = station_monitoring_system_.getStationList();
	using stationId = AccountingSystem::StationId;
	auto update = [&] (const stationId& station_id) {
		AccountingReportGenerator report_generator(accounting_system_, station_monitoring_system_, station_id);
		report_generator.updateOnEvent(event);
		auto report = report_generator.generateReport();
		auto& accounting_report = *static_cast<AccountingReport*>(report.get());
		AccountingLogMessage msg(accounting_report.ReportContent);
		logger_->log(msg);
	};
	std::ranges::for_each(stationList, update);
}

AccountingLogMessage::AccountingLogMessage(std::string message): message_(std::move(message)) {}

const char *AccountingLogMessage::toString() const {
	return message_.c_str();
}
