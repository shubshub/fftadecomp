#include "ffta.h"

typedef struct Node080BA66C {
    void *object;
    u8 active;
    u8 first;
    u8 second;
    u8 height;
    struct Node080BA66C *next;
} Node080BA66C;

typedef struct {
    Node080BA66C *head;
    u8 unknown_04[0x9C];
    s8 counter;
} State080BA66C;

extern u16 data_03003BA4[];
extern void (*data_0836D4BC)(void *destination, const void *source, u32 length);
extern void func_0808EFCC(void *object, u32 first, u32 height, u32 second);

/* 0x080BA66C: 100 bytes; rotate the values periodically and update active nodes. */
void func_080BA66C(State080BA66C *state)
{
    Node080BA66C *node;

    if (++state->counter > 5) {
        u16 first = data_03003BA4[0];

        data_0836D4BC(data_03003BA4, data_03003BA4 + 1, 12);
        data_03003BA4[6] = first;
        state->counter = 0;
    }
    for (node = state->head; node; node = node->next) {
        if (node->active)
            func_0808EFCC(node->object, node->first * 32 + 16,
                          node->height * 16, node->second * 32 + 16);
    }
}
