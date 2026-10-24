/* func_080E28C4: target [080E28C4,080E29C4), 256 bytes.
 * f0b557464e464546e0b4031c0e1c141c318880204000814211d0814202dc00290ad065e08120400081421cd0814211db013081425ad05be00620a07058e0044806211a1cf5f7b2f86063308801304ee07c5c3908606bf5f7cff86063002847d13088013043e001208246002188460025142000198146271da80049460c182268002a16d0680038180188494209040914101c2ef77ffb20682ef792fd2060002802d00024a24604e0404601300006000e8046681c0006050e072dddd900253a1c00236800111808884446001b08800004002800da0b80681c0006050e072df0d95046002804d03088013000e002203080002038bc9846a146aa46f0bc02bc0847
 */

#include "ffta.h"

typedef struct Struct08011058 Struct08011058;
typedef struct ListNode ListNode;

typedef struct {
    u16 phase;
} CallbackDescriptor;

typedef struct {
    u8 unknown_00[2];
    u8 field_02;
    u8 unknown_03;
    s16 values[8];
    void *objects[8];
    void *child;
} CallbackPayload;

void *func_080D7A70(const void *records, u8 count, void *parent);
void *func_080D7ABC(void *task);
void func_08011058(Struct08011058 *item, s16 value);
ListNode *func_08011484(ListNode *node);

u32 func_080E28C4(void *task, void *descriptor, void *payload)
{
    CallbackDescriptor *state = descriptor;
    CallbackPayload *work = payload;

    switch (state->phase) {
    case 0:
        work->field_02 = 6;
        break;
    case 0x100:
        work->child = func_080D7A70((const void *)0x08395C7C, 6, task);
        state->phase++;
        break;
    case 0x101:
        work->child = func_080D7ABC(work->child);
        if (work->child == 0)
            state->phase++;
        break;
    case 0x102:
    {
        u8 all_done = 1;
        u8 completed = 0;
        u8 index;

        for (index = 0; index < 8; index++) {
            if (work->objects[index] != 0) {
                func_08011058(work->objects[index], -work->values[index]);
                work->objects[index] = func_08011484(work->objects[index]);
                if (work->objects[index] != 0)
                    all_done = 0;
                else
                    completed++;
            }
        }
        for (index = 0; index < 8; index++) {
            work->values[index] -= completed;
            if (work->values[index] < 0)
                work->values[index] = 0;
        }
        if (all_done)
            state->phase++;
        break;
    }
    case 0x103:
        state->phase = 2;
        break;
    }
    return 0;
}
