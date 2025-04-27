#ifndef DATE_TYPE_H
#define DATE_TYPE_H

#include "../common/status.h"

#include "string-type.h"
#include "int-type.h"
#include <time.h>

/**
 * Custom date and time types and functions for time manipulation
 */

/* Type definitions */
typedef uint64 TimeValue;
typedef time_t DateTime;

/* Structs */
typedef struct Date {
    uint8 day;   // 1-31
    uint8 month; // 1-12
    uint16 year; // 1900-2100
} Date;

typedef struct Clock {
    uint8 hour;  // 0-23
    uint8 minute;// 0-59
    uint8 second;// 0-59
} Clock;

typedef struct Time {
    uint16 year;  // 1900-2100
    uint8 month; // 1-12
    uint8 day;   // 1-31
    uint8 hour;  // 0-23
    uint8 minute;// 0-59
    uint8 second;// 0-59
    uint16 millisecond; // 0-999
} Time;

typedef struct DateTimeInfo {
    uint16 year;  // 1900-2100
    uint8 month; // 1-12
    uint8 day;   // 1-31
    uint8 hour;  // 0-23
    uint8 minute;// 0-59
    uint8 second;// 0-59
    uint8 utc; // UTC offset in hours
} DateTimeInfo;

/* Format strings */
#define DATE_FORMAT "%04hu-%02hhu-%02hhu" // YYYY-MM-DD
#define CLOCK_FORMAT "%02hhu:%02hhu:%02hhu" // HH:MM:SS
#define TIME_FORMAT "%04hu-%02hhu-%02hhu %02hhu:%02hhu:%02hhu.%03hu" // YYYY-MM-DD HH:MM:SS.mmm
#define DATETIME_FORMAT "%04hu-%02hhu-%02hhu %02hhu:%02hhu:%02hhu UTC+%hhu" // YYYY-MM-DD HH:MM:SS UTC+X
#define TIMEVALUE_FORMAT "%04hu%02hhu%02hhu%02hhu%02hhu%02hhu%03hu" // YYYYMMDDHHMMSSmmm

/* Log format strings */
#define DATE_LOG_FORMAT "%04hu-%02hhu-%02hhu\n"
#define CLOCK_LOG_FORMAT "%02hhu:%02hhu:%02hhu\n"
#define TIME_LOG_FORMAT "%u-%u-%u %u:%u:%u.%u\n"
#define DATETIME_LOG_FORMAT "%u-%u-%u %u:%u:%u UTC+%u\n"
#define TIMEVALUE_LOG_FORMAT "%u%u%u%u%u%u%u\n" // YYYYMMDDHHMMSSmmm
#define KID_TIME_LOG_FORMAT "Year: %u, Month: %u, Day: %u, Hour: %u, Minute: %u, Second: %u\n"

/**
 * Get the current date and time
 * 
 * @param dateTime Pointer to store the result
 * @return NULL on success, error message on failure
 */
error getCurrentDateTime(DateTime* dateTime);

/**
 * Log Functions
 */
void logDate(const Date* date);
void logClock(const Clock* clock);
void logTime(const Time* time);
void logDateTimeInfo(const DateTimeInfo* info);
void logTimeValue(TimeValue value);
void logDateTime(DateTime dateTime);

/**
 * Memory Management Functions
 */
void freeDate(Date* date);
void freeClock(Clock* clock);
void freeTime(Time* time);
void freeDateTimeInfo(DateTimeInfo* info);

/**
 * Convert a Date structure to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param date Date structure to convert
 * @return NULL on success, error message on failure
 */
error dateToString(string* str, const Date* date);

/**
 * Convert a Clock structure to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param clock Clock structure to convert
 * @return NULL on success, error message on failure
 */
error clockToString(string* str, const Clock* clock);

/**
 * Convert a Time structure to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param time Time structure to convert
 * @return NULL on success, error message on failure
 */
error timeToString(string* str, const Time* time);

/**
 * Convert a DateTimeInfo structure to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param info DateTimeInfo structure to convert
 * @return NULL on success, error message on failure
 */
error dateTimeInfoToString(string* str, const DateTimeInfo* info);

/**
 * Convert a TimeValue to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param value TimeValue to convert
 * @return NULL on success, error message on failure
 */
error timeValueToString(string* str, TimeValue value);

/**
 * Convert a DateTime to a string
 * 
 * @param str Pointer to char pointer (should be NULL)
 * @param dt DateTime to convert
 * @return NULL on success, error message on failure
 */
error dateTimeToString(string* str, DateTime dt);

/**
 * Convert a string to a Date structure
 * 
 * @param date Pointer to Date pointer (should be NULL)
 * @param str String to convert (format: YYYY-MM-DD)
 * @return NULL on success, error message on failure
 */
error stringToDate(Date** date, const string str);

/**
 * Convert a string to a Clock structure
 * 
 * @param clock Pointer to Clock pointer (should be NULL)
 * @param str String to convert (format: HH:MM:SS)
 * @return NULL on success, error message on failure
 */
error stringToClock(Clock** clock, const string str);

/**
 * Convert a string to a Time structure
 * 
 * @param time Pointer to Time pointer (should be NULL)
 * @param str String to convert (format: YYYY-MM-DD HH:MM:SS.mmm)
 * @return NULL on success, error message on failure
 */
error stringToTime(Time** time, const string str);

/**
 * Convert a string to a DateTimeInfo structure
 * 
 * @param info Pointer to DateTimeInfo pointer (should be NULL)
 * @param str String to convert (format: YYYY-MM-DD HH:MM:SS UTC+X)
 * @return NULL on success, error message on failure
 */
error stringToDateTimeInfo(DateTimeInfo** info, const string str);

/**
 * Convert a string to a TimeValue
 * 
 * @param value Pointer to TimeValue to store the result
 * @param str String to convert (format: YYYYMMDDHHMMSSmmm)
 * @return NULL on success, error message on failure
 */
error stringToTimeValue(TimeValue* value, const string str);

/**
 * Convert a string to a DateTime
 * 
 * @param dt Pointer to DateTime to store the result
 * @param str String to convert (format: YYYY-MM-DD HH:MM:SS)
 * @return NULL on success, error message on failure
 */
error stringToDateTime(DateTime* dt, const string str);

#endif // DATE_TYPE_H