#include "ffta.h"

typedef struct UnitOwner080B7F4C UnitOwner080B7F4C;

typedef struct CursorState080B7F4C {
    UnitOwner080B7F4C *owner;
    void *handle;
    u8 x;
    u8 y;
} CursorState080B7F4C;

typedef void (*BufferInitializer080B7F4C)(void *destination, u32 size);

extern CursorState080B7F4C data_02010050;
extern BufferInitializer080B7F4C const g_callbacks_0836D4B8[];

/* Complete [0x080B7F4C, 0x080B7F74): 40 bytes, 15 instructions. */
void func_080B7F4C(void)
{
    g_callbacks_0836D4B8[0](&data_02010050, sizeof(data_02010050));
    data_02010050.x = 0xFF;
    data_02010050.y = -1;
}
