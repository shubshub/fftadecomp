#include "ffta.h"

typedef struct {
    u16 first;
    u16 second;
    u8 kind;
    u8 flags;
    u8 mode;
    u16 start;
    u16 end;
    void *value;
} TaskParameters08116480;

typedef struct {
    u16 phase;
    u16 unknown_02;
    TaskParameters08116480 *parameters;
    u32 unknown_08[5];
} TaskRequest08116480;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern u32 func_081160E4(void *task, void *request, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                          void *request, void *parent);

void *func_08116480(u8 kind, u16 first, u16 second, u8 flags,
                     u8 mode, u16 start, u16 end, void *value,
                     void *parent)
{
    TaskRequest08116480 request;
    TaskParameters08116480 parameters;

    parameters.kind = kind;
    parameters.first = first;
    parameters.second = second;
    parameters.flags = flags;
    parameters.mode = mode;
    parameters.start = start;
    parameters.end = end;
    parameters.value = value;
    request.parameters = &parameters;
    return func_08005B6C(func_081160E4, 0x38, &request, parent);
}
