#include "ffta.h"

/* 0x0800A4F8 - 108 bytes including two trailing literal words. */
typedef struct {
    u16 unknown_00;
    u16 position;
} ScriptContext0800A4F8;

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x103];
} ScriptObject0800A4F8;

typedef struct {
    u8 unknown_0000[0xA8];
    u8 selected;
    u8 unknown_00A9[0xE4B];
    ScriptObject0800A4F8 objects[12];
} ScriptState0800A4F8;

extern ScriptState0800A4F8 g_state_020020D0;

u8 func_080C82B8(const ScriptObject0800A4F8 *object);
u8 func_080C8364(const ScriptObject0800A4F8 *object);
u8 func_080C8348(const ScriptObject0800A4F8 *object);

void func_0800A4F8(ScriptContext0800A4F8 *context, const u8 *instruction)
{
    s8 index = g_state_020020D0.selected - 1;

    if ((u8)index <= 11) {
        ScriptObject0800A4F8 *object = &g_state_020020D0.objects[index];

        if (object->active == 0 || !func_080C82B8(object) ||
            func_080C8364(object) || func_080C8348(object))
            context->position += instruction[1] | (instruction[2] << 8);
    }
}
