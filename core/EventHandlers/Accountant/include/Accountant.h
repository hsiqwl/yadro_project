#ifndef ACCOUNTER_H
#define ACCOUNTER_H
#include "ClientMonitoringSystem.h"
#include "StationMonitoringSystem.h"
#include "AccountingSystem.h"
#include "EventHandler.h"
#include "EventPublisher.h"

class Accountant final: public EventHandler,
                        public EventPublisher,
                        public EventListener
{
public:
	using revenueType = AccountingSystem::revenueType;

	Accountant(
		StationMonitoringSystem *station_monitoring_system,
		AccountingSystem *accounting_system,
		ClientMonitoringSystem* client_monitoring_system,
		revenueType stationPrice);

	void operator () (const ClientArriveEvent& event) override;
	void operator () (const ClientAwaitEvent& event) override;
	void operator () (const ClientLeaveEvent& event) override;
	void operator () (const ErrorEvent& event) override;
	void operator () (const StationOccupyEvent& event) override;
	void operator () (const ShutdownEvent& event) override;

	void publishEvent(const Event &event) override;
	void addListener(EventListener* listener) override;

	void updateOnEvent(const Event &event) override;

private:
	using StationId = StationMonitoringSystem::StationId;

	revenueType station_price_;

	std::vector<EventListener*> listeners_;

	StationMonitoringSystem *station_monitoring_system_;

	ClientMonitoringSystem *client_monitoring_system_;

	AccountingSystem *accounting_system_;
};

#endif //ACCOUNTER_H
