#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Inventory.hpp"
#include "Transport.hpp"

class ServiceCenter {
    std::vector<std::shared_ptr<InventoryItem> > fleet_;

    std::weak_ptr<InventoryItem> focus_;

    std::shared_ptr<InventoryItem> find(const std::string &id) const;

    void inspect(const Transport &t) const;

    bool hasId(const std::string &id) const;

public:
    void setfocus(const std::string &id);

    void printfocus(std::ostream &os) const;

    void addTransport(std::unique_ptr<Transport> t);

    void addThing(std::unique_ptr<InventoryItem> item);

    void remove(const std::string &id);

    std::size_t size() const { return fleet_.size(); }

    double totalEnergy() const;

    void printAll(std::ostream &os) const;

    void printNovice(std::ostream &os) const;
};
