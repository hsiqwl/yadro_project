#include "App.h"

#include <complex>

#include "AppException.h"
#include <fstream>
#include <filesystem>
#include <Orchestrator.h>
namespace fs = std::filesystem;

App::App(const char *filename) {
	invokeFileChecks(filename);
	std::ifstream ifs(filename);
	Parser parser;
	std::string line;
	while (std::getline(ifs, line))
		if (!parser.parse(line)) throw InvalidFileFormatException(line);
	EventBuilder builder(proxy_);
	while (!parser.contentEmpty())
		std::visit(builder, parser.getNextContent());
}

void App::invokeFileChecks(const char *filename) {
	auto path = fs::path(filename);
	if (!fs::exists(path)) throw FileDoesNotExistException(path.string());
	if (!fs::is_regular_file(path)) throw UnableToOpenFileException(path.string());
	std::ifstream ifs(filename);
	if (!ifs.is_open()) throw UnableToOpenFileException(filename);
}

void App::run() {
	Orchestrator orchestrator(proxy_.num_stations, proxy_.open_time, proxy_.close_time, proxy_.price);
	auto& logger = orchestrator.logger_;
	TimePointMessage open_msg (proxy_.open_time);
	logger->log(open_msg);
	for (auto& event: proxy_.events_) {
		orchestrator.event_logger_.updateOnEvent(event);
		orchestrator.accountant_.updateOnEvent(event);
		orchestrator.client_queue_manager_.updateOnEvent(event);
		orchestrator.accounting_logger_.updateOnEvent(event);
	}
	Event event = ShutdownEvent{proxy_.close_time};
	orchestrator.event_logger_.updateOnEvent(event);
	orchestrator.accountant_.updateOnEvent(event);
	orchestrator.client_queue_manager_.updateOnEvent(event);
	TimePointMessage close_msg (proxy_.close_time);
	logger->log(close_msg);
	orchestrator.accounting_logger_.updateOnEvent(event);
}

