#ifndef EL_CLASSICO_EXPERIENCE_GLOBALS_H
#define EL_CLASSICO_EXPERIENCE_GLOBALS_H

#include "semaphore.h"

enum zone {HOME, AWAY, NEUTRAL};
extern sem_t *zoneSeats;

#endif //EL_CLASSICO_EXPERIENCE_GLOBALS_H
