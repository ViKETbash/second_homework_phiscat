#include <algorithm>
#include <cctype>
#include <ostream>
#include "Errors.hpp"
#include "ServiceCenter.hpp"

namespace {
    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return s;
    }
}

std::shared_ptr<InventoryItem> ServiceCenter::find(const std::string &id) const {
    for (const auto &p: fleet_)
        if (p->inventory_id() == id) return p;
    return nullptr;
}

void ServiceCenter::setfocus(const std::string &id) {
    std::shared_ptr<InventoryItem> item = find(id);
    if (!item) throw BadCommand("no such id");
    focus_ = item;
}

bool ServiceCenter::hasId(const std::string &id) const {
    for (const auto &p: fleet_) {
        if (p->inventory_id() == id) return true;
    }
    return false;
}

void ServiceCenter::inspect(const Transport &t) const {
    if (toLower(t.inventory_name()).find("broken") != std::string::npos)
        throw InspectionRejected();
}

void ServiceCenter::addTransport(std::unique_ptr<Transport> t) {
    try {
        inspect(*t);
    } catch (const InspectionRejected &) {
        reg("rejected " + (*t).inventory_id());
        throw;
    }
    if (hasId((*t).inventory_id())) throw BadCommand("duplicate id");
    reg("new_" + (*t).inventory_id());
    fleet_.push_back(std::move(t));
}

void ServiceCenter::printfocus(std::ostream &os) const {
    if (std::shared_ptr<InventoryItem> item = focus_.lock())
        os << *item << '\n';
    else
        os << "expired\n";
}

void ServiceCenter::addThing(std::unique_ptr<InventoryItem> item) {
    if (hasId((*item).inventory_id())) throw BadCommand("duplicate id");
    reg("new_" + (*item).inventory_id());
    fleet_.push_back(std::move(item));
}

void ServiceCenter::remove(const std::string &id) {
    auto it = std::find_if(fleet_.begin(), fleet_.end(),
                           [&](const std::shared_ptr<InventoryItem> &p) { return p->inventory_id() == id; });
    if (it == fleet_.end()) throw BadCommand("no such id");
    fleet_.erase(it);
    reg("udalen_" + id);
}

double ServiceCenter::totalEnergy() const {
    double total = 0;
    for (const auto &p: fleet_)
        if (const EnergyConsumer *c = p->checker_energy()) total += c->dailyEnergy();
    return total;
}

void ServiceCenter::printAll(std::ostream &os) const {
    std::vector<const InventoryItem *> view;
    for (const auto &p: fleet_) view.push_back(p.get());
    std::sort(view.begin(), view.end(),
              [](const InventoryItem *a, const InventoryItem *b) { return *a < *b; });
    for (const InventoryItem *p: view) os << *p << '\n';
}

void ServiceCenter::printNovice(std::ostream &os) const {
    for (const auto &p: fleet_)
        if (p->check_rook()) os << *p << '\n';
}

void ServiceCenter::reg(const std::string &msg) {
    if (zhurnal_.check()) {
        zhurnal_.add(msg);
    }
}

void ServiceCenter::printZhurnal(std::ostream &os) const {
    os << zhurnal_;
}

void ServiceCenter::printMaxEnergy(std::ostream &os) const {
    std::vector<const InventoryItem *> all;
    for (const auto &p: fleet_)
        if (p->checker_energy()) all.push_back(p.get());
    std::sort(all.begin(), all.end(),
              [](const InventoryItem *a, const InventoryItem *b) {
                  double ea = a->checker_energy()->dailyEnergy();
                  double eb = b->checker_energy()->dailyEnergy();
                  if (ea != eb) return ea > eb;
                  return *a < *b;
              });
    Registry<const InventoryItem *, 3> top;
    for (const InventoryItem *p: all) {
        if (!top.check()) break;
        top.add(p);
    }
    os << top;
}
