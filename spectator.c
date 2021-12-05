#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "spectator.h"
#include "globals.h"
#include "goal.h"

pthread_cond_t homeFans;
pthread_cond_t awayFans;

pthread_mutex_t searchingLock;
pthread_cond_t searchingCV;
int searching = 0;

void fans_init() {
    Pthread_cond_init(&homeFans, NULL);
    Pthread_cond_init(&awayFans, NULL);
}

void *spectator_process(void *input) {
    Spectator *spectator = (Spectator *) input;
    sleep(spectator->entryTime);
    printf(C_SPECTATOR "%s has reached the stadium\n" RESET, spectator->name);
    pthread_t seatAcquireThreads[3];
    if (spectator->type == HOME || spectator->type == NEUTRAL) {
        SeatGrab sg;
        sg.spectator = spectator;
        sg.seatType = HOME;
        Pthread_create(&seatAcquireThreads[HOME], NULL, seat_acquire, (void *) &sg);
    }
    if (spectator->type == AWAY || spectator->type == NEUTRAL) {
        SeatGrab sg;
        sg.spectator = spectator;
        sg.seatType = AWAY;
        Pthread_create(&seatAcquireThreads[AWAY], NULL, seat_acquire, (void *) &sg);
    }
    if (spectator->type == NEUTRAL) {
        SeatGrab sg;
        sg.spectator = spectator;
        sg.seatType = NEUTRAL;
        Pthread_create(&seatAcquireThreads[NEUTRAL], NULL, seat_acquire, (void *) &sg);
    }
    Pthread_mutex_init(&searchingLock, NULL);
    Pthread_cond_init(&searchingCV, NULL);

    Pthread_mutex_lock(&spectator->seatLock);

    Pthread_mutex_lock(&searchingLock);
    searching = 1;
    Pthread_cond_broadcast(&searchingCV);
    Pthread_mutex_unlock(&searchingLock);

    struct timespec ts_;
    clock_gettime(CLOCK_REALTIME, &ts_);
    ts_.tv_sec += spectator->patienceTime;
    pthread_cond_timedwait(&spectator->seatCV, &spectator->seatLock, &ts_);
    Pthread_mutex_unlock(&spectator->seatLock);
    if (spectator->seatType == -1) {
        printf(C_SPECTATOR2 "%s couldn't get a seat\n" RESET, spectator->name);
    }
    else {
        char c;
        switch(spectator->seatType) {
            case HOME:
                c = 'H';
                break;
            case AWAY:
                c = 'A';
                break;
            default:
                c = 'N';
        }
        printf(C_SPECTATOR "%s has got a seat in zone %c\n" RESET, spectator->name, c);
        if (spectator->type == NEUTRAL) {
            sleep(spectatingTime);
            printf(C_SPECTATOR2 "%s watched the match for %d seconds and is leaving\n" RESET, spectator->name, spectatingTime);
        } else {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += spectatingTime;
            int decidedToLeave = 0;
            while (!decidedToLeave) {
                Pthread_mutex_lock(&Scoreboard.scoreboardLock);
                if (Scoreboard.score[spectator->type ^ 1] >= spectator->goalLimit) {
                    printf(C_SPECTATOR2 "%s is leaving due to the bad defensive performance of his team\n" RESET, spectator->name);
                    decidedToLeave = 1;
                    Pthread_mutex_unlock(&Scoreboard.scoreboardLock);
                    continue;
                }
                int rc = 0;
                if (spectator->type == HOME)
                    rc = pthread_cond_timedwait(&homeFans, &Scoreboard.scoreboardLock, &ts);
                else
                    rc = pthread_cond_timedwait(&awayFans, &Scoreboard.scoreboardLock, &ts);
                if (rc != 0) {
                    decidedToLeave = 1;
                    printf(C_SPECTATOR2 "%s watched the match for %d seconds and is leaving\n" RESET, spectator->name, spectatingTime);
                } else if (Scoreboard.score[spectator->type ^ 1] >= spectator->goalLimit) {
                    printf(C_SPECTATOR2 "%s is leaving due to the bad defensive performance of his team\n" RESET, spectator->name);
                    decidedToLeave = 1;
                }
                Pthread_mutex_unlock(&Scoreboard.scoreboardLock);
            }
        }
        sem_post(&zoneSeats[spectator->seatType]);
    }
    printf(C_SPECTATOR "%s is waiting for their friends at the exit\n" RESET, spectator->name);
    return NULL;
}

void *seat_acquire(void *input) {
    SeatGrab *sg = (SeatGrab *) input;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += sg->spectator->patienceTime;
    Pthread_mutex_lock(&searchingLock);
    while (!searching)
        Pthread_cond_wait(&searchingCV, &searchingLock);
    Pthread_mutex_unlock(&searchingLock);

    if (sem_timedwait(&zoneSeats[sg->seatType], &ts) != 0) {
        return NULL;
    }
    Pthread_mutex_lock(&sg->spectator->seatLock);
    if (sg->spectator->seatType != -1) {
        sem_post(&zoneSeats[sg->seatType]);
        Pthread_mutex_unlock(&sg->spectator->seatLock);
        return NULL;
    }
    sg->spectator->seatType = sg->seatType;
    Pthread_cond_signal(&sg->spectator->seatCV);
    Pthread_mutex_unlock(&sg->spectator->seatLock);
    return NULL;
}