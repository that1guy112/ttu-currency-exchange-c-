#ifndef IREPORTABLE_H
#define IREPORTABLE_H

#include <string>

// Abstract interface — forces all reportable entities to produce a summary string.
// Addresses Lecture 6: Abstraction and Polymorphism.
// UI calls generateReport() on any IReportable without knowing its concrete type.
class IReportable {
public:
    virtual std::string generateReport() const = 0;
    virtual ~IReportable() = default;
};

#endif
