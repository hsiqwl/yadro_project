#ifndef CLIENTMONITORINGSYSTEM_H
#define CLIENTMONITORINGSYSTEM_H
#include <string>
#include <vector>

class ClientMonitoringSystem {
public:
	using ClientList = std::vector<std::string>;

  	using StationId = unsigned;

	virtual void checkClientIn(std::string client_name) = 0;

	virtual void checkClientOut(const std::string& client_name) = 0;

	virtual bool clientIsBoundToStation(const std::string& client_name) const = 0;

  	virtual void bindClientToStation(std::string client_name, StationId station_id) = 0;

    virtual void unbindClientFromStation(const std::string& client_name) = 0;

    virtual bool clientHasCheckedIn(const std::string& client_name) const = 0;

    virtual StationId getClientStation(const std::string& client_name) const = 0;

	virtual ClientList getClientList() const = 0;

	virtual ~ClientMonitoringSystem() {}
};

#endif //CLIENTMONITORINGSYSTEM_H
