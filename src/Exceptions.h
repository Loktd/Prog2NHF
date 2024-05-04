#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_


#include <exception>
#include <string>


class NonExistentConnection : public std::exception {
    std::string message;
public:
    NonExistentConnection(const std::string& msg) : message(msg) {}
    const char* what() {
        return message.c_str();
    }
};

class ShortCircuit : public std::exception {
    std::string message;
public:
    ShortCircuit(const std::string& msg) : message(msg) {}
    const char* what() {
        return message.c_str();
    }
};


#endif // EXCEPTIONS_H_