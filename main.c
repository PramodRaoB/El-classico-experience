#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "globals.h"
#include "group.h"
#include "goal.h"
#include "wrapper.h"

int numGoals;
int spectatingTime;

int main() {
    int capacity[3];
    scanf("%d %d %d", &capacity[HOME], &capacity[AWAY], &capacity[NEUTRAL]);
    scanf("%d", &spectatingTime);
    int numGroups;
    scanf("%d", &numGroups);
    group_init(numGroups);
    for (int i = 0; i < numGroups; i++) {
        Group *currGroup = &all_groups[i];
        scanf("%d", &currGroup->size);
        group_fill(&currGroup->members, currGroup->size);
        currGroup->id = i;
        for (int j = 0; j < currGroup->size; j++) {
            char zoneType;
            Spectator *currMember = &currGroup->members[j];
            scanf("%s %c %d %d %d", currMember->name, &zoneType, &currMember->entryTime, &currMember->patienceTime, &currMember->goalLimit);
            int validInput = 0;
            while (!validInput) {
                switch (zoneType) {
                    case 'A':
                        currMember->type = AWAY;
                        validInput = 1;
                        break;
                    case 'H':
                        currMember->type = HOME;
                        validInput = 1;
                        break;
                    default:
                        fprintf(stderr, "Invalid team entered. Enter valid team (H/A): ");
                }
            }
            currMember->groupID = i;
        }
    }
    scanf("%d", &numGoals);
    goal_init(numGoals);
    int prefixTime = 0;
    for (int i = 0; i < numGoals; i++) {
        Goal *currGoal = &all_goals[i];
        char teamType;
        scanf("%c %d %lf", &teamType, &currGoal->delta, &currGoal->chance);
        int validInput = 0;
        while (!validInput) {
            switch (teamType) {
                case 'A':
                    currGoal->team = AWAY;
                    validInput = 1;
                    break;
                case 'H':
                    currGoal->team = HOME;
                    validInput = 1;
                    break;
                case 'N':
                    currGoal->team = NEUTRAL;
                    validInput = 1;
                    break;
                default:
                    fprintf(stderr, "Invalid zone type entered. Enter the valid zone type: ");
            }
        }
        if (i != 0) currGoal->delta -= prefixTime;
        prefixTime += currGoal->delta;
    }
    scoreboard_init();
    fans_init();

    //simulation start
    pthread_t goalThread;
    Pthread_create(&goalThread, NULL, goal_process, all_goals);

    pthread_t *groupThreads = NULL;
    groupThreads = (pthread_t *) malloc(numGroups * sizeof(pthread_t));
    assert(groupThreads);
    for (int i = 0; i < numGroups; i++)
        Pthread_create(&groupThreads[i], NULL, group_process, (Group *) &all_groups[i]);
}