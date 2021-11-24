#include <stdlib.h>
#include <assert.h>
#include "group.h"

Group *all_groups = NULL;

void group_init(int n) {
    all_groups = (Group *) malloc(n * sizeof(Group));
    assert(all_groups);
}

void group_fill(Spectator **members, int n) {
    *members = (Spectator *) malloc(n * sizeof(Spectator));
    assert(*members);
    for (int i = 0; i < n; i++) {
        (*members)[i].name = (char *) malloc(MAX_NAME_LEN);
        assert((*members)[i].name);
        Pthread_mutex_init(&(*members)[i].seatLock, NULL);
        Pthread_cond_init(&(*members)[i].seatCV, NULL);
        (*members)[i].seatType = -1;
    }
}

void *group_process(void *input) {
    Group *group = (Group *) input;
    pthread_t *memberThreads = (pthread_t *) malloc(group->size * sizeof(pthread_t));
    assert(memberThreads);
    for (int i = 0; i < group->size; i++) {
        Pthread_create(&memberThreads[i], NULL, spectator_process, (void *) &group->members[i]);
    }
}