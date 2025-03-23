#include<stdio.h>

#include<timespec_utils.h>
#include<pthread_cond_utils.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c;

#define SECS  0
#define MSECS 1
#define USECS 2
#define NSECS 3

void time_and_wait(uint64_t duration, int unit)
{
	// get time before waiting
	struct timespec before_wait;
	clock_gettime(CLOCK_MONOTONIC, &before_wait);

	pthread_mutex_lock(&m);

	switch(unit)
	{
		default:
		case SECS:
		{
			printf("%"PRIu64" waiting for secs\n", duration);
			pthread_cond_timedwait_for_seconds(&c, &m, &duration);
			break;
		}
		case MSECS:
		{
			printf("%"PRIu64" waiting for millisecs\n", duration);
			pthread_cond_timedwait_for_milliseconds(&c, &m, &duration);
			break;
		}
		case USECS:
		{
			printf("%"PRIu64" waiting for microsecs\n", duration);
			pthread_cond_timedwait_for_microseconds(&c, &m, &duration);
			break;
		}
		case SECS:
		{
			printf("%"PRIu64" waiting for nanosecs\n", duration);
			pthread_cond_timedwait_for_nanoseconds(&c, &m, &duration);
			break;
		}
	}

	pthread_mutex_unlock(&m);

	// get time after the wait completes
	struct timespec after_wait;
	clock_gettime(CLOCK_MONOTONIC, &after_wait);

	// calculate time we waited for
	// we are sure that after_wait > before_wait, as we are using CLOCK_MONOTONIC
	const struct timespec waited_for = timespec_sub(after_wait, before_wait);

	printf("waited_for => %ld.%09ld\n\n", waited_for.tv_sec, waited_for.tv_nsec);
}

int main()
{
	pthread_cond_init_with_monotonic_clock(&c);

	time_and_wait(1, SECS);
	time_and_wait(1, MSECS);
	time_and_wait(1, USECS);
	time_and_wait(1, NSECS);

	time_and_wait(250, SECS);
	time_and_wait(250, MSECS);
	time_and_wait(250, USECS);
	time_and_wait(250, NSECS);

	time_and_wait(5, SECS);
	time_and_wait(2000, MSECS);
	time_and_wait(1000000, USECS);
	time_and_wait(1000000, NSECS);

	return 0;
}