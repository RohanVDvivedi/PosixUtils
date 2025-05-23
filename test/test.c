#include<stdio.h>
#include<inttypes.h>

#include<posixutils/timespec_utils.h>
#include<posixutils/pthread_cond_utils.h>

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
		case NSECS:
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
	struct timespec t1 = {.tv_sec = 5, .tv_nsec = 234567890};

	{
		struct timespec t2 = {.tv_sec = 6, .tv_nsec = 789012345};
		printf("t2 => %ld.%09ld\n\n", t2.tv_sec, t2.tv_nsec);
		printf("t1 => %ld.%09ld\n\n", t1.tv_sec, t1.tv_nsec);
		struct timespec t_diff = timespec_sub(t2, t1);
		printf("Dt => %ld.%09ld\n\n", t_diff.tv_sec, t_diff.tv_nsec);
		struct timespec tf = timespec_add(t1, t_diff);
		printf("tf => %ld.%09ld\n\n", tf.tv_sec, tf.tv_nsec);
		printf("\n");
	}

	{
		struct timespec t2 = {.tv_sec = 6, .tv_nsec = 132569478};
		printf("t2 => %ld.%09ld\n\n", t2.tv_sec, t2.tv_nsec);
		printf("t1 => %ld.%09ld\n\n", t1.tv_sec, t1.tv_nsec);
		struct timespec t_diff = timespec_sub(t2, t1);
		printf("Dt => %ld.%09ld\n\n", t_diff.tv_sec, t_diff.tv_nsec);
		struct timespec tf = timespec_add(t1, t_diff);
		printf("tf => %ld.%09ld\n\n", tf.tv_sec, tf.tv_nsec);
		printf("\n");
	}

	{
		struct timespec t2 = {.tv_sec = 8, .tv_nsec = 789012345};
		printf("t2 => %ld.%09ld\n\n", t2.tv_sec, t2.tv_nsec);
		printf("t1 => %ld.%09ld\n\n", t1.tv_sec, t1.tv_nsec);
		struct timespec t_diff = timespec_sub(t2, t1);
		printf("Dt => %ld.%09ld\n\n", t_diff.tv_sec, t_diff.tv_nsec);
		struct timespec tf = timespec_add(t1, t_diff);
		printf("tf => %ld.%09ld\n\n", tf.tv_sec, tf.tv_nsec);
		printf("\n");
	}

	{
		struct timespec t2 = {.tv_sec = 8, .tv_nsec = 132569478};
		printf("t2 => %ld.%09ld\n\n", t2.tv_sec, t2.tv_nsec);
		printf("t1 => %ld.%09ld\n\n", t1.tv_sec, t1.tv_nsec);
		struct timespec t_diff = timespec_sub(t2, t1);
		printf("Dt => %ld.%09ld\n\n", t_diff.tv_sec, t_diff.tv_nsec);
		struct timespec tf = timespec_add(t1, t_diff);
		printf("tf => %ld.%09ld\n\n", tf.tv_sec, tf.tv_nsec);
		printf("\n");
	}

	pthread_cond_init_with_monotonic_clock(&c);

	time_and_wait(1, SECS);
	time_and_wait(1, MSECS);
	time_and_wait(1, USECS);
	time_and_wait(1, NSECS);

	time_and_wait(7, SECS);
	time_and_wait(250, MSECS);
	time_and_wait(250, USECS);
	time_and_wait(250, NSECS);

	time_and_wait(5, SECS);
	time_and_wait(2533, MSECS);
	time_and_wait(2533555, USECS);
	time_and_wait(2533555777, NSECS);

	return 0;
}