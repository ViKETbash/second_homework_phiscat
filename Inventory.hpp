#pragma once
#include <string>

class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual std::string inventory_id() const = 0;

    virtual std::string inventory_name() const = 0;

    virtual void describe(std::ostream &os) const = 0;
};

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;

    virtual double dailyEnergy() const = 0;
};

std::ostream &operator<<(std::ostream &os, const InventoryItem &item);

bool operator<(const InventoryItem &a, const InventoryItem &b);
