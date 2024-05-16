#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>

class InputComponent;

class MessagedException : public std::exception {
    std::string message;
public:
    MessagedException(const std::string& msg) : message(msg) {}
    std::string exception_message() {
        return std::string(message.c_str());
    }
};

class NonExistentConnection : public MessagedException {
public:
    NonExistentConnection(const std::string& msg) : MessagedException(msg) {}
};

class ShortCircuit : public MessagedException {
    InputComponent* resimulated;
public:
    ShortCircuit(const std::string& msg, InputComponent* resimmed) : MessagedException(msg), resimulated(resimmed) {}
    InputComponent* getResimulated() { return resimulated; }
};

class MatchingComponentNotFound : public MessagedException {
public:
    MatchingComponentNotFound(const std::string& msg) : MessagedException(msg) {}
};

class FileAccessError : public MessagedException {
public:
    FileAccessError(const std::string& msg) : MessagedException(msg) {}
};

class NonExistentLineType : public MessagedException {
public:
    NonExistentLineType(const std::string& msg) : MessagedException(msg) {}
};

class CommentLine : public MessagedException {
public:
    CommentLine(const std::string& msg) : MessagedException(msg) {}
};

class IncorrectSyntax : public MessagedException {
public:
    IncorrectSyntax(const std::string& msg) : MessagedException(msg) {}
};

class IncorrectPinCount : public MessagedException {
public:
    IncorrectPinCount(const std::string& msg) : MessagedException(msg) {}
};

class PointerConversionError : public MessagedException {
public:
    PointerConversionError(const std::string& msg) : MessagedException(msg) {}
};

class UnsimulatedComponent : public MessagedException {
public:
    UnsimulatedComponent(const std::string& msg) : MessagedException(msg) {}
};

class SchematicsFileHasSyntaxError : public MessagedException {
public:
    SchematicsFileHasSyntaxError(const std::string msg) : MessagedException(msg) {}
};

class ConfigurationError : public MessagedException {
public:
    ConfigurationError(const std::string msg) : MessagedException(msg) {}
};

#endif // EXCEPTIONS_H_