#include "ffta.h"

// Target [0x080C034C, 0x080C045C), 272 bytes:
// 70b5051c0c1c134813490268281c81f077ff6c600d2009f021f9000600282ad0201c01f0ddfb
// 0006002821d1201cdaf749fb0006060e201c803000682168d6f7adfe002800d00126002e07d0
// 082006f00bff06e0b8d436083c550000092006f003ff024829180b20088046e0f4540000092006
// f0f9fe206873f012ff0006002805d01f482a18117804200843107020680df0d2fb0006002807d1
// 20680af000f80a2182f05ffb002805d115482a1811784020084310702068152107f04dfd114aa9
// 18002308802168081cf63002780e4c28190270f73109780c4aa81801702a342a191380518848
// 1c50800904c90b04342819401803800920108070bc01bc0047af540000c8540000ca540000cb54
// 0000

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0xF6];
    u8 unknown_F6;
    u8 unknown_F7;
} Unit080C034C;

typedef struct {
    Unit080C034C *unit;
    u8 unknown_04[0x7C];
    void *collection;
} Context080C034C;

typedef struct {
    u16 state;
    u16 count;
    u16 entries[(0x553C - 0x54F8) / 2];
} Phase080C034C;

typedef struct {
    u32 unknown_00;
    Context080C034C *context;
    u8 unknown_08[0x54AF - 0x8];
    u8 flags;
    u8 unknown_54B0[0x54C8 - 0x54B0];
    u16 unknown_54C8;
    u8 unknown_54CA;
    u8 unknown_54CB;
    u8 unknown_54CC[0x54F4 - 0x54CC];
    Phase080C034C phase;
} State080C034C;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 func_080C95A8(u32 id);
extern u8 func_080C1B2C(Context080C034C *context);
extern u8 func_0809AA10(Context080C034C *context);
extern void *func_080970E8(void *collection, Unit080C034C *unit);
extern void func_080C71B4(u16 request);
extern u8 func_081341EC(Unit080C034C *unit);
extern u8 func_080CDB84(Unit080C034C *unit);
extern s32 func_080CA3EC(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);

void func_080C034C(State080C034C *state, Context080C034C *context)
{
    Phase080C034C *phase;

    g_callbacks_0836D4B8[0](state, sizeof(State080C034C));
    state->context = context;

    if (func_080C95A8(0xD)) {
        if (!func_080C1B2C(context)) {
            u8 selected = func_0809AA10(context);

            if (func_080970E8(context->collection, context->unit))
                selected = 1;
            if (selected)
                func_080C71B4(8);
            else
                func_080C71B4(9);
            state->phase.state = 0xB;
            return;
        }
        func_080C71B4(9);
    }

    if (func_081341EC(context->unit))
        state->flags |= 4;
    if (func_080CDB84(context->unit)
        || (u32)func_080CA3EC(context->unit) / 10 == 0)
        state->flags |= 0x40;

    state->unknown_54C8 = func_080C7EA4(context->unit, 0x15);
    state->unknown_54CA = context->unit->unknown_F6;
    state->unknown_54CB = context->unit->unknown_F7;
    phase = &state->phase;
    phase->state = 0;
    phase->entries[phase->count++] = 0;
    phase->state = 9;
}
