#ifndef EL_CLASSICO_EXPERIENCE_GLOBALS_H
#define EL_CLASSICO_EXPERIENCE_GLOBALS_H

#include "semaphore.h"

enum zone {HOME, AWAY, NEUTRAL};
extern sem_t *zoneSeats;

#define C_GROUP     "\x1b[35m"
#define C_SPECTATOR   "\x1b[32m"
#define C_GOAL  "\x1b[33m"
#define C_SPECTATOR2 "\x1b[36m"
#define RESET   "\x1b[0m"

#endif //EL_CLASSICO_EXPERIENCE_GLOBALS_H
