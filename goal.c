#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "goal.h"
#include "wrapper.h"
#include "globals.h"
#include "spectator.h"

Goal *all_goals = NULL;
struct scoreboard Scoreboard;

void goal_init(int n) {
    all_goals = (Goal *) malloc(n * sizeof(Goal));
    assert(all_goals);
}

void scoreboard_init() {
    Scoreboard.score[HOME] = 0;
    Scoreboard.score[AWAY] = 0;
    Pthread_mutex_init(&Scoreboard.scoreboardLock, NULL);
}

void *goal_process(void *input) {
    for (int i = 0; i < numGoals; i++) {
        Goal *currGoal = &all_goals[i];
        sleep(currGoal->delta);
        double prob = (double) rand() / RAND_MAX;
        if (prob <= currGoal->chance) {
            Pthread_mutex_lock(&Scoreboard.scoreboardLock);
            Scoreboard.score[currGoal->team]++;

            if (currGoal->team == HOME)
                Pthread_cond_broadcast(&awayFans);
            else
                Pthread_cond_broadcast(&homeFans);
            Pthread_mutex_unlock(&Scoreboard.scoreboardLock);
            printf(C_GOAL "Team %c have scored their %dth goal\n" RESET, (currGoal->team == HOME ? 'H': 'A'), Scoreboard.score[currGoal->team]);
        }
        else {
            printf(C_GOAL "Team %c missed the chance to score their %dth goal\n" RESET, (currGoal->team == HOME ? 'H': 'A'), Scoreboard.score[currGoal->team] + 1);
        }
    }
    return NULL;
}