#include "ffta.h"

struct Node0800395C {
    struct Node0800395C *next;
    u16 id;
};

extern struct Node0800395C *data_030034B8;

/* 0800395C..0800397C: 32 bytes. */
u8 func_0800395C(void)
{
    if (data_030034B8 == 0)
        return 0;
    return data_030034B8->next != 0;
}
