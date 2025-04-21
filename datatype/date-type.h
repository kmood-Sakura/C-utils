#ifndef DATE_TYPE_H
#define DATE_TYPE_H

#include "int-type.h"
#include <time.h>

typedef time_t DateTime; // time_t is typically a 64-bit integer representing seconds since the epoch (1970-01-01 00:00:00 UTC)

typedef struct DateTimeInfo {
    uint16 year;  // 1900-2100
    uint8 month; // 1-12
    uint8 day;   // 1-31
    uint8 hour;  // 0-23
    uint8 minute;// 0-59
    uint8 second;// 0-59
    uint8 utc; // UTC offset in hours
} DateTimeInfo;

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
// time : "YYYYMMDDHHMMSSmmm"

// for handle struct tm
typedef struct Time {
    uint16 year;  // 1900-2100
    uint8 month; // 1-12
    uint8 day;   // 1-31
    uint8 hour;  // 0-23
    uint8 minute;// 0-59
    uint8 second;// 0-59
    uint16 millisecond; // 0-999
} Time;

typedef uint64 TimeValue; // YYYYMMDDHHMMSSmmm

/* Format Definitions */
#define DATE_LOG_FORMAT "%04hu-%02hhu-%02hhu\n"
#define CLOCK_LOG_FORMAT "%02hhu:%02hhu:%02hhu\n"
#define TIME_LOG_FORMAT "%d-%d-%d %d:%d:%d.%d\n"
#define DATETIME_LOG_FORMAT "%d-%d-%d %d:%d:%d UTC+%d\n"
#define TIMEVALUE_LOG_FORMAT "%d%d%d%d%d%d%d\n" // YYYYMMDDHHMMSSmmm
#define KID_TIME_LOG_FORMAT "Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d\n"

#define DATE_FORMAT "%d-%d-%d" // YYYY-MM-DD
#define CLOCK_FORMAT "%d:%d:%d" // HH:MM:SS
#define TIME_FORMAT "%d-%d-%d %d:%d:%d.%d" // YYYY-MM-DD HH:MM:SS.mmm
#define DATETIME_FORMAT "%d-%d-%d %d:%d:%d UTC+%d" // YYYY-MM-DD HH:MM:SS UTC+X
#define TIMEVALUE_FORMAT "%d%d%d%d%d%d%d" // YYYYMMDDHHMMSSmmm

/* Function Declarations */

/* Log Functions */
void logDate(const Date* date);
void logClock(const Clock* clock);
void logTime(const Time* time);
void logDateTimeInfo(const DateTimeInfo* info);
void logTimeValue(TimeValue value);
void logDateTime(DateTime dateTime);

/* DateTime Retrieval Functions */
DateTime getCurrentDateTime(void);
DateTime getDateTimeFromComponents(uint16 year, uint8 month, uint8 day, 
                                  uint8 hour, uint8 minute, uint8 second);

/* Data Type Conversion Functions */
Date* dateTimeToDate(DateTime dt);
Clock* dateTimeToClock(DateTime dt);
Time* dateTimeToTime(DateTime dt);
DateTimeInfo* dateTimeToDateTimeInfo(DateTime dt);

/* Memory Management Functions */
void freeDate(Date* date);
void freeClock(Clock* clock);
void freeTime(Time* time);
void freeDateTimeInfo(DateTimeInfo* info);

/* Time Functions */
Time* createTime(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 minute, uint8 second, uint16 millisecond);
Time* getCurrentTime(void);
Time* copyTime(const Time* time);

/* Date Functions */
Date* createDate(uint8 day, uint8 month, uint16 year);
Date* getCurrentDate(void);
Date* copyDate(const Date* date);

/* Clock Functions */
Clock* createClock(uint8 hour, uint8 minute, uint8 second);
Clock* getCurrentClock(void);
Clock* copyClock(const Clock* clock);

/* DateTimeInfo Functions */
DateTimeInfo* createDateTimeInfo(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 minute, uint8 second, uint8 utc);
DateTimeInfo* getCurrentDateTimeInfo(void);
DateTimeInfo* copyDateTimeInfo(const DateTimeInfo* info);

/* TimeValue Functions */
TimeValue createTimeValue(uint16 year, uint8 month, uint8 day, 
                        uint8 hour, uint8 minute, uint8 second, uint16 millisecond);
TimeValue getCurrentTimeValue(void);
TimeValue timeToTimeValue(const Time* time);
Time* timeValueToTime(TimeValue value);

/* String Conversion Functions */
char* dateToString(const Date* date);
char* clockToString(const Clock* clock);
char* timeToString(const Time* time);
char* dateTimeInfoToString(const DateTimeInfo* info);
char* timeValueToString(TimeValue value);
char* dateTimeToString(DateTime dt);

#endif // DATE_TYPE_H