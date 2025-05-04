#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H
#include "LogStream.h"
#include <memory>

class Logger {
public:
    virtual void rebind(std::shared_ptr<LogStream>) = 0;

	virtual void log(const LogMessage&) = 0;

    virtual ~Logger() = default;
};

#endif //LOG_SYSTEM_H
