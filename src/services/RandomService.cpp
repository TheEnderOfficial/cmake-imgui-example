//
// Created by enderoff on 26.02.23.
//

#include "../../inc/services/RandomService.h"
#include <cstdlib>
#include <time.h>

namespace RandomService {
    int RandomService::randInt(int min, int max) {
        srand(time(nullptr));
        return rand() % (max - min) + min;
    }
}