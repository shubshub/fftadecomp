/* 0x080D989C: 56 target bytes, including the callback literal. */
#include "ffta.h"

typedef struct DisplayEvent {
    u16 state;
    u8 unknown_02[2];
    void *entries;
    u8 unknown_08[0x0c];
    u16 first;
    u16 second;
    u16 third;
} DisplayEvent;

typedef struct DisplayPayload DisplayPayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D9170(void *task, DisplayEvent *event, DisplayPayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D989C(u8 first, u8 second, u8 third, void *entries, void *parent)
{
    DisplayEvent descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.third = third;
    descriptor.entries = entries;
    return func_08005B6C((TaskCallback)func_080D9170, 0x1ac, &descriptor, parent);
}
