#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 value;
} WindowState;

extern void func_08016D64(WindowState *window);

/* 08017508..08017514: 12 bytes. */
void func_08017508(WindowState *window, u8 value)
{
    window->value = value;
    func_08016D64(window);
}
