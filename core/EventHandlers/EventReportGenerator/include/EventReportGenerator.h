#ifndef EVENTREPORTER_H
#define EVENTREPORTER_H
#include "ReportGenerator.h"
#include "EventReport.h"
#include "EventListener.h"
#include "EventHandler.h"

class EventReportGenerator final : public EventHandler,
                                   public EventListener,
                                   public ReportGenerator
{
public:
	void operator () (const ClientArriveEvent& event) override;
	void operator () (const ClientAwaitEvent& event) override;
	void operator () (const ClientLeaveEvent& event) override;
	void operator () (const ErrorEvent& event) override;
	void operator () (const StationOccupyEvent& event) override;
	void operator () (const ShutdownEvent& event) override;

	void updateOnEvent(const Event &event) override;

	std::shared_ptr<Report> generateReport() override;

private:
	std::shared_ptr<Report> generated_;
};

#endif //EVENTREPORTER_H
