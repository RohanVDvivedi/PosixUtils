#ifndef TIMESPEC_UTILS_H
#define TIMESPEC_UTILS_H

#include<stdint.h>
#include<time.h>

static inline struct timespec timespec_from_seconds(uint64_t seconds);
static inline struct timespec timespec_from_milliseconds(uint64_t milliseconds);
static inline struct timespec timespec_from_microseconds(uint64_t microseconds);
static inline struct timespec timespec_from_nanoseconds(uint64_t nanoseconds);

static inline uint64_t timespec_to_seconds(struct timespec t);
static inline uint64_t timespec_to_milliseconds(struct timespec t);
static inline uint64_t timespec_to_microseconds(struct timespec t);
static inline uint64_t timespec_to_nanoseconds(struct timespec t);

// t1 + t2 -> assumes no overflow
static inline struct timespec timespec_add(struct timespec t1, struct timespec t2);
// t1 - t2 -> asumes no underflow
static inline struct timespec timespec_sub(struct timespec t1, struct timespec t2);// this function assumesthat t1 > t3

static inline int timespec_compare(struct timespec t1, struct timespec t2);

#endif