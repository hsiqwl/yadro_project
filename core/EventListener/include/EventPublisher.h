#ifndef EVENTPUBLISHER_H
#define EVENTPUBLISHER_H
#include "EventListener.h"

class EventPublisher {
public:
	virtual ~EventPublisher() {}

    virtual void publishEvent(const Event &event) = 0;

    virtual void addListener(EventListener* listener) = 0;
};

#endif //EVENTPUBLISHER_H
