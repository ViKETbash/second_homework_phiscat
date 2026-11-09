#pragma once
#include <stdexcept>

class FleetError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InspectionRejected : public FleetError {
public:
    InspectionRejected() : FleetError("Otkaz po inspekcii") {
    }
};

class BadCommand : public FleetError {
public:
    using FleetError::FleetError;
};
