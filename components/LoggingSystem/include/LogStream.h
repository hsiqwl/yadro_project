#ifndef LOG_STREAM_H
#define LOG_STREAM_H
#include "LogMessage.h"

class LogStream {
public:
  	virtual void send(const LogMessage& msg) = 0;

	virtual ~LogStream() {}
};

#endif //LOG_STREAM_H
