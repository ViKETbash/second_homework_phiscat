#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "Errors.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"
template <typename T>
T Arg(std::stringstream &ss) {
    T value;
    if (!(ss >> value)) throw BadCommand("bad vvod");
    return value;
}
void main_energy(ServiceCenter &sc, std::stringstream &ss) {
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    std::cout << std::fixed << std::setprecision(1) << sc.totalEnergy() << '\n';
}
void main_add(ServiceCenter &sc, std::stringstream &ss) {
    std::string kind = Arg<std::string>(ss);
    if (kind == "scooter") {
        std::string id = Arg<std::string>(ss);
        std::string name = Arg<std::string>(ss);
        double energy = Arg<double>(ss);
        int score = Arg<int>(ss);
        std::string garb;
        if (ss >> garb) {
            throw BadCommand("bad vvod");
        }
        sc.addTransport(std::make_unique<Scooter>(id, name, energy, score));
    } else if (kind == "bike") {
        std::string id = Arg<std::string>(ss);
        std::string name = Arg<std::string>(ss);
        int score = Arg<int>(ss);
        std::string garb;
        if (ss >> garb) {
            throw BadCommand("bad vvod");
        }
        sc.addTransport(std::make_unique<Bike>(id, name, score));
    } else if (kind == "ebike") {
        std::string id =     Arg<std::string>(ss);
        std::string name = Arg<std::string>(ss);
        double energy = Arg<double>(ss);
        int score = Arg<int>(ss);
        std::string garb;
        if (ss >> garb) {
            throw BadCommand("bad vvod");
        }
        sc.addTransport(std::make_unique<ElectricBike>(id, name, energy, score));
    } else if (kind == "helmet") {
        std::string id = Arg<std::string>(ss);
        std::string name = Arg<std::string>(ss);
        std::string garb;
        if (ss >> garb) {
            throw BadCommand("bad vvod");
        }
        sc.addThing(std::make_unique<Helmet>(id, name));
    } else if (kind == "dock") {
        std::string id = Arg<std::string>(ss);
        std::string name = Arg<std::string>(ss);
        double energy = Arg<double>(ss);
        std::string garb;
        if (ss >> garb) {
            throw BadCommand("bad vvod");
        }
        sc.addThing(std::make_unique<Dock_station>(id, name, energy));
    } else {
        throw BadCommand("badd vvod");
    }
}
void main_list(ServiceCenter &sc, std::stringstream &ss) {
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.printAll(std::cout);
}

void main_novice(ServiceCenter &sc, std::stringstream &ss) {
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.printNovice(std::cout);
}
void main_top_energy(ServiceCenter &sc, std::stringstream &ss) {
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.printMaxEnergy(std::cout);
}
void  main_show_focus(ServiceCenter &sc, std::stringstream &ss) {
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.printfocus(std::cout);
}
void main_focus(ServiceCenter &sc, std::stringstream &ss) {
    std::string id = Arg<std::string>(ss);
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.setfocus(id);
}
void main_remove(ServiceCenter &sc, std::stringstream &ss) {
    std::string id = Arg<std::string>(ss);
    std::string garb;
    if (ss >> garb) {
        throw BadCommand("bad vvod");
    }
    sc.remove(id);
}

int main() {
    std::stringstream ss;
    std::string s;
    ServiceCenter sc;
    while (true) {
        ss.clear();
        s.clear();
        std::getline(std::cin, s);
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        ss << s;
        if (!(ss >> s)) {
            continue;
        }
        try {
            if (s == "add") {
                main_add(sc, ss);
            } else if (s == "novice") {
                main_novice(sc, ss);
            } else if (s == "quit") {
                exit(0);
            } else if (s == "list") {
                main_list(sc, ss);
            } else if (s == "focus") {
                main_focus(sc, ss);
            } else if (s == "show_focus") {
                main_show_focus(sc, ss);
            } else if (s == "remove") {
                main_remove(sc, ss);
            } else if (s == "top_energy") {
                main_top_energy(sc, ss);
            } else if (s == "energy") {
                main_energy(sc, ss);
            }
        } catch (const FleetError &garb) {
            std::cout << "error: " << garb.what() << '\n';
        }
    }
}
