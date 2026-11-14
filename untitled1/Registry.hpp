#pragma once
#include <string>
#include "Errors.hpp"

template <typename T>
void outPrint(std::ostream& os, const T& x) {
    os << x;
}
template <>
inline void outPrint<const InventoryItem*>(std::ostream& os, const InventoryItem* const& p) {
    os << *p;
}
template<typename T, int Cap>

class Registry {
    T inf_[Cap];
    int sz_ = 0;
    public:
    void add(const T& x) {
        if (sz_ >= Cap) {
            throw FleetError("Zhurnal perepolnen");
        }
        inf_[sz_] = x;
        sz_++;
    }
    int size() {
        return sz_;
    }
    int check() {
        if (sz_ >= Cap) {
            return 0;
        }
        return 1;
    }
    const T& operator[](int i) const {
        if (i < 0 || i >= sz_) {
            throw FleetError("vishel za masssiv");
        }
        return inf_[i];
    }
    friend std::ostream& operator<<(std::ostream& os, const Registry& zhurnal) {
        for (int i = 0; i < zhurnal.sz_; i++) {
            outPrint(os, zhurnal.inf_[i]);
            os << '\n';
        }
        return os;
    }
};
