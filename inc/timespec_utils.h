#ifndef TIMESPEC_UTILS_H
#define TIMESPEC_UTILS_H

#include<stdint.h>
#include<time.h>

#define MILLISECONDS_IN_SECOND          1000LL
#define MICROSECONDS_IN_SECOND          1000000LL
#define NANOSECONDS_IN_SECOND           1000000000LL
#define NANOSECONDS_IN_MILLISECOND      1000000LL
#define NANOSECONDS_IN_MICROSECOND      1000LL

static inline struct timespec timespec_from_seconds(uint64_t seconds);
static inline struct timespec timespec_from_milliseconds(uint64_t milliseconds);
static inline struct timespec timespec_from_microseconds(uint64_t microseconds);
static inline struct timespec timespec_from_nanoseconds(uint64_t nanoseconds);

static inline uint64_t timespec_to_seconds(struct timespec t);
static inline uint64_t timespec_to_milliseconds(struct timespec t);
static inline uint64_t timespec_to_microseconds(struct timespec t);
static inline uint64_t timespec_to_nanoseconds(struct timespec t);

static inline int timespec_compare(struct timespec t1, struct timespec t2);

static inline int timespec_is_zero(struct timespec t);

// t1 + t2 -> assumes no overflow
static inline struct timespec timespec_add(struct timespec t1, struct timespec t2);
// t1 - t2 -> asumes no underflow
static inline struct timespec timespec_sub(struct timespec t1, struct timespec t2);// this function assumesthat t1 > t3

static inline struct timespec timespec_from_seconds(uint64_t seconds)
{
	return struct timespec{
		.tv_sec = seconds,
		.tv_nsec = 0,
	};
}

static inline struct timespec timespec_from_milliseconds(uint64_t milliseconds)
{
	return struct timespec{
		.tv_sec = milliseconds / MILLISECONDS_IN_SECOND,
		.tv_nsec = (milliseconds % MILLISECONDS_IN_SECOND) * NANOSECONDS_IN_MILLISECOND,
	};
}

static inline struct timespec timespec_from_microseconds(uint64_t microseconds)
{
	return struct timespec{
		.tv_sec = microseconds / MICROSECONDS_IN_SECOND,
		.tv_nsec = (microseconds % MICROSECONDS_IN_SECOND) * NANOSECONDS_IN_MICROSECOND,
	};
}

static inline struct timespec timespec_from_nanoseconds(uint64_t nanoseconds)
{
	return struct timespec{
		.tv_sec = nanoseconds / NANOSECONDS_IN_SECOND,
		.tv_nsec = (nanoseconds % NANOSECONDS_IN_SECOND),
	};
}

static inline uint64_t timespec_to_seconds(struct timespec t)
{
	return t.tv_sec;
}

static inline uint64_t timespec_to_milliseconds(struct timespec t)
{
	return t.tv_sec * MILLISECONDS_IN_SECOND + t.tv_nsec / NANOSECONDS_IN_MILLISECOND;
}

static inline uint64_t timespec_to_microseconds(struct timespec t)
{
	return t.tv_sec * MICROSECONDS_IN_SECOND + t.tv_nsec / NANOSECONDS_IN_MICROSECOND;
}

static inline uint64_t timespec_to_nanoseconds(struct timespec t)
{
	return t.tv_sec * NANOSECONDS_IN_SECOND + t.tv_nsec;
}

static inline int timespec_compare(struct timespec t1, struct timespec t2)
{
	if(t1.tv_sec != t2.tv_sec)
		return compare_numbers(t1.tv_sec, t2.tv_sec);
	return compare_numbers(t1.tv_nsec, t2.tv_nsec);
}

static inline int timespec_is_zero(struct timespec t)
{
	return t.tv_sec == 0 && t.tv_nsec == 0;
}

#endif