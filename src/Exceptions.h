#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_


#include <exception>
#include <string>

class MessagedException : public std::exception {
    std::string message;
public:
    MessagedException(const std::string& msg) : message(msg) {}
    std::string errorMessage() {
        return std::string(message.c_str());
    }
};

class NonExistentConnection : public MessagedException {
public:
    NonExistentConnection(const std::string& msg) : MessagedException(msg) {}
};

class ShortCircuit : public MessagedException {
public:
    ShortCircuit(const std::string& msg) : MessagedException(msg) {}
};

class MatchingComponentNotFound : public MessagedException {
public:
    MatchingComponentNotFound(const std::string& msg) : MessagedException(msg) {}
};

class NoFileGiven : public MessagedException {
public:
    NoFileGiven(const std::string& msg) : MessagedException(msg) {}
};

class NonExistentLineType : public MessagedException {
public:
    NonExistentLineType(const std::string& msg) : MessagedException(msg) {}
};

class IncorrectSyntax : public MessagedException {
public:
    IncorrectSyntax(const std::string& msg) : MessagedException(msg) {}
};

class IncorrectPinCount : public MessagedException {
public:
    IncorrectPinCount(const std::string& msg) : MessagedException(msg) {}
};

class NonExistentType : public MessagedException {
public:
    NonExistentType(const std::string& msg) : MessagedException(msg) {}
};

class ConversionError : public MessagedException {
public:
    ConversionError(const std::string& msg) : MessagedException(msg) {}
};

#endif // EXCEPTIONS_H_