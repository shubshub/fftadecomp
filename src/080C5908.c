#include "ffta.h"

/* Complete target: [0x080C5908, 0x080C5D60), 1112 bytes, including the
 * jump table and literal pools. */

typedef struct {
    u16 command;
    u16 count;
    u16 commands[34];
} CommandQueue080C5908;

typedef struct {
    u8 unknown_00[0x9C];
    s32 local_a;
    s32 local_b;
    s32 remote_a;
    s32 remote_b;
    u8 retries;
    s8 delay;
    u8 flags;
    u8 unknown_AF;
    CommandQueue080C5908 queue;
} Link080C5908;

typedef struct {
    u8 flags;
    u8 unknown_01;
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
    union {
        u16 packed;
        struct {
            u8 phase;
            u8 flags;
        } bytes;
    } status;
} System080C5908;

extern System080C5908 data_030028A0;
extern const char data_081499DC[];
extern const char data_081499E4[];
extern void func_08004B9C(void);
extern void func_08003A98(void);
extern void func_08004C40(void);
extern void func_08005028(void);
extern u32 func_08002804(void);
extern s32 func_08003B1C(const char *first, const char *second);
extern u32 func_08003D9C(const void *send, void *send_destination,
                         u16 send_count, void *receive, void *receive_source,
                         u16 receive_count);

/* Command-stack operations on a queue: push the current command and switch to
 * the next one, pop back to the pushed command, and empty the stack.  The ROM
 * has 19 copies of the push (ldrh/adds/strh [r4, #2], the first at 0x080C59CC;
 * case 1's is folded into the reset) and every count access goes through the
 * queue's address (link + 0xB0, then [r4, #2]), never through link + 0xB2,
 * with the redundant queue addresses commoned by the copy `adds r4, r1, #0` at
 * the switch head (0x080C5956): the operations took the queue by address. */
#define PUSH_COMMAND(queue, next) \
    ((queue)->commands[(queue)->count++] = (queue)->command, \
     (queue)->command = (next))
#define POP_COMMAND(queue) \
    ((queue)->command = (queue)->commands[--(queue)->count])
#define CLEAR_COMMANDS(queue) ((queue)->count = 0)

void func_080C5908(Link080C5908 *link)
{
    if (link->flags & 0x40)
        return;
    if (link->flags & 2) {
        if (data_030028A0.busy != 0 || data_030028A0.mode != 3) {
            link->flags |= 1;
            return;
        }
        link->flags &= ~1;
    }

    switch (link->queue.command) {
    case 1:
        func_08004B9C();
        func_08003A98();
        link->queue.command = 2;
        CLEAR_COMMANDS(&link->queue);
        PUSH_COMMAND(&link->queue, 4);
        break;
    case 2:
        if (!(link->flags & 0x10))
            break;
        link->flags &= ~2;
        PUSH_COMMAND(&link->queue, 3);
        PUSH_COMMAND(&link->queue, 11);
        if (data_030028A0.flags & 8) {
            PUSH_COMMAND(&link->queue, 7);
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 12);
        } else {
            PUSH_COMMAND(&link->queue, 7);
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 9);
        }
        break;
    case 3:
        if (link->local_a != link->remote_a || link->local_b != link->remote_b)
            link->flags |= 8;
        link->flags &= ~0x10;
        POP_COMMAND(&link->queue);
        break;
    case 4:
        if (data_030028A0.busy != 0
            || (data_030028A0.mode != 3 && data_030028A0.ticks > 16)) {
            if (++link->retries > 14) {
                link->retries = 14;
                link->queue.command = 13;
            } else {
                func_08004C40();
                link->queue.command = 1;
            }
        } else if (data_030028A0.busy != 0 || data_030028A0.mode != 3) {
            /* busy is known zero here (tested at 0x080C5AB8); the ROM
             * reloads and tests it again (0x080C5AF6-0x080C5B00). */
            func_08003A98();
        } else if (data_030028A0.status.packed == 0x101) {
            if (data_030028A0.flags & 8)
                link->delay = 8;
            else
                link->delay = 16;
            link->queue.command = 5;
        }
        break;
    case 5:
        if (link->delay > 0) {
            link->delay--;
            break;
        }
        link->flags |= 0x20;
        func_08005028();
        link->queue.command = 6;
        break;
    case 6:
        if (!func_08003B1C(data_081499DC, data_081499E4))
            break;
        POP_COMMAND(&link->queue);
        link->delay = 0;
        PUSH_COMMAND(&link->queue, 3);
        PUSH_COMMAND(&link->queue, 11);
        if (data_030028A0.flags & 8) {
            link->flags |= 4;
            link->local_a = (s16)func_08002804();
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 12);
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 8);
        } else {
            link->local_b = (s16)func_08002804();
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 9);
            PUSH_COMMAND(&link->queue, 10);
            PUSH_COMMAND(&link->queue, 9);
        }
        PUSH_COMMAND(&link->queue, 7);
        break;
    case 7:
        if (link->delay <= 7) {
            link->delay++;
            break;
        }
        link->delay = 0;
        POP_COMMAND(&link->queue);
        break;
    case 8:
        if (func_08003D9C(&link->local_a, &link->local_a, 2,
                           &link->local_b, &link->local_b, 2))
            POP_COMMAND(&link->queue);
        break;
    case 12:
        if (func_08003D9C(&link->local_a, &link->remote_a, 4,
                           &link->local_a, &link->remote_a, 4))
            POP_COMMAND(&link->queue);
        break;
    case 9:
        if (data_030028A0.status.bytes.flags == 12)
            POP_COMMAND(&link->queue);
        break;
    case 10:
        if (data_030028A0.status.packed == 0x101 && data_030028A0.mode == 3) {
            link->delay = 0;
            link->queue.command = 7;
        }
        break;
    case 11:
        link->flags |= 2;
        POP_COMMAND(&link->queue);
        break;
    }
}
