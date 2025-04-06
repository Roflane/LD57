#pragma once
#include <raylib.h>
#include <vector>
#include "../base/typedefs.h"
#include "../base/misc.h"
#include "../base/dirs.h"
#include "Orb.h"

class OrbGroup {
private:
    // Fields
    std::vector<Orb> _orbs;
public:
    // Properties
    ushort getSize() const { return _orbs.size(); }

    // Operator overloads
    Orb& operator[](ushort index) {
        return _orbs[index];
    }
    
    // Methods
    void fillOrbs();
    void update();
};