#include "AccountingReportGenerator.h"

AccountingReportGenerator::AccountingReportGenerator(
	const AccountingSystem &accounting_system,
	const StationMonitoringSystem& monitoring_system,
	StationId station_id)
	: accounting_system_(accounting_system),
	  station_monitoring_system_(monitoring_system),
	  station_id_(station_id) {}


void AccountingReportGenerator::updateOnEvent(const Event &event) {
	std::visit(*this, event);
}

std::shared_ptr<Report> AccountingReportGenerator::generateReport() {
	return generated_;
}

void AccountingReportGenerator::operator()(const ErrorEvent &event) {}

void AccountingReportGenerator::operator()(const ClientArriveEvent &event) {}

void AccountingReportGenerator::operator()(const ClientAwaitEvent &event) {}

void AccountingReportGenerator::operator()(const ClientLeaveEvent &event) {}

void AccountingReportGenerator::operator()(const StationOccupyEvent &event) {}

void AccountingReportGenerator::operator()(const ShutdownEvent &event) {
	auto usageDuration = station_monitoring_system_.getUsageDuration(station_id_);
	auto revenue = accounting_system_.getRevenue(station_id_);
	generated_ = std::make_shared<AccountingReport>(station_id_, revenue, usageDuration);
}

