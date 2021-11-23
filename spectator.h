#ifndef EL_CLASSICO_EXPERIENCE_SPECTATOR_H
#define EL_CLASSICO_EXPERIENCE_SPECTATOR_H

#define MAX_NAME_LEN 256

typedef struct spectator {
    char *name;
    int type;
    int entryTime;
    int patienceTime;
    int goalLimit;
    int groupID;
} Spectator;

#endif //EL_CLASSICO_EXPERIENCE_SPECTATOR_H
