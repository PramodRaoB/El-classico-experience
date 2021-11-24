#ifndef EL_CLASSICO_EXPERIENCE_GOAL_H
#define EL_CLASSICO_EXPERIENCE_GOAL_H

typedef struct goal {
    int team;
    int delta;
    double chance;
} Goal;

struct scoreboard {
    int score[2];
    pthread_mutex_t scoreboardLock;
};

extern int numGoals;
extern Goal *all_goals;

extern struct scoreboard Scoreboard;

void goal_init(int n);
void scoreboard_init();
void *goal_process(void *input);

#endif //EL_CLASSICO_EXPERIENCE_GOAL_H
