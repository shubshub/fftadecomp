#include "ffta.h"

typedef struct DmaRequest {
    u8 mode;
    u8 flags;
    u16 unknown_02;
    u32 source;
    void *destination;
    u32 control;
    u16 remaining;
    u16 source_step;
    u16 destination_step;
    u16 unknown_16;
    struct DmaRequest *next;
} DmaRequest;

extern DmaRequest *data_03002BCC;

/* 08000C64..08000CB8: 84 bytes, 39 instructions. */
void func_08000C64(DmaRequest *request, u16 value, void *destination,
                   u16 count, u16 remaining, u16 destination_step)
{
    request->mode = 1;
    request->flags = 3;
    request->source = value;
    request->destination = destination;
    request->control = count | 0x81000000;
    request->remaining = remaining;
    request->source_step = 0;
    request->destination_step = destination_step;
    request->next = 0;

    if (data_03002BCC == 0) {
        data_03002BCC = request;
    } else {
        DmaRequest *tail = data_03002BCC;

        while (tail->next != 0)
            tail = tail->next;
        tail->next = request;
    }
}
