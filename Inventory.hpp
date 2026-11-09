#pragma once
#include <string>

class InventoryItem {
public:
    virtual ~InventoryItem() = default;

    virtual std::string inventory_id() const = 0;

    virtual std::string inventory_name() const = 0;

    virtual void describe(std::ostream &os) const = 0;
};
