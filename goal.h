#ifndef EL_CLASSICO_EXPERIENCE_GOAL_H
#define EL_CLASSICO_EXPERIENCE_GOAL_H

typedef struct goal {
    int team;
    int entryTime;
    double chance;
} Goal;

extern Goal *all_goals;

void goal_init(int n);

#endif //EL_CLASSICO_EXPERIENCE_GOAL_H
