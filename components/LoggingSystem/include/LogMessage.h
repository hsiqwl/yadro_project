#ifndef LOG_MSG_H
#define LOG_MSG_H

class LogMessage {
public:
    virtual const char* toString() const = 0;

    virtual ~LogMessage() = default;
};

#endif //LOG_MSG_H
