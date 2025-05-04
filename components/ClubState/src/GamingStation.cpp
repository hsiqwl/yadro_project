#include "GamingStation.h"

bool GamingStation::isAvailable() const {
	return available_;
}

void GamingStation::startWorking() {
	available_ = false;
}

void GamingStation::stopWorking() {
	available_ = true;
}