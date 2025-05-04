#ifndef CONSOLE_LOG_STREAM_H
#define CONSOLE_LOG_STREAM_H
#include "LogStream.h"

class ConsoleLogStream final: public LogStream {
public:
	void send(const LogMessage& msg) override;
};


#endif //CONSOLE_LOG_STREAM_H
