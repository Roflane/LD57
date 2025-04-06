#include "OrbGroup.h"

void OrbGroup::fillOrbs() {
	Orb red(ORB_RED);
	Orb violet(ORB_VIOLET);
	Orb blue(ORB_BLUE);

	std::cout << "red orb pos: " << red.getPos().x << std::endl;

	std::vector<Orb> orbList = { red, violet, blue };
	_orbs = orbList;
}

void OrbGroup::update() {
	for (auto &orb : _orbs) {
		orb.update();
	}
}