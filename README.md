# Monsoon 2021 - OS Assignment 5

> Pramod Rao B
> 2020111012

## Multithreaded El-classico experience

Entities being simulated by threads:

- Groups
- Goals
- Spectators

Entities being simulated as a resource (semaphore):

- Seats available in each zone

### General working

Each spectator is either a "HOME" fan, an "AWAY" fan or a "NEURAL" fan. The stands are also divided into three zone "H", "A" and "N". A home fan may pick H or N, an away fan may pick only A and a neutral fan may pick any of the three zones. Each spectator arrives at the stadium and waits to get a ticket in any of his preferred zones. Once he manages to get a ticket, he spectates the match until either he gets bored and leaves or if he gets enraged because the opponent team scored more than or equal to some given number of goals. He then leaves the zone and **waits at the gate for his friends and once they all reach the gate, they go out for dinner together.**

- **Zone seats**

  Each of the three zones are implemented using semaphores so that we can perform atomic post and wait operations.

- **Group thread**
  1. The group thread creates all the spectator threads who are under that group
  2. To make sure all the spectators in one group leave home together **[BONUS]** the group thread, joins the spectator threads together and exits after.
- **Spectator thread**
  1. The spectator thread sleeps until the spectator reaches the stadium
  2. The spectator then creates a maximum of three threads [0-3] to help acquire a seat whose working is as follows:
     1. To acquire a seat of type 'X' where 'X' can be either HOME, NEUTRAL or AWAY, the worker thread first waits on the condition variable `searchingCV` which is signalled by the spectator thread when he wants his worker threads to start the searching process
     2. The worker thread then does a `timed_wait` on the semaphore of type 'X' (with the time limit set to the `patienceTime` of the spectator).
     3. If it fails to obtain a seat, the thread exits
     4. If not, then it obtains the `seatLock` of the spectator.
     5. If the `spectator->seatType` is not -1 then, that means that one of the other worker threads already found a seat in which case, the current worker thread posts the obtained seat and exits
     6. If not, then the current worker is the first one to find a valid seat and so, fills in the seat type 'X' in `spectator->seatType` and signals the condition variable `seatCV` on which the parent spectator is sleeping while waiting for his workers to finish
  3. The spectator does a `timed_wait` on the condition variable `seatCV` (with the time limit set to his `patienceTime`)
  4. After waking up, if the `seatType` is still -1, then that means that none of his worker threads found a valid seat, in which case the thread exits the simulation failing to find a seat in time
  5. If not, then the spectator having occupied his seat, spectates the match
  6. If the spectator is a neutral fan, then he sleeps for the duration of `spectatingTime` and exits the zone and goes to the gate
  7. If not, then the spectator `timed_wait`s on the condition variable `homeFans` or `awayFans` (for a duration of `spectatingTime`).
  8. He is woken up every time the opponent team scores a goal, checks whether the opponent team has scored more than or equal to his `goalLimit`. If so, then he leaves to the exit and the thread exits the simulation and if not, then he continues to spectate
  9. If he was woken up by the timer running out, then he leaves for the exit regardless of the opponents goals
- **Goal thread**
  1. It sleeps for duration of time in between two consecutive goal chances
  2. Then, with a some probability based on the `chance` the team either scores the goal in which case the corresponding condition variable (either `homeFans` or `awayFans`).
  3. If the team failed to score the goal, then the thread just continues without doing anything
  4. The above steps repeat until all the goal chances have been accounted for, after which the thread exits

**Note**
The simulation ends when all the group threads and the goal thread exits.
Bonus was implemented as specified :)

