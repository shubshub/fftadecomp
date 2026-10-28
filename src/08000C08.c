#include "ffta.h"

/* 0x08000C08..0x08000C64: 92 bytes. */
struct Transfer08000C08 {
    u8 active;
    u8 enabled;
    u16 unknown_02;
    const void *source;
    void *destination;
    u32 control;
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_16;
    struct Transfer08000C08 *next;
};

extern struct Transfer08000C08 *data_03002BCC;

void func_08000C08(struct Transfer08000C08 *transfer, const void *source,
                   void *destination, u16 count, u16 first, u16 second,
                   u16 third)
{
    transfer->active = 1;
    transfer->enabled = 1;
    transfer->source = source;
    transfer->destination = destination;
    transfer->control = count | 0x84000000;
    transfer->first = first;
    transfer->second = second;
    transfer->third = third;
    transfer->next = 0;

    if (data_03002BCC == 0) {
        data_03002BCC = transfer;
    } else {
        struct Transfer08000C08 *tail = data_03002BCC;

        while (tail->next != 0)
            tail = tail->next;
        tail->next = transfer;
    }
}
