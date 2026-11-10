#include <iostream>
#include <memory>
#include "Inventory.hpp"
#include "Things.hpp"


int main() {
    std::unique_ptr<InventoryItem> p = std::make_unique<Helmet>("nefr_europapa", "negr_afrika(mbappe)");
    std::cout << *p << '\n';
    Dock_station d("fanat_arsenala", "elis", 10.0);
    Helmet h("fanat_chelsea", "ilusha");
    std::cout << h << '\n';
    std::cout << d << '\n';
    std::cout << d.dailyEnergy() << '\n';
    InventoryItem* garb_a = &d;
    EnergyConsumer* garb_e = &d;
    std::cout << garb_a->inventory_id() << ' ' << garb_e->dailyEnergy() << '\n';
}
