#include "../date-type.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

error getCurrentDateTime(DateTime* dateTime) {
    if (dateTime == NULL) {
        return "dateTime pointer is NULL";
    }
    
    *dateTime = time(NULL);
    return NULL;
}

void logDate(const Date* date) {
    if (date == NULL) {
        printf("Date: NULL\n");
        return;
    }
    printf("Date: ");
    printf(DATE_LOG_FORMAT, date->year, date->month, date->day);
}

void logClock(const Clock* clock) {
    if (clock == NULL) {
        printf("Clock: NULL\n");
        return;
    }
    printf("Clock: ");
    printf(CLOCK_LOG_FORMAT, clock->hour, clock->minute, clock->second);
}

void logTime(const Time* time) {
    if (time == NULL) {
        printf("Time: NULL\n");
        return;
    }
    printf("Time: ");
    printf(TIME_LOG_FORMAT, time->year, time->month, time->day,
           time->hour, time->minute, time->second, time->millisecond);
}

void logDateTimeInfo(const DateTimeInfo* info) {
    if (info == NULL) {
        printf("DateTimeInfo: NULL\n");
        return;
    }
    
    printf("DateTimeInfo: ");
    printf(DATETIME_LOG_FORMAT, info->year, info->month, info->day,
           info->hour, info->minute, info->second, info->utc);
}

void logTimeValue(TimeValue value) {
    uint16 ms = value % 1000;
    value /= 1000;
    uint8 sec = value % 100;
    value /= 100;
    uint8 min = value % 100;
    value /= 100;
    uint8 hour = value % 100;
    value /= 100;
    uint8 day = value % 100;
    value /= 100;
    uint8 month = value % 100;
    value /= 100;
    uint16 year = value;
    
    printf("TimeValue: ");
    printf(TIMEVALUE_LOG_FORMAT, year, month, day, hour, min, sec, ms);
}

