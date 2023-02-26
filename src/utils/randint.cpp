//
// Created by enderoff on 26.02.23.
//

#include <cstdlib>
#include "utils.h"

namespace AppUtils {
    int randRange(int min, int max) {
        return rand() % (max - min) + min;
    }
}