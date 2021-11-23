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
    }
}