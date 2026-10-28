#include "ffta.h"

typedef struct DmaRequest {
    u8 enabled;
    u8 channel;
    u16 unknown_02;
    const void *source;
    void *destination;
    u32 control;
    u16 interval;
    u16 progress;
    u16 repetitions;
    u16 unknown_16;
    struct DmaRequest *next;
} DmaRequest;

extern DmaRequest *data_03002BCC;

/* 08000CB8..08000D08: 80 bytes. */
void func_08000CB8(DmaRequest *request, const void *source, void *destination,
                   u16 count, u16 interval, u16 repetitions)
{
    request->enabled = 1;
    request->channel = 3;
    request->source = source;
    request->destination = destination;
    request->control = count | 0x85000000;
    request->interval = interval;
    request->progress = 0;
    request->repetitions = repetitions;
    request->next = 0;

    if (data_03002BCC == 0) {
        data_03002BCC = request;
    } else {
        DmaRequest *current = data_03002BCC;
        while (current->next != 0)
            current = current->next;
        current->next = request;
    }
}
