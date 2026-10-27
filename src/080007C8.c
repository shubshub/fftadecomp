#include "ffta.h"

typedef struct DmaRequest {
    u8 mode;
    u8 flags;
    u8 unknown_02[2];
    u32 source;
    u32 destination;
    u32 control;
    u16 remaining;
    u16 source_step;
    u16 destination_step;
    u16 unknown_16;
    struct DmaRequest *next;
} DmaRequest;

typedef struct {
    u32 source;
    u32 destination;
    u32 control;
} DmaRegisters;

extern DmaRequest *data_03002BCC;
extern u16 data_03000E10;
extern u32 data_03002BC8;
extern u16 data_03002BC0[];
extern DmaRegisters *const data_0836D470[];
extern void func_08003A08(u32 channel);

void func_080007C8(void)
{
    DmaRequest *request = data_03002BCC;
    DmaRequest *last;

    while (request) {
        if (data_03000E10 == 1 && (request->flags & 1)) {
            request = request->next;
            continue;
        }
        if (request->flags & 2)
            data_03002BC8 = request->source;
        for (;;) {
            s32 channel;
            DmaRegisters *registers;

            if (request->source > 0x07FFFFFF ||
                request->destination > 0x07FFFFFF)
                channel = 3;
            else
                channel = 0;
            for (; channel <= 3; channel++) {
                if (!data_03002BC0[channel])
                    break;
            }
            if (channel > 3)
                break;
            registers = data_0836D470[channel];
            registers->source = (request->flags & 2)
                ? (u32)&data_03002BC8 : request->source;
            registers->destination = request->destination;
            registers->control = request->control;
            func_08003A08(channel);
            if (request->mode != 1)
                break;
            if (--request->remaining == 0)
                break;
            if (!(request->flags & 2))
                request->source += request->source_step;
            request->destination += request->destination_step;
        }
        request->flags |= 0x80;
        request = request->next;
    }

    request = data_03002BCC;
    last = 0;
    data_03002BCC = 0;
    while (request) {
        if (!(request->flags & 0x80)) {
            if (!last) {
                last = request;
                data_03002BCC = request;
            } else {
                last->next = request;
                last = request;
            }
        }
        request = request->next;
    }
}
