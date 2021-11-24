#ifndef PARALLELISM_WRAPPER_H
#define PARALLELISM_WRAPPER_H

#include <pthread.h>

int Pthread_create(pthread_t *nt, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int Pthread_join(pthread_t thread, void **retval);
int Pthread_cancel(pthread_t thread);
int Pthread_mutex_lock(pthread_mutex_t *p);
int Pthread_mutex_unlock(pthread_mutex_t *p);
int Pthread_mutex_init(pthread_mutex_t *p, const pthread_mutexattr_t *ptr);
int Pthread_cond_init(pthread_cond_t *p, const pthread_condattr_t *ptr);
int Pthread_cond_signal(pthread_cond_t *p);
int Pthread_cond_broadcast(pthread_cond_t *p);
int Pthread_cond_wait(pthread_cond_t *p, pthread_mutex_t *x);
int Pthread_cond_timedwait(pthread_cond_t *p, pthread_mutex_t *x, const struct timespec* t);

#endif //PARALLELISM_WRAPPER_H
