#ifndef PTHREAD_COND_UTILS_H
#define PTHREAD_COND_UTILS_H

#include<stdint.h>
#include<pthread.h>

// inits a pthread_cond_t with a CLOCK_MONOTONIC
static inline int pthread_cond_init_with_monotonic_clock(pthread_cond_t *cond);

// below functions can be used to performed a timedwait on a condition variable for a duration given as its last parameter
// below functions assume that the condition variable is initialized with CLOCK_MONOTONIC, possibly using the above function (pthread_cond_init_with_monotonic_clock)
static inline int pthread_cond_timedwait_for_timespec(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, struct timespec* duration);
static inline int pthread_cond_timedwait_for_seconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_seconds);
static inline int pthread_cond_timedwait_for_milliseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_milliseconds);
static inline int pthread_cond_timedwait_for_microseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_microseconds);
static inline int pthread_cond_timedwait_for_nanoseconds(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_nanoseconds);

static inline int pthread_cond_init_with_monotonic_clock(pthread_cond_t *cond)
{
	pthread_condattr_t attr;
	pthread_cond_condattr_init(&attr);

	pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);

	int result = pthread_cond_init(cond, &attr);

	pthread_cond_condattr_destroy(&attr);

	return result;
}

#endif