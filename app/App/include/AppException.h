#ifndef APPEXCPETION_H
#define APPEXCPETION_H
#include <exception>
#include <string>

class AppException : public std::exception {
protected:
	std::string msg;
public:
	AppException(std::string msg = {}) : msg(std::move(msg)) {}

    const char* what() const noexcept override {
	    return msg.c_str();
    }

	virtual ~AppException() = default;
};

class FileDoesNotExistException final : public AppException {
public:
	FileDoesNotExistException(std::string filename) {
		msg = "File " + std::move(filename) + " does not exist";
	}
};


class UnableToOpenFileException final : public AppException {
public:
	UnableToOpenFileException(std::string filename) {
		msg = "File " + std::move(filename) + " could not be opened";
	}
};

class InvalidFileFormatException final : public AppException {
public:
	InvalidFileFormatException(std::string invalid_string): AppException(std::move(invalid_string)) {}
};
#endif //APPEXCPETION_H
