#include "ConsoleLogStream.h"
#include <iostream>

void ConsoleLogStream::send(const LogMessage &msg) {
	std::cout << msg.toString() << "\n";
}
