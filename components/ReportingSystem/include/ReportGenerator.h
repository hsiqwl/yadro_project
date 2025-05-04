#ifndef REPORTER_H
#define REPORTER_H
#include "Report.h"
#include <memory>

//base reporter class for future inheritance hierarchy
class ReportGenerator {
public:
    virtual std::shared_ptr<Report> generateReport() = 0;

    virtual ~ReportGenerator() = default;
};

#endif //REPORTER_H
