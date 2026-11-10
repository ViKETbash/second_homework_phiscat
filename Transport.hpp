#pragma once

#include "Inventory.hpp"
#include "Errors.hpp"

class Transport : public InventoryItem {
    std::string id_;
    std::string name_;
    int rookie_;

protected:
    Transport(std::string garb_id, std::string garb_name, int garb_score) {
        id_ = garb_id;
        name_ = garb_name;
        rookie_ = garb_score;
        if (id_.empty()) throw BadCommand("empty id");
        if (rookie_ < 1 || rookie_ > 10) throw BadCommand("rang out of range");
    }

public:
    std::string inventory_id() const override { return id_; }
    std::string inventory_name() const override { return name_; }
    void describe(std::ostream &os) const override { os << id_ << ' ' << name_; }
    bool check_rook() const override { return rookie_ >= 6; }
    int rookies() const { return rookie_; }
};

class Bike : public Transport {
public:
    Bike(std::string garb_id, std::string garb_name, int garb_rookie)
        : Transport(std::move(garb_id), std::move(garb_name), garb_rookie) {
    }
};

class ElectricBike : public Bike, public EnergyConsumer {
    double energy_;

public:
    ElectricBike(std::string garb_id, std::string garb_name, double garb_energy, int garb_rookie)
        : Bike(std::move(garb_id), std::move(garb_name), garb_rookie), energy_(garb_energy) {
    }

    double dailyEnergy() const override { return energy_; }
    const EnergyConsumer *checker_energy() const override { return this; }
};

class Scooter : public Transport, public EnergyConsumer {
    double energy_;

public:
    Scooter(std::string garb_id, std::string garb_name, double garb_energy, int garb_rookie)
        : Transport(std::move(garb_id), std::move(garb_name), garb_rookie), energy_(garb_energy) {
        if (energy_ < 0) throw BadCommand("energy is < 0");
    }

    double dailyEnergy() const override { return energy_; }
    const EnergyConsumer *checker_energy() const override { return this; }
};
