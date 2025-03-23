#ifndef PTHREAD_COND_UTILS_H
#define PTHREAD_COND_UTILS_H

#include<pthread.h>

// inits a pthread_cond_t with a CLOCK_MONOTONIC
int pthread_cond_init_with_monotonic_clock(pthread_cond_t *cond, const pthread_condattr_t *attr);

// below functions can be used to performed a timedwait on a condition variable for a duration given as its last parameter
int pthread_cond_timedwait_for_timespec(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, struct timespec* duration);
int pthread_cond_timedwait_for_seconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_seconds);
int pthread_cond_timedwait_for_milliseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_milliseconds);
int pthread_cond_timedwait_for_microseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_microseconds);
int pthread_cond_timedwait_for_nanoseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_nanoseconds);

#endif