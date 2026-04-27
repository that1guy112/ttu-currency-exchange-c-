#ifndef EXCHANGE_EXCEPTIONS_H
#define EXCHANGE_EXCEPTIONS_H

#include <stdexcept>
#include <string>



class InvalidInput : public std::exception {
private:
    std::string message;
public:
    explicit InvalidInput(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown by the Logic layer (ExchangeManager) when a business rule is violated.
// Examples: amount <= 0, rate <= 0.
class InvalidData : public std::exception {
private:
    std::string message;
public:
    explicit InvalidData(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown by the Logic layer when a postcondition fails after computation.
// Example: conversion result is not positive.
class LogicError : public std::exception {
private:
    std::string message;
public:
    explicit LogicError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown by the Repository layer when a required rate does not exist.
class MissingRate : public std::exception {
private:
    std::string message;
public:
    explicit MissingRate(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown by the Repository layer when a reserve would go negative.
class InsufficientReserve : public std::exception {
private:
    std::string message;
public:
    explicit InsufficientReserve(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

#endif
