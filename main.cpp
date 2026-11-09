#include <iostream>
#include <memory>
#include "Inventory.hpp"

class Helmet : public InventoryItem {
    std::string helmet_id;
    std::string helmet_name;

public:
    Helmet(std::string garb_id, std::string garb_name) {
        helmet_id = garb_id;
        helmet_name = garb_name;
    }

    std::string inventory_id() const override { return helmet_id; }
    std::string inventory_name() const override { return helmet_name; }
    void describe(std::ostream &os) const override { os << helmet_id << ' ' << helmet_name << '\n'; }
};

int main() {
    std::unique_ptr<InventoryItem> p = std::make_unique<Helmet>("nefr_europapa", "negr_afrika(mbappe)");
    std::cout << *p << '\n';
}
