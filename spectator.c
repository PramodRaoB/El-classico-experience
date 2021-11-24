#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "spectator.h"
#include "globals.h"
#include "goal.h"

pthread_cond_t homeFans;
pthread_cond_t awayFans;

void fans_init() {
    Pthread_cond_init(&homeFans, NULL);
    Pthread_cond_init(&awayFans, NULL);
}

void *spectator_process(void *input) {
    Spectator *spectator = (Spectator *) input;
    sleep(spectator->entryTime);
    pthread_t seatAcquireThreads[3];
    if (spectator->type == HOME) {
        Pthread_create(&seatAcquireThreads[HOME], NULL, home_acquire, input);
        Pthread_create(&seatAcquireThreads[NEUTRAL], NULL, neutral_acquire, input);
    }
    else if (spectator->type == NEUTRAL) {
        Pthread_create(&seatAcquireThreads[HOME], NULL, home_acquire, input);
        Pthread_create(&seatAcquireThreads[NEUTRAL], NULL, neutral_acquire, input);
        Pthread_create(&seatAcquireThreads[AWAY], NULL, away_acquire, input);
    }
    else {
        Pthread_create(&seatAcquireThreads[AWAY], NULL, away_acquire, input);
    }

    Pthread_mutex_lock(&spectator->seatLock);
    Pthread_cond_wait(&spectator->seatCV, &spectator->seatLock);
    if (spectator->seatType == -1) {
        printf("%s couldn't get a seat\n", spectator->name);
        Pthread_mutex_unlock(&spectator->seatLock);
        return NULL;
    }
    Pthread_mutex_unlock(&spectator->seatLock);

    if (spectator->type == NEUTRAL) {
        sleep(spectatingTime);
        printf("%s watched the match for %d seconds and is leaving\n", spectator->name, spectatingTime);
    }
    else {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += spectatingTime;
        int decidedToLeave = 0;
        while (!decidedToLeave) {
            Pthread_mutex_lock(&Scoreboard.scoreboardLock);
            int rc = 0;
            if (spectator->type == HOME)
                rc = pthread_cond_timedwait(&homeFans, &Scoreboard.scoreboardLock, &ts);
            else
                rc = pthread_cond_timedwait(&awayFans, &Scoreboard.scoreboardLock, &ts);
            if (rc != 0) {
                decidedToLeave = 1;
                printf("%s watched the match for %d seconds and is leaving\n", spectator->name, spectatingTime);
            } else if (Scoreboard.score[spectator->type ^ 1] >= spectator->goalLimit) {
                printf("%s is leaving due to the bad defensive performance of his team\n", spectator->name);
                decidedToLeave = 1;
            }
            Pthread_mutex_unlock(&Scoreboard.scoreboardLock);
        }
    }
    printf("%s is waiting for their friends at the exit\n", spectator->name);
    return NULL;
}

void *home_acquire(void *input) {
    Spectator *spectator = (Spectator *) input;
}