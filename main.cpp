#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "Transport.hpp"
#include "Inventory.hpp"
#include "Things.hpp"
#include "ServiceCenter.hpp"

template<typename F>
void attempt(F f) {
    try { f(); } catch (const FleetError &e) { std::cout << "error: " << e.what() << '\n'; }
}


int main() {
    std::unique_ptr<InventoryItem> p = std::make_unique<Helmet>("nefr_europapa", "negr_afrika(mbappe)");
    std::cout << *p << '\n';
    Dock_station d("fanat_arsenala", "elis", 10.0);
    Helmet h("fanat_chelsea", "ilusha");
    std::cout << h << '\n';
    std::cout << d << '\n';
    std::cout << d.dailyEnergy() << '\n';
    InventoryItem *garb_a = &d;
    EnergyConsumer *garb_e = &d;
    std::cout << garb_a->inventory_id() << ' ' << garb_e->dailyEnergy() << '\n';
    std::vector<std::unique_ptr<InventoryItem> > v;
    v.push_back(std::make_unique<Scooter>("S-1", "ModelX", 2.5, 8));
    v.push_back(std::make_unique<Scooter>("S-3", "Slow", 1.5, 5));
    v.push_back(std::make_unique<Bike>("B-1", "City", 4));
    v.push_back(std::make_unique<ElectricBike>("E-1", "Volt", 0.5, 7));
    v.push_back(std::make_unique<Dock_station>("D-1", "Hub", 10.0));
    double total = 0;
    for (const auto &p: v) {
        std::cout << *p << '\n';
        if (p->check_rook()) std::cout << "rookie\n";
        if (const EnergyConsumer *c = p->checker_energy()) total += c->dailyEnergy();
    }
    std::cout << total << '\n';
    std::cout << "-----------------------------------" << '\n';
    ServiceCenter sc;
    attempt([&] { sc.addTransport(std::make_unique<Scooter>("Mancity", "blue", 2.5, 8)); });
    attempt([&] { sc.addTransport(std::make_unique<Bike>("MU", "City", 4)); });
    attempt([&] { sc.addTransport(std::make_unique<Scooter>("Chelsea", "BrokenX", 1.0, 9)); });
    attempt([&] { sc.addThing(std::make_unique<Helmet>("barca-fu", "nePro")); });
    attempt([&] { sc.addThing(std::make_unique<Dock_station>("tarkov", "Hub", 10.0)); });

    //sc.printAll(std::cout);
    sc.printNovice(std::cout);
    std::cout << sc.totalEnergy() << '\n';
    std::cout << "--------------------" << '\n';
}
