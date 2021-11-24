#include <assert.h>
#include "wrapper.h"

int Pthread_create(pthread_t *nt, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
    int rc = pthread_create(nt, attr, start_routine, arg);
    assert(rc == 0);
    return 0;
}

int Pthread_join(pthread_t thread, void **retval) {
    int rc = pthread_join(thread, retval);
    assert(rc == 0);
    return 0;
}

int Pthread_cancel(pthread_t thread) {
    int rc = pthread_cancel(thread);
    assert(rc == 0);
    return 0;
}

int Pthread_mutex_lock(pthread_mutex_t *p) {
    int rc = pthread_mutex_lock(p);
    assert(rc == 0);
    return 0;
}

int Pthread_mutex_unlock(pthread_mutex_t *p) {
    int rc = pthread_mutex_unlock(p);
    assert(rc == 0);
    return 0;
}

int Pthread_mutex_init(pthread_mutex_t *p, const pthread_mutexattr_t *ptr) {
    int rc = pthread_mutex_init(p, ptr);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_init(pthread_cond_t *p, const pthread_condattr_t *ptr) {
    int rc = pthread_cond_init(p, ptr);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_signal(pthread_cond_t *p) {
    int rc = pthread_cond_signal(p);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_broadcast(pthread_cond_t *p) {
    int rc = pthread_cond_broadcast(p);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_wait(pthread_cond_t *p, pthread_mutex_t *x) {
    int rc = pthread_cond_wait(p, x);
    assert(rc == 0);
    return 0;
}

int Pthread_cond_timedwait(pthread_cond_t *p, pthread_mutex_t *x, const struct timespec* t) {
    int rc = pthread_cond_timedwait(p, x, t);
    assert(rc == 0);
    return 0;
}
