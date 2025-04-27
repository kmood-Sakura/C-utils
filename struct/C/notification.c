#include "../notification.h"

#include <stdio.h>
#include <stdlib.h>

error allocateNotification(Notification** notification) {
    if (notification == NULL) {
        return "Notification pointer is required"; // Invalid notification pointer
    }
    if (*notification != NULL) {
        return NULL; // Invalid notification pointer
    }

    *notification = (Notification*)malloc(sizeof(Notification));
    if (*notification == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*notification)->header = NULL; // Initialize header
    (*notification)->title = NULL; // Initialize title

    DateTime set = {0}; // Initialize set
    (*notification)->dueDate = set; // Initialize dueDate

    return NULL; // Success
}

error allocateNotificationList(NotificationList** notificationList) {
    if (notificationList == NULL) {
        return "NotificationList pointer is required"; // Invalid notification list pointer
    }
    if (*notificationList != NULL) {
        return NULL; // Invalid notification list pointer
    }

    *notificationList = (NotificationList*)malloc(sizeof(NotificationList));
    if (*notificationList == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }
    (*notificationList)->next = NULL; // Initialize next
    (*notificationList)->prev = NULL; // Initialize prev

    return NULL; // Success
}

error createNotification(Notification* notification, const string header, const string title, DateTime dueDate) {
    if (notification == NULL) {
        return "Notification pointer is required"; // Invalid notification pointer
    }
    if (header == NULL || title == NULL) {
        return "Header and title are required"; // Invalid parameters
    }

    error err = NULL;
    err = allocateString(&notification->header, header); // Allocate memory for header
    if (err != NULL) {
        return err; // Memory allocation failed
    }

    err = allocateString(&notification->title, title); // Allocate memory for title
    if (err != NULL) {
        FreeString(&notification->header); // Free header
        return err; // Memory allocation failed
    }
    
    notification->dueDate = dueDate; // Copy dueDate

    return NULL; // Success
}

error createNotificationListNode(NotificationList** node, Notification notification) {
    if (*node != NULL) {
        return "NotificationList node pointer must be NULL"; // Invalid notification list node pointer
    }

    *node = (NotificationList*)malloc(sizeof(NotificationList));
    if (*node == NULL) {
        return "Memory allocation failed"; // Memory allocation failed
    }

    (*node)->notification = notification; // Copy notification
    (*node)->next = NULL; // Initialize next
    (*node)->prev = NULL; // Initialize prev

    return NULL; // Success
}

error addNotificationToList(NotificationList** head, Notification notification) {
    if (head == NULL) {
        return "Notification list head pointer is required"; // Invalid notification list head pointer
    }

    NotificationList* newNode = NULL;
    error err = createNotificationListNode(&newNode, notification); // Create a new notification list node
    if (err != NULL) {
        return err; // Memory allocation failed
    }

    if (*head == NULL) {
        *head = newNode;
    }

    NotificationList* current = *head;
    while(current->next != NULL) {
        current = current->next; // Traverse to the end of the list
    }

    current->next = newNode; // Add the new node at the end of the list
    newNode->prev = current; // Set the previous pointer of the new node
    return NULL; // Success
}

void FreeNotificationContent(Notification* notification) {
    if (notification == NULL) {
        return; // Invalid notification pointer
    }
    if (notification->header != NULL) {
        FreeString(&notification->header); // Free header string
    }
    if (notification->title != NULL) {
        FreeString(&notification->title); // Free title string
    }
    DateTime set = {0};
    notification->dueDate = set; // Reset dueDate
}

void FreeNotification(Notification* notification) {
    if (notification == NULL) {
        return; // Invalid notification pointer
    }
    FreeNotificationContent(notification); // Free notification content
    free(notification); // Free the notification structure
}

void FreeNotificationList(NotificationList* notificationList) {
    if (notificationList == NULL) return;

    NotificationList* current = notificationList->next;
    while (current != NULL) {
        NotificationList* temp = current;
        current = current->next; // Move to the next node
        FreeNotificationContent(&temp->notification); // Free notification content
        free(temp); // Free the node
    }
    
    current = notificationList->prev;
    while (current != NULL) {
        NotificationList* temp = current;
        current = current->prev; // Move to the previous node
        FreeNotificationContent(&temp->notification); // Free notification
        free(temp); // Free the node
    }

    FreeNotificationContent(&notificationList->notification); // Free the head notification
    free(notificationList); // Free the notification list structure
}