#include <iostream>
#include "App.h"
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}

	try {
		App app(argv[1]);
		app.run();
	} catch (const std::exception &e) {
		std::cerr << e.what() << "\n";
	}
}