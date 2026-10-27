#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u16 selection;
    u16 count;
    u16 options[34];
} OptionList;

extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);

static inline void append_option(OptionList *list, u16 option)
{
    list->selection = option;
    list->options[list->count++] = option;
}

/* 0x080BD14C: 160 bytes; initialize the available modes and selection. */
void func_080BD14C(OptionList *list)
{
    g_callbacks_0836D4B8[0](list, sizeof(*list));
    append_option(list, 0);
    append_option(list, 8);
    append_option(list, 11);
    append_option(list, 10);
    append_option(list, 5);
    append_option(list, 7);
    append_option(list, 6);
    list->selection = 3;
}
