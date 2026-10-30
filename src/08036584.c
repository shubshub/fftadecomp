#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2E54];
    unsigned selection : 5;
    unsigned unknown_05 : 3;
} SelectionState08036584;

extern SelectionState08036584 g_state_02000000;
extern void func_0803652C(u8 value);

/* 08036584..080365B8: 52 bytes, including the global and field-offset literals. */
void func_08036584(u8 value)
{
    func_0803652C(value);
    g_state_02000000.selection = value;
}
