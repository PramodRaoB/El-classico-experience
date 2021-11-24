#ifndef EL_CLASSICO_EXPERIENCE_SPECTATOR_H
#define EL_CLASSICO_EXPERIENCE_SPECTATOR_H

#include "wrapper.h"

#define MAX_NAME_LEN 256

typedef struct spectator {
    char *name;
    int type;
    int entryTime;
    int patienceTime;
    int goalLimit;
    int groupID;
    pthread_mutex_t seatLock;
    pthread_cond_t seatCV;
    int seatType;
} Spectator;

typedef struct seatGrab {
    Spectator *spectator;
    int seatType;
} SeatGrab;

extern int spectatingTime;

extern pthread_cond_t homeFans;
extern pthread_cond_t awayFans;

void fans_init();
void *spectator_process(void *input);
void *seat_acquire(void *input);

#endif //EL_CLASSICO_EXPERIENCE_SPECTATOR_H
