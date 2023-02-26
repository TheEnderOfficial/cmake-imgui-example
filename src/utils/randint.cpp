//
// Created by enderoff on 26.02.23.
//

#include <cstdlib>
#include "utils.h"
#include "time.h"

namespace AppUtils {
    int randRange(int min, int max) {
        srand(time(NULL));
        return rand() % (max - min) + min;
    }
}