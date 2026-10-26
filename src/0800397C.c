#include "ffta.h"

struct Node0800397C {
    struct Node0800397C *next;
    u16 id;
};

extern u8 data_030034D1;
extern u16 data_030034D4;
extern u8 data_030034D0;
extern struct Node0800397C data_030034C0[];
extern struct Node0800397C *data_030034B8;

/* Target: [0x0800397C, 0x080039E8), 108 bytes, 37 instructions. */
void func_0800397C(u8 two_nodes)
{
    data_030034D1 = 0;
    data_030034D4 = 2;
    if (two_nodes != 0) {
        struct Node0800397C *second;

        data_030034D0 = 2;
        data_030034C0[0].next = 0;
        data_030034C0[0].id = 1;
        data_030034B8 = second = &data_030034C0[1];
        second->next = &data_030034C0[0];
        second->id = 2;
    } else {
        data_030034D0 = 1;
        data_030034B8 = &data_030034C0[0];
        data_030034C0[0].next = 0;
        data_030034C0[0].id = 2;
    }
}
