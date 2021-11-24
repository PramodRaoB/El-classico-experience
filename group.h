#ifndef EL_CLASSICO_EXPERIENCE_GROUP_H
#define EL_CLASSICO_EXPERIENCE_GROUP_H

#include "spectator.h"

typedef struct group {
    int size;
    Spectator *members;
    int id;
} Group;

extern Group *all_groups;

void group_init(int n);
void group_fill(Spectator **members, int n);

void *group_process(void *input);

#endif //EL_CLASSICO_EXPERIENCE_GROUP_H
