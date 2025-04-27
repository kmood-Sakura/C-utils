#ifndef NOTIFICATION_H 
#define NOTIFICATION_H

#include "../datatype/int-type.h"
#include "../datatype/string-type.h"
#include "../datatype/date-type.h"

typedef struct Notification {
    string header; // notification title
    string title; // notification message
    DateTime dueDate; // notification date and time
} Notification;

typedef struct NotificationList {
    Notification notification; // notification
    struct NotificationList* next; // next notification
    struct NotificationList* prev; // previous notification
} NotificationList;

error allocateNotification(Notification** notification);
error allocateNotificationList(NotificationList** notificationList);

error createNotification(Notification* notification, const string header, const string title, DateTime dueDate);
error createNotificationListNode(NotificationList** node, Notification notification);
error addNotificationToList(NotificationList** head, Notification notification);

void FreeNotificationContent(Notification* notification);
void FreeNotificationList(NotificationList* notificationList);

#endif // NOTIFICATION_H