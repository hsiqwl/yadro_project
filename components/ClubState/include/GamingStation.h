#ifndef GAMING_STATION_H
#define GAMING_STATION_H

class GamingStation {
public:
	bool isAvailable() const;

	void startWorking();

   	void stopWorking();

private:
	bool available_ = true;
};

#endif //GAMING_STATION_H
