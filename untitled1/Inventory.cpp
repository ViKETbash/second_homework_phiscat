#include "Inventory.hpp"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const InventoryItem &item) {
    item.describe(os);
    return os;
}

bool operator<(const InventoryItem &a, const InventoryItem &b) {
    return a.inventory_id() < b.inventory_id();
}
