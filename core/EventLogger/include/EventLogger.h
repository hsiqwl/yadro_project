#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H
#include "EventListener.h"
#include "EventReportGenerator.h"
#include "Logger.h"

class EventLogMessage : public LogMessage {
public:
	EventLogMessage(std::string message);

	const char* toString() const override;

private:
	std::string message_;
};

class EventLogger: public EventListener  {
public:
	EventLogger(std::shared_ptr<Logger> logger);

	void updateOnEvent(const Event &event) override;
private:
	std::shared_ptr<Logger> logger_;
};

#endif //EVENTLOGGER_H
