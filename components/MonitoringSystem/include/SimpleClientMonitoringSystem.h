#ifndef SIMPLECLIENTMONITORINGSYSTEM_H
#define SIMPLECLIENTMONITORINGSYSTEM_H
#include "ClientMonitoringSystem.h"
#include <unordered_map>
#include <unordered_set>

class SimpleClientMonitoringSystem final: public ClientMonitoringSystem {
public:
	void checkClientIn(std::string client_name) override;

	void checkClientOut(const std::string& client_name) override;

	void bindClientToStation(std::string client_name, StationId station_id) override;

	void unbindClientFromStation(const std::string& client_name) override;

	bool clientHasCheckedIn(const std::string& client_name) const override;

	bool clientIsBoundToStation(const std::string& client_name) const override;

	StationId getClientStation(const std::string& client_name) const override;

	ClientList getClientList() const override;
private:
	std::unordered_set<std::string> checked_in_clients_;

	std::unordered_map<std::string, StationId> client_station_map_;
};

#endif //SIMPLECLIENTMONITORINGSYSTEM_H
