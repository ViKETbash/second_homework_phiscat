#pragma once
#include <ostream>
#include <string>
#include "Inventory.hpp"

class Dock_station : public EnergyConsumer, public InventoryItem{
    std::string id_;
    std::string name_;
    double energy_;

public:
    Dock_station(std::string garb_id, std::string garb_name, double garb_energy) {
        id_ = garb_id;
        name_ = garb_name;
        energy_ = garb_energy;
        if (id_.empty()) throw BadCommand("empty id");
        if (energy_ < 0) throw BadCommand("energy is < 0");
    }

    double dailyEnergy() const override { return energy_; }
    std::string inventory_id() const override { return id_; }
    std::string inventory_name() const override { return name_; }
    void describe(std::ostream &os) const override { os << id_ << ' ' << name_; }
    const EnergyConsumer* checker_energy() const override { return this; }
};

class Helmet : public InventoryItem {
    std::string id_;
    std::string name_;

public:
    Helmet(std::string garb_id, std::string garb_name) {
        id_ = garb_id;
        name_ = garb_name;
        if (id_.empty()) throw BadCommand("empty id");
    }

    std::string inventory_id() const override { return id_; }
    std::string inventory_name() const override { return name_; }
    void describe(std::ostream &os) const override { os << id_ << ' ' << name_; }
};
