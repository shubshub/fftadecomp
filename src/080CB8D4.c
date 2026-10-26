#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2FC2];
    unsigned mode : 2;
} State080CB8D4;

extern State080CB8D4 g_state_02000000;
extern const u8 data_083D5A1C[];
extern const u8 data_083D965C[];
extern const u8 data_083DD360[];
extern void func_08005318(const void *table, void *object, u32 index, u32 flag);

/* Complete [0x080CB8D4, 0x080CB928): 84 bytes, 29 instructions. */
void func_080CB8D4(void *object, u8 index)
{
    s32 mode = g_state_02000000.mode;

    switch (mode) {
    case 2:
        func_08005318(data_083DD360, object, index, 1);
        break;
    case 1:
        func_08005318(data_083D965C, object, index, 1);
        break;
    case 0:
    default:
        func_08005318(data_083D5A1C, object, index, 1);
        break;
    }
}
