#ifndef PTHREAD_COND_UTILS_H
#define PTHREAD_COND_UTILS_H

#include<stdint.h>
#include<pthread.h>

#include<timespec_utils.h>

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

int pthread_cond_timedwait_for_timespec(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, struct timespec* duration)
{
	// get time before waiting
	struct timespec before_wait;
	clock_gettime(CLOCK_MONOTONIC, &before_wait);

	int result;
	{
		const struct timespec wait_until = timespec_add(before_wait, *duration);
		result = pthread_cond_timedwait(cond, mutex, &wait_until);
	}

	// get time after the wait completes
	struct timespec after_wait;
	clock_gettime(CLOCK_MONOTONIC, &after_wait);

	// calculate time we waited for
	// we are sure that after_wait > before_wait, as we are using CLOCK_MONOTONIC
	const struct timespec waited_for = timespec_sub(after_wait, before_wait);

	// remove the duration that we waited for from the duration
	if(timespec_compare(waited_for, *duration) > 0) // if we for some reason waited for more than the duration
		(*duration) = (struct timespec){};
	else
		(*duration) = timespec_sub(*duration, waited_for);

	return result;
}

#define pthread_cond_timedwait_for_(unit)                                                                                                                  \
static inline int pthread_cond_timedwait_for_ ## unit (pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, uint64_t* duration_ ## unit)        \
{                                                                                                                                                          \
	struct timespec duration = timespec_from_ ## unit(*duration_ ## unit);                                                                                 \
                                                                                                                                                           \
	int result = pthread_cond_timedwait_for_timespec(cond, mutex, &duration);                                                                              \
                                                                                                                                                           \
	(*duration_ ## unit) = timespec_to_ ## unit(duration);                                                                                                 \
                                                                                                                                                           \
	return result;                                                                                                                                         \
}                                                                                                                                                          \
// new line break here

pthread_cond_timedwait_for_(seconds)
pthread_cond_timedwait_for_(milliseconds)
pthread_cond_timedwait_for_(microseconds)
pthread_cond_timedwait_for_(nanoseconds)

#endif