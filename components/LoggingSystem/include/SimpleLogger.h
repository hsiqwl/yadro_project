#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H
#include "Logger.h"
#include <memory>

class SimpleLogger final: public Logger {
public:
	SimpleLogger(std::shared_ptr<LogStream> stream);

	void rebind(std::shared_ptr<LogStream> new_stream) override;

	void log(const LogMessage& msg) override;

private:
	std::shared_ptr<LogStream> stream_;
};

#endif //SIMPLELOGGER_H
