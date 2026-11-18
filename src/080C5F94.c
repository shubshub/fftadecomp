#include "ffta.h"

// Complete target: [0x080C5F94, 0x080C62CA), 822 bytes, including the
// jump table and literal pools.

typedef struct {
    void *context;
    void *send_destination;
    void *buffer;
    void *receive;
    u16 width;
    u16 mode;
    s8 delay;
    u8 index;
    u8 blocks;
    u8 unknown_17;
    u16 command;
    u16 count;
    u16 commands[34];
} CommandQueue080C5F94;

typedef void (*BufferCopier080C5F94)(void *, const void *, u32);

extern BufferCopier080C5F94 const data_0836D4BC[];

typedef struct {
    u8 flags;
    u8 unknown_01;
    u8 mode;
    u8 unknown_03[0x121];
    union {
        u16 packed;
        struct {
            u8 phase;
            u8 flags;
        } bytes;
    } status;
} System080C5F94;

typedef struct {
    u8 unknown_00[0xAE];
    u8 flags;
} Input080C5F94;

extern System080C5F94 data_030028A0;
extern Input080C5F94 data_02015738;
extern u32 data_02015830[];
extern const char data_081499EC[];
extern const char data_081499F4[];
extern const char data_081499FC[];
extern const char data_08149A04[];
extern const char data_08149A0C[];
extern const char data_08149A14[];
extern void func_08005028(void);
extern s32 func_08003B1C(const char *first, const char *second);
extern u32 func_08003D20(const void *source, void *destination, u16 length);
extern u32 func_08003D9C(const void *send, void *send_destination,
                         u16 send_count, void *receive, void *receive_source,
                         u16 receive_count);
extern void func_08022854(void *allocation);

u8 func_080C5F94(CommandQueue080C5F94 *queue)
{
    s32 n;
    s32 offset;
    u32 count;

    switch (queue->command) {
    case 11:
        queue->delay = 8;
        queue->command = 12;
        break;
    case 12:
        if (queue->delay > 0) {
            queue->delay--;
            break;
        }
        queue->command = queue->commands[--queue->count];
        break;
    case 17:
        if (queue->buffer) {
            data_0836D4BC[0](queue->context, queue->buffer, queue->width);
            func_08022854(queue->buffer);
            queue->buffer = 0;
        }
        queue->command = queue->commands[--queue->count];
        break;
    case 13:
        if (data_030028A0.flags & 8) {
            data_02015830[0] = (u32)queue->buffer;
            data_02015830[1] = (u32)queue->context;
        } else {
            data_02015830[16] = (u32)queue->buffer;
            data_02015830[17] = (u32)queue->context;
        }
        queue->command = queue->commands[--queue->count];
        break;
    case 15:
        if (data_030028A0.flags & 8) {
            queue->send_destination = (void *)data_02015830[16];
            queue->receive = (void *)data_02015830[17];
        } else {
            queue->send_destination = (void *)data_02015830[0];
            queue->receive = (void *)data_02015830[1];
        }
        queue->command = queue->commands[--queue->count];
        break;
    case 14:
        if (func_08003D9C(data_02015830, data_02015830, 4,
                           data_02015830 + 16, data_02015830 + 16, 4))
            queue->command = 7;
        break;
    case 16:
        offset = queue->index * 64;
        n = queue->width - offset;
        if (n <= 0) {
            queue->command = queue->commands[--queue->count];
            break;
        }
        if (n > 64)
            n = 64;
        if (!(data_030028A0.flags & 8)) {
            queue->index++;
            queue->commands[queue->count++] = queue->command;
            queue->command = 5;
            break;
        }
        if (!func_08003D9C((u8 *)queue->context + offset,
                           (u8 *)queue->send_destination + offset, n >> 1,
                           (u8 *)queue->receive + offset,
                           (u8 *)queue->buffer + offset, n >> 1))
            break;
        queue->index++;
        queue->commands[queue->count++] = queue->command;
        queue->command = 7;
        break;
    case 8:
        data_02015830[0] = (u32)queue->context;
        if (func_08003D20(data_02015830, data_02015830, 2))
            queue->command = 7;
        break;
    case 9:
        queue->send_destination = (void *)data_02015830[0];
        queue->command = queue->commands[--queue->count];
        break;
    case 10:
        count = queue->width;
        if (count & 1)
            count++;
        if (func_08003D20(queue->context, queue->send_destination, count >> 1))
            queue->command = 7;
        break;
    case 7:
        if (data_030028A0.status.packed == 0x101 && data_030028A0.mode == 3)
            queue->command = 11;
        break;
    case 19:
        data_02015738.flags |= 0x10;
        queue->command = 20;
        break;
    case 20:
        if ((data_02015738.flags >> 1) & 1)
            queue->command = queue->commands[--queue->count];
        break;
    case 5:
        if (data_030028A0.status.bytes.flags == 12)
            queue->command = 7;
        break;
    case 6:
        if (data_030028A0.status.bytes.flags == 5)
            queue->command = 7;
        break;
    case 0:
        func_08005028();
        queue->command = queue->commands[--queue->count];
        break;
    case 1:
        if (func_08003B1C(data_081499EC, data_081499F4))
            queue->command = 2;
        break;
    case 4:
        if (func_08003B1C(data_081499FC, data_08149A04))
            queue->command = 2;
        break;
    case 18:
        if (func_08003B1C(data_08149A0C, data_08149A14))
            queue->command = 2;
        break;
    case 2:
        if (data_030028A0.status.packed == 0x101 && data_030028A0.mode == 3) {
            queue->delay = 0;
            queue->command = 3;
        }
        break;
    case 3:
        if (queue->delay <= 7) {
            queue->delay++;
            break;
        }
        queue->command = queue->commands[--queue->count];
        break;
    case 21:
        if (!queue->buffer)
            return 0;
        func_08022854(queue->buffer);
        queue->buffer = 0;
        break;
    }
    return 1;
}
