#pragma once
#include <raylib.h>
#include <vector>
#include <time.h>

#include "../libs/XVec.h"
#include "../libs/XStr.h"

#include "settings/GlobalSettings.h"
#include "../base/dirs.h"

#include "ui/gauge.h"
#include "ui/utility/Tooltip.h"

#include "graphics/Star.h"
#include "Orb.h"
#include "Card.h"
#include "CardCollection.h"


#define LOG(...) std::cout << __VA_ARGS__ << '\n'

extern void MainLoop();