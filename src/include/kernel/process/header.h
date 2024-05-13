#ifndef _PROCESS_HEADER_H
#define _PROCESS_HEADER_H
typedef enum {
    CREATED,
    READY,
    RUNNING,
    BLOCKED,
    WAIT,
    TERMINATED,
    DIED,
} task_state;


#endif