#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Owner0812BA08;

typedef struct {
    u16 state;
    u16 unknown_02;
    Owner0812BA08 *owner;
} Script0812BA08;

/* The unit record of src/08124560.c. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xCC];
    u8 x;
    u8 y;
    u8 facing;
} UnitRecord0812BA08;

typedef struct {
    UnitRecord0812BA08 *record;
    u8 unknown_04[4];
    s16 unknown_08;
    s16 y;
    u8 unknown_0C[0x13];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u8 unknown_34[0x20];
    void *first;
} Object0812BA08;

typedef struct {
    u8 fields[0x30];
} UnitDefinition0812BA08;

/* The 0x28-byte scene definition of src/08124560.c. */
typedef struct {
    u16 count;
    u8 unknown_02[2];
    UnitDefinition0812BA08 *units;
    u8 unknown_08[0x19];
    u8 unit_index;  /* 1-based, into g_table_0854CD54[29].units */
    u8 unknown_22[6];
} SceneDefinition0812BA08;

typedef struct {
    Owner0812BA08 *owner;
    Object0812BA08 *entries[13];
    Object0812BA08 *current;
    s16 timer;
    s16 target;
    u8 flags;
} Payload0812BA08;

extern const SceneDefinition0812BA08 g_table_0854CD54[];
extern void (*data_08394034)(void *object, u8 value, u32 first, u32 second,
                             u32 third, u32 fourth);
extern void *func_08096D7C(void);
extern u32 func_08099CDC(void *context, Object0812BA08 **entries);
extern u8 func_080C8298(UnitRecord0812BA08 *record);
extern u16 func_0800A018(void);
/* The ROM passes a zero (0x0812BACA); src/080C83A4.c reads no argument. */
extern UnitRecord0812BA08 *func_080C83A4(u32 unknown);
extern void func_080C9644(UnitRecord0812BA08 *record,
                          UnitDefinition0812BA08 *definition, u8 mode);
extern u8 func_080C84F4(void);
extern u8 func_080C8530(void);
extern Object0812BA08 *func_08092440(void *context, UnitRecord0812BA08 *record);
extern void func_0809836C(Object0812BA08 *object, u16 action, s8 value,
                          u16 option);
extern void func_08141520(u16 sound);
extern s32 abs(s32 value);

/* Complete target [0x0812BA08, 0x0812BCE4), 732 bytes.
 *
 * A task phase handler in the form of src/0812B980.c.  It finds or creates
 * a unit object, moves it 0x50 from its place, fades the blend registers
 * while it eases back, then steps its direction through 1, 2, 3 and 0. */
u32 func_0812BA08(void *task, Script0812BA08 *script, Payload0812BA08 *payload)
{
    s32 count;
    s32 index;
    s32 done;
    s32 diff;
    s32 step;

    switch (script->state) {
    case 0:
        payload->owner = script->owner;
        payload->current = 0;
        count = func_08099CDC(func_08096D7C(), payload->entries);
        for (index = 0; index < count; index++) {
            if (func_080C8298(payload->entries[index]->record))
                payload->current = payload->entries[index];
        }
        break;
    case 1:
        break;
    case 0x100:
        if (payload->current != 0) {
            script->state = 0x101;
        } else {
            const SceneDefinition0812BA08 *scene = &g_table_0854CD54[func_0800A018()];
            /* The ROM forms the address of row 29, g_table_0854CD54 + 0x488
             * (0x0812BAB4-0x0812BAB8), and reads units through it at +4
             * (0x0812BAC6). */
            const SceneDefinition0812BA08 *source = &g_table_0854CD54[29];
            UnitDefinition0812BA08 *definition = &source->units[scene->unit_index - 1];
            UnitRecord0812BA08 *record = func_080C83A4(0);

            func_080C9644(record, definition, 0);
            record->flags |= 0x1000;
            record->facing = 0;
            record->x = func_080C84F4();
            record->y = func_080C8530();
            payload->current = func_08092440(func_08096D7C(), record);
            payload->current->flags |= 5;
            script->state = 0x101;
        }
        break;
    case 0x101:
        g_control_flags_03000940.bldcnt_lo = 0x40;
        g_control_flags_03000940.bldcnt_hi = 0x3F;
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 0x10;
        payload->timer = 0;
        func_0809836C(payload->current, 3, 0, 0);
        payload->current->flags &= ~5;
        payload->target = payload->current->y;
        payload->current->y += 0x50;
        data_08394034(payload->current->first, 1, 0, 0, 0, 0);
        func_08141520(200);
        script->state = 0x102;
        break;
    case 0x102:
        done = 0;
        if (++payload->timer > 1) {
            payload->timer = 0;
            if (g_control_flags_03000940.bldalpha_lo < 16) {
                g_control_flags_03000940.bldalpha_lo++;
            } else if (g_control_flags_03000940.bldalpha_hi != 0) {
                g_control_flags_03000940.bldalpha_hi--;
            } else {
                data_08394034(payload->current->first, 0, 0, 0, 0, 0);
                g_control_flags_03000940.bldcnt_lo = 0;
                done = 1;
            }
        }
        diff = payload->target - payload->current->y;
        step = diff / 8;
        if (step == 0 && diff != 0)
            step = diff / abs(diff);
        payload->current->y += step;
        /* The ROM takes abs(step) and tests it > 0 (0x0812BC32-0x0812BC3C). */
        if (abs(step) < 1 && !(payload->flags & 1)) {
            func_0809836C(payload->current, 4, 0, 0);
            payload->flags |= 1;
        }
        if (step == 0 && done) {
            script->state = 0x103;
            payload->timer = 0;
        }
        break;
    case 0x103:
        if (++payload->timer > 7) {
            payload->timer = 0;
            payload->current->direction++;
            if (payload->current->direction > 3) {
                payload->current->direction = 0;
                func_0809836C(payload->current, 8, payload->current->direction, 0);
                script->state = 0x105;
            } else {
                func_0809836C(payload->current, 9, payload->current->direction, 0);
            }
        }
        break;
    case 0x105:
        payload->owner->complete = 1;
        script->state = 3;
        break;
    }
    return 0;
}
