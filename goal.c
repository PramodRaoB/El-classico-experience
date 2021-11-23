#include <stdlib.h>
#include <assert.h>
#include "goal.h"

Goal *all_goals = NULL;

void goal_init(int n) {
    all_goals = (Goal *) malloc(n * sizeof(Goal));
    assert(all_goals);
}
