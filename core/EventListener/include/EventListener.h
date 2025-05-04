#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#include "Events.h"

class EventListener {
public:
  	virtual void updateOnEvent(const Event &event) = 0;

	virtual ~EventListener() {}
};

#endif //EVENTLISTENER_H
