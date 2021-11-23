#include <stdio.h>
#include "globals.h"
#include "group.h"
#include "goal.h"

int main() {
    int capacity[3];
    scanf("%d %d %d", &capacity[HOME], &capacity[AWAY], &capacity[NEUTRAL]);
    int spectatingTime;
    scanf("%d", &spectatingTime);
    int numGroups;
    scanf("%d", &numGroups);
    group_init(numGroups);
    for (int i = 0; i < numGroups; i++) {
        Group *currGroup = &all_groups[i];
        scanf("%d", &currGroup->size);
        group_fill(&currGroup->members, currGroup->size);
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
                    case 'N':
                        currMember->type = NEUTRAL;
                        validInput = 1;
                        break;
                    default:
                        fprintf(stderr, "Invalid zone type entered. Enter the valid zone type: ");
                }
            }
            currMember->groupID = i;
        }
    }
    int numGoals;
    scanf("%d", &numGoals);
    goal_init(numGoals);
    for (int i = 0; i < numGoals; i++) {
        Goal *currGoal = &all_goals[i];
        char teamType;
        scanf("%c %d %lf", &teamType, &currGoal->entryTime, &currGoal->chance);
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
    }

    //simulation start
}