void logDateTime(DateTime dateTime) {
    char buffer[64];
    struct tm* timeInfo = localtime(&dateTime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    printf("DateTime: %s (%lld)\n", buffer, (long long)dateTime);
}

void freeDate(Date* date) {
    if (date != NULL) {
        free(date);
    }
}

void freeClock(Clock* clock) {
    if (clock != NULL) {
        free(clock);
    }
}

void freeTime(Time* time) {
    if (time != NULL) {
        free(time);
    }
}

void freeDateTimeInfo(DateTimeInfo* info) {
    if (info != NULL) {
        free(info);
    }
}

error dateToString(string* str, const Date* date) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (date == NULL) {
        return "date is NULL";
    }
    
    *str = (string)malloc(12 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    sprintf(*str, DATE_FORMAT, date->year, date->month, date->day);
    return NULL;
}

error clockToString(string* str, const Clock* clock) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (clock == NULL) {
        return "clock is NULL";
    }
    
    *str = (string)malloc(10 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    sprintf(*str, CLOCK_FORMAT, clock->hour, clock->minute, clock->second);
    return NULL;
}

error timeToString(string* str, const Time* time) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (time == NULL) {
        return "time is NULL";
    }
    
    *str = (string)malloc(30 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    sprintf(*str, TIME_FORMAT, 
            time->year, time->month, time->day,
            time->hour, time->minute, time->second,
            time->millisecond);
    
    return NULL;
}

error dateTimeInfoToString(string* str, const DateTimeInfo* info) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    if (info == NULL) {
        return "info is NULL";
    }
    
    *str = (string)malloc(35 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    sprintf(*str, DATETIME_FORMAT, 
            info->year, info->month, info->day,
            info->hour, info->minute, info->second,
            info->utc);
    
    return NULL;
}

error timeValueToString(string* str, TimeValue value) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    *str = (string)malloc(20 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    uint16 ms = value % 1000;
    value /= 1000;
    uint8 sec = value % 100;
    value /= 100;
    uint8 min = value % 100;
    value /= 100;
    uint8 hour = value % 100;
    value /= 100;
    uint8 day = value % 100;
    value /= 100;
    uint8 month = value % 100;
    value /= 100;
    uint16 year = value;
    
    sprintf(*str, TIMEVALUE_FORMAT, 
            year, month, day, hour, min, sec, ms);
    
    return NULL;
}

DateTime makeDateTime(Date date, int hour, int minute) {
    struct tm tm_time = {0};
    tm_time.tm_year = date.year - 1900;
    tm_time.tm_mon = date.month - 1;
    tm_time.tm_mday = date.day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = minute;
    tm_time.tm_sec = 0;

    return mktime(&tm_time);
}

code isSameDate(const Date* d1, const Date* d2) {
    if (d1 == NULL || d2 == NULL) return 0;
    return (d1->year == d2->year) &&
           (d1->month == d2->month) &&
           (d1->day == d2->day);
}

error dateTimeToString(string* str, DateTime dt) {
    if (str == NULL) {
        return "string pointer is NULL";
    }
    
    if (*str != NULL) {
        return "string already allocated";
    }
    
    *str = (string)malloc(20 * sizeof(char));
    if (*str == NULL) {
        return "memory allocation failed";
    }
    
    struct tm* timeInfo = localtime(&dt);
    strftime(*str, 20, "%Y-%m-%d %H:%M:%S", timeInfo);
    
    return NULL;
}

error stringToDate(Date** date, const string str) {
    if (date == NULL) {
        return "date pointer is NULL";
    }
    
    if (*date != NULL) {
        return "date already allocated";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    uint16 year;
    uint8 month, day;
    
    if (sscanf(str, "%hu-%hhu-%hhu", &year, &month, &day) != 3) {
        return "invalid date format, expected YYYY-MM-DD";
    }
    
    if (month < 1 || month > 12) {
        return "invalid month value";
    }
    
    uint8 maxDays = 31;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    }
    
    if (day < 1 || day > maxDays) {
        return "invalid day value for this month/year";
    }
    
    *date = (Date*)malloc(sizeof(Date));
    if (*date == NULL) {
        return "memory allocation failed";
    }
    
    (*date)->day = day;
    (*date)->month = month;
    (*date)->year = year;
    
    return NULL;
}

error stringToClock(Clock** clock, const string str) {
    if (clock == NULL) {
        return "clock pointer is NULL";
    }
    
    if (*clock != NULL) {
        return "clock already allocated";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    uint8 hour, minute, second;
    
    if (sscanf(str, "%hhu:%hhu:%hhu", &hour, &minute, &second) != 3) {
        return "invalid clock format, expected HH:MM:SS";
    }
    
    if (hour > 23 || minute > 59 || second > 59) {
        return "invalid time value";
    }
    
    *clock = (Clock*)malloc(sizeof(Clock));
    if (*clock == NULL) {
        return "memory allocation failed";
    }
    
    (*clock)->hour = hour;
    (*clock)->minute = minute;
    (*clock)->second = second;
    
    return NULL;
}

error stringToTime(Time** time, const string str) {
    if (time == NULL) {
        return "time pointer is NULL";
    }
    
    if (*time != NULL) {
        return "time already allocated";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    uint16 year, millisecond;
    uint8 month, day, hour, minute, second;
    
    if (sscanf(str, "%hu-%hhu-%hhu %hhu:%hhu:%hhu.%hu", 
              &year, &month, &day, &hour, &minute, &second, &millisecond) != 7) {
        return "invalid time format, expected YYYY-MM-DD HH:MM:SS.mmm";
    }
    
    if (month < 1 || month > 12) {
        return "invalid month value";
    }
    
    uint8 maxDays = 31;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    }
    
    if (day < 1 || day > maxDays) {
        return "invalid day value for this month/year";
    }
    
    if (hour > 23 || minute > 59 || second > 59 || millisecond > 999) {
        return "invalid time component";
    }
    
    *time = (Time*)malloc(sizeof(Time));
    if (*time == NULL) {
        return "memory allocation failed";
    }
    
    (*time)->year = year;
    (*time)->month = month;
    (*time)->day = day;
    (*time)->hour = hour;
    (*time)->minute = minute;
    (*time)->second = second;
    (*time)->millisecond = millisecond;
    
    return NULL;
}

error stringToDateTimeInfo(DateTimeInfo** info, const string str) {
    if (info == NULL) {
        return "info pointer is NULL";
    }
    
    if (*info != NULL) {
        return "info already allocated";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    uint16 year;
    uint8 month, day, hour, minute, second, utc;
    
    if (sscanf(str, "%hu-%hhu-%hhu %hhu:%hhu:%hhu UTC+%hhu", 
              &year, &month, &day, &hour, &minute, &second, &utc) != 7) {
        return "invalid format, expected YYYY-MM-DD HH:MM:SS UTC+X";
    }
    
    if (month < 1 || month > 12) {
        return "invalid month value";
    }
    
    uint8 maxDays = 31;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    }
    
    if (day < 1 || day > maxDays) {
        return "invalid day value for this month/year";
    }
    
    if (hour > 23 || minute > 59 || second > 59 || utc > 12) {
        return "invalid time component";
    }
    
    *info = (DateTimeInfo*)malloc(sizeof(DateTimeInfo));
    if (*info == NULL) {
        return "memory allocation failed";
    }
    
    (*info)->year = year;
    (*info)->month = month;
    (*info)->day = day;
    (*info)->hour = hour;
    (*info)->minute = minute;
    (*info)->second = second;
    (*info)->utc = utc;
    
    return NULL;
}

error stringToTimeValue(TimeValue* value, const string str) {
    if (value == NULL) {
        return "value pointer is NULL";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    uint16 year, millisecond;
    uint8 month, day, hour, minute, second;
    
    if (sscanf(str, "%4hu%2hhu%2hhu%2hhu%2hhu%2hhu%3hu", 
              &year, &month, &day, &hour, &minute, &second, &millisecond) != 7) {
        return "invalid format, expected YYYYMMDDHHMMSSmmm";
    }
    
    if (month < 1 || month > 12) {
        return "invalid month value";
    }
    
    uint8 maxDays = 31;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    }
    
    if (day < 1 || day > maxDays) {
        return "invalid day value for this month/year";
    }
    
    if (hour > 23 || minute > 59 || second > 59 || millisecond > 999) {
        return "invalid time component";
    }
    
    *value = (TimeValue)year * 10000000000ULL +
             (TimeValue)month * 100000000ULL +
             (TimeValue)day * 1000000ULL +
             (TimeValue)hour * 10000ULL +
             (TimeValue)minute * 100ULL +
             (TimeValue)second +
             (TimeValue)millisecond / 1000.0;
    
    return NULL;
}

error stringToDateTime(DateTime* dt, const string str) {
    if (dt == NULL) {
        return "dateTime pointer is NULL";
    }
    
    if (str == NULL) {
        return "string is NULL";
    }
    
    struct tm tm_time = {0};
    uint16 year;
    uint8 month, day, hour, minute, second;
    
    if (sscanf(str, "%hu-%hhu-%hhu %hhu:%hhu:%hhu", 
               &year, &month, &day, &hour, &minute, &second) != 6) {
        return "invalid format, expected YYYY-MM-DD HH:MM:SS";
    }
    
    tm_time.tm_year = year - 1900;  // Years since 1900
    tm_time.tm_mon = month - 1;     // Month (0-11)
    tm_time.tm_mday = day;          // Day of month (1-31)
    tm_time.tm_hour = hour;         // Hours (0-23)
    tm_time.tm_min = minute;        // Minutes (0-59)
    tm_time.tm_sec = second;        // Seconds (0-59)
    
    *dt = mktime(&tm_time);
    if (*dt == (time_t)-1) {
        return "failed to convert to DateTime";
    }
    
    return NULL; // Success
}