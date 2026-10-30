#include "ffta.h"

typedef struct {
    u8 active : 1;
    u8 unknown_flags : 7;
    u8 unknown_001[0x10C];
    u8 graphic;
    u8 unknown_10E[2];
    u8 width;
    u8 height;
} DisplayObject08089CAC;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} RenderState08089CAC;

extern RenderState08089CAC data_03000E30;
extern void func_0804C7A0(Entry *entries, u16 index);

/* Target bytes [08089CAC, 08089CE4):
 * 00 B5 02 1C 11 78 02 20 40 42 08 40 10 70 08 49
 * 50 18 F0 21 01 70 88 23 5B 00 D0 18 01 70 05 48
 * 40 68 03 3B D1 18 09 78 C2 F7 64 FD 01 BC 00 47
 * 11 01 00 00 30 0E 00 03.
 */
void func_08089CAC(DisplayObject08089CAC *object)
{
    object->active = 0;
    object->height = 0xF0;
    object->width = 0xF0;
    func_0804C7A0(data_03000E30.surface, object->graphic);
}
