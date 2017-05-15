//
// Created by augusto on 10/05/17.
//

#include <cstdlib>
#include "Problem.h"

Problem::Problem() {
    key = rand()%12;
}

int Problem::getKey() {
    return key;
}
