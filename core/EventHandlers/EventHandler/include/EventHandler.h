#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H
#include "Events.h"

class EventHandler {
public:
	virtual void operator () (const ClientArriveEvent& event) = 0;
	virtual void operator () (const ClientAwaitEvent& event) = 0;
	virtual void operator () (const ClientLeaveEvent& event) = 0;
	virtual void operator () (const ErrorEvent& event) = 0;
	virtual void operator () (const StationOccupyEvent& event) = 0;
	virtual void operator () (const ShutdownEvent& event) = 0;

    virtual ~EventHandler() = default;
};


#endif //EVENTPROCESSOR_H
