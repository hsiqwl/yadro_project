#ifndef CLIENTQUEUEMANAGER_H
#define CLIENTQUEUEMANAGER_H
#include "ClubState.h"
#include "ClientMonitoringSystem.h"
#include "StationMonitoringSystem.h"
#include "EventPublisher.h"
#include "EventHandler.h"
#include <deque>

class ClientQueueManager final: public EventHandler,
                          public EventPublisher,
                          public EventListener
{
public:
	ClientQueueManager(
		ClubState* state,
		ClientMonitoringSystem* client_monitoring_system,
		StationMonitoringSystem* station_monitoring_system);

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


	ClubState* state_;

	ClientMonitoringSystem* client_monitoring_system_;

	StationMonitoringSystem* station_monitoring_system_;

	std::deque<std::string> client_queue_;

	std::vector<EventListener*> listeners_;
};


#endif //CLIENTQUEUEMANAGER_H
