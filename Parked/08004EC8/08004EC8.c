#include "ffta.h"

struct Packet08004EC8 {
    u8 command;
    u8 flags;
    u16 checksum;
    u8 payload[16];
};

struct TransferState08004EC8 {
    u8 timer_enabled;
    u8 unknown_01;
    u8 first_flags;
    u8 second_flags;
    u8 unknown_04[6];
    s8 timeout;
    u8 command;
    u8 unknown_0C[8];
    s32 remaining;
    u8 unknown_18[16];
    struct Packet08004EC8 *packet;
};

extern struct TransferState08004EC8 data_030028A0;
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Target: 0x08004EC8..0x08004F34, 108 bytes / 47 instructions. */
void func_08004EC8(const void *payload)
{
    u32 sum = 0;
    u32 i;
    u16 *word;

    data_030028A0.packet->command = data_030028A0.command;
    data_030028A0.packet->flags = data_030028A0.first_flags ^ data_030028A0.second_flags;
    data_030028A0.packet->checksum = 0;
    func_0814186C(payload, data_030028A0.packet->payload, (1u << 26) | 4);
    for (i = 0, word = (u16 *)data_030028A0.packet; i < 10; i++) {
        sum += *word++;
    }
    data_030028A0.packet->checksum = ~sum;
    if (data_030028A0.timer_enabled) {
        /* plausible: hardware register, timer 3 control. */
        *(volatile u16 *)0x0400010E = 0;
    }
    data_030028A0.remaining = data_030028A0.timeout;
    if (data_030028A0.timer_enabled) {
        /* plausible: hardware register, timer 3 control. */
        *(volatile u16 *)0x0400010E = 0xC0;
    }
}
