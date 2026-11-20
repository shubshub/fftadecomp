#include "ffta.h"

/* Complete [0x080BAEE8, 0x080BB36E): 1158 bytes, including the 27-entry
 * jump table at 0x080BAF04 and the literal words at 0x080BB244, 0x080BB300
 * and 0x080BB340.  Runs the field list built by func_080BACF0
 * (src/080BACF0.c).
 * f0b582b0061c308c1a2800d936e28000014940180068874604af0b08a6af0b08
 * bcaf0b08c8af0b08deaf0b08faaf0b08dcb00b082cb10b08dcb10b0810b20b08
 * 48b20b0844b10b088ab10b081cb00b087ab00b0850b20b085eb20b08dcb20b08
 * eeb20b0804b30b08ceb20b08d6b20b082eb30b0844b30b0820b30b0828b30b08
 * 0cb00b0870af0b0830680168c07ff83100240870b069002802d067f767fcb461
 * 7168002909d00868f83000228256081c0a210023ddf7e6f974600020dfe13268
 * 0821505e0a23d15e0c24125fdbf7c2ff0120d2e1dbf7deff002800d0cee1c3e1
 * 72680825505f0a23d15e0c24125fdbf7b1ff0120c1e130681f22825607210023
 * ddf7c0f900207082872086f095fa0420b3e1708a01307082000400143f2800dc
 * ace1a1e130681f22825600210023ddf7a9f999e18020400167f70efcb0613368
 * 717bb27b0090181c4023dff7e7fab08200040014012806dc3068803000680121
 * dff70cfb80e13068006844210cf026ffb0683168b2691425735fe2f7fff93068
 * 7822524256235b421021e2f7b7fb0d2073e10124b068e0f705fc071c0025b068
 * e2f7c4fa002806d13168081c80300068e2f7d2fa051ce1f729fd013c002ce9da
 * 002f00d05ae1002800d057e1002d00d054e13068016800894009f63108703068
 * 016880894009f7310870b06967f7befbb56139e13468357b7268108900044015
 * 218909044915401a00060016918909044915a28912045215891a09060916e2f7
 * d9fa021c12061216201c291c0023ddf729f9002070820d203073882086f0fcf9
 * 06201ae1718a1222b05e772802dc481c708213e13068def791fd03e174683268
 * 108900044015218909044915401a00060016918909044915a28912045215891a
 * 09060916e2f7a6fa021c12061216201c05210023ddf7f6f8892086f0cdf90b20
 * ebe07068def76afd002800d1e6e07468206b0821084320633268108900044015
 * 218909044915401a00060016918909044915a28912045215891a09060916e2f7
 * 79fa021c12061216201c00210023ddf7c9f8b9e0348a7068006800210cf05efe
 * 021c201c00216af74bfa232030820d200ef0d6f90006002802d0c42040003082
 * 002070820820a8e06af728f9708a01307082000400140f2807dd0848c18a0320
 * 0840002801d0782070821223f05e772800dc93e06ef76af909208ee090f30002
 * 6af70cf900047de000207082dd2086f063f90f2081e0ff247068016b01225140
 * 01631225715f031c0a2909d00a2902dc002903d007e0142904d004e0062402e0
 * 052400e004242406002c0cdbf0690822995e0a255a5f0c255b5f240e00940224
 * 019427f0a9fc708a01307082000400141f2853dd7068def775fc7068def77cf9
 * 0020706040e018f04dfa142045e018f08ffa36e0ab2040000021012218f010f9
 * f061122039e004480021012218f008f9f061122031e0000057010000f0690028
 * 22d018f0b5fa0006002827d0f06918f0a5fa0020f06117e018f044fa18201ce0
 * 18f04cfa0de004480021002218f0e8f8f061162011e000005b010000f06927f0
 * 49fc0006002809d0708c013870840004c00b311c2431091808883084012002b0
 * f0bc02bc0847
 */

typedef struct {
    u8 unknown_00[0xF6];
    u8 tile_x;
    u8 tile_z;
    s8 direction;
} Unit;

/* The subject and the entry share this layout: both are read at +0, +8,
 * +0xA and +0xC, and both go to func_0809836C and func_08099C64. */
typedef struct {
    Unit *unit;
    u8 unknown_04[4];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u8 unknown_34[0x4C];
    void *scene;
} Subject;

typedef struct {
    Subject *subject;
    Subject *entry;
    void *details;
    u8 category;
    u8 first;
    u8 second;
    u8 third;
    u16 identifier;
    s16 timer;
    s16 result;
    u8 unknown_16[2];
    void *buffer;
    void *task;
    u16 current;
    u16 count;
    u16 fields[34];
} FieldContext;

typedef struct {
    u8 unknown_00[0x16];
    u16 filtered_pressed;
} InputState;

extern InputState g_state_0200F390;

extern void func_08022854(u8 *object);
extern void *func_08022840(u32 size);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern void func_08141520(u16 value);
extern int func_0809A604(void *context, u8 first, u8 second, u8 third, int fourth);
extern void func_0809A664(void *state, u8 value);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern void func_0809D464(void *details, Subject *subject, void *buffer, s32 count);
extern void func_0809D7E4(Subject *subject, u32 mode, s16 x, s16 y);
extern u32 func_0809B88C(void *resource);
extern u32 func_0809D614(const void *state);
extern u32 func_0809D640(void *owner, Subject *record);
extern u32 func_0809CAF4(void);
extern s32 func_0809D6BC(s8 x, s8 y);
extern u32 func_08099C64(const void *owner);
extern void func_08025688(u16 identifier, u16 value, const void *argument);
extern u8 func_080C95A8(u16 index);
extern s32 func_08025464(void);
extern void func_08029514(void);
extern void func_080E2C00(void *object, s16 x, s16 y, s16 z, u8 effect, u8 argument);
extern void func_08099BAC(Subject *state);
extern u32 func_080995C0(Subject *object);
extern void func_080D376C(void);
extern u8 func_080D37F8(void);
extern void *func_080D3508(u16 id, void *object, u32 arg);
extern u8 func_080D3878(const void *object);
extern void func_080D3864(void *task);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);
extern u8 func_080E2BDC(void *object);

/* Takes the next field off the list: the counterpart of commit_field in
 * src/080BACF0.c, and the same operation as next_step in src/080BBC38.c.
 * Its one copy in the ROM is the shared tail at 0x080BB350-0x080BB362. */
static inline void next_field(FieldContext *context)
{
    context->current = context->fields[--context->count];
}

u32 func_080BAEE8(FieldContext *context)
{
    u32 busy;
    u32 blocked;
    u32 moving;
    s32 i;
    s8 frame;

    switch (context->current) {
    case 26:
        context->subject->unit->direction = context->subject->direction;
        if (context->buffer) {
            func_08022854(context->buffer);
            context->buffer = 0;
        }
        if (context->entry) {
            func_0809836C(context->entry, 10, context->entry->unit->direction, 0);
            context->entry = 0;
        }
        return 0;
    case 0:
        func_08096F3C(context->subject->x, context->subject->y, context->subject->z);
        context->current = 1;
        break;
    case 1:
        if (!func_08096F7C())
            next_field(context);
        break;
    case 2:
        func_08096F3C(context->entry->x, context->entry->y, context->entry->z);
        context->current = 1;
        break;
    case 3:
        func_0809836C(context->subject, 7, context->subject->direction, 0);
        context->timer = 0;
        func_08141520(0x87);
        context->current = 4;
        break;
    case 4:
        if (++context->timer > 0x3F)
            next_field(context);
        break;
    case 25:
        func_0809836C(context->subject, 0, context->subject->direction, 0);
        next_field(context);
        break;
    case 12:
        context->buffer = func_08022840(0x1000);
        context->result = func_0809A604(context->subject, context->first,
                                        context->second, 0x40, (int)context->buffer);
        if (context->result <= 1) {
            func_0809A664(context->subject->scene, 1);
            next_field(context);
            break;
        }
        func_080C7EA4(context->subject->unit, 0x44);
        func_0809D464(context->details, context->subject, context->buffer,
                      context->result);
        func_0809D7E4(context->subject, 0x10, -0x78, -0x56);
        context->current = 13;
        break;
    case 13:
        /* 0x080BB07A-0x080BB0A6: the body runs twice (r4 counts 1, 0). */
        for (i = 0; i < 2; i++) {
            busy = func_0809B88C(context->details);
            blocked = 0;
            if (!func_0809D614(context->details))
                blocked = func_0809D640(context->subject->scene, context->subject);
            moving = func_0809CAF4();
        }
        if (busy || moving || blocked)
            break;
        context->subject->unit->tile_x = context->subject->x >> 5;
        context->subject->unit->tile_z = context->subject->z >> 5;
        func_08022854(context->buffer);
        context->buffer = 0;
        next_field(context);
        break;
    case 5:
        func_0809836C(context->subject, context->category,
                      func_0809D6BC((context->entry->x >> 5) - (context->subject->x >> 5),
                                    (context->entry->z >> 5) - (context->subject->z >> 5)), 0);
        context->timer = 0;
        context->category = 13;
        func_08141520(0x88);
        context->current = 6;
        break;
    case 6:
        if (context->timer <= 0x77) {
            context->timer++;
            break;
        }
        if (func_08099C64(context->subject))
            next_field(context);
        break;
    case 10:
        func_0809836C(context->entry, 5,
                      func_0809D6BC((context->subject->x >> 5) - (context->entry->x >> 5),
                                    (context->subject->z >> 5) - (context->entry->z >> 5)), 0);
        func_08141520(0x89);
        context->current = 11;
        break;
    case 11:
        if (!func_08099C64(context->entry))
            break;
        context->entry->flags |= 8;
        func_0809836C(context->entry, 0,
                      func_0809D6BC((context->subject->x >> 5) - (context->entry->x >> 5),
                                    (context->subject->z >> 5) - (context->entry->z >> 5)), 0);
        next_field(context);
        break;
    case 7:
        func_08025688(context->identifier, 0,
                      (const void *)func_080C7EA4(context->entry->unit, 0));
        context->identifier = 0x23;
        if (func_080C95A8(13))
            context->identifier = 0x188;
        context->timer = 0;
        context->current = 8;
        break;
    case 8:
        func_08025464();
        if (++context->timer > 0xF && (g_state_0200F390.filtered_pressed & 3))
            context->timer = 0x78;
        if (context->timer > 0x77) {
            func_08029514();
            context->current = 9;
        }
        break;
    case 9:
        /* 0x080BB24C: only the low halfword of the result is tested. */
        if ((u16)func_08025464())
            next_field(context);
        break;
    case 14:
        context->timer = 0;
        func_08141520(0xDD);
        context->current = 15;
        break;
    case 15:
        frame = -1;
        context->entry->flags ^= 1;
        switch (context->timer) {
        case 0:
            frame = 6;
            break;
        case 10:
            frame = 5;
            break;
        case 20:
            frame = 4;
            break;
        }
        if (frame >= 0)
            func_080E2C00(context->task, context->entry->x, context->entry->y,
                          context->entry->z, frame, 2);
        if (++context->timer > 0x1F) {
            func_08099BAC(context->entry);
            func_080995C0(context->entry);
            context->entry = 0;
            next_field(context);
        }
        break;
    case 19:
        func_080D376C();
        context->current = 20;
        break;
    case 20:
        if (func_080D37F8())
            next_field(context);
        break;
    case 16:
        context->task = func_080D3508(0x156, 0, 1);
        context->current = 18;
        break;
    case 17:
        context->task = func_080D3508(0x157, 0, 1);
        context->current = 18;
        break;
    case 18:
        if (!context->task) {
            next_field(context);
            break;
        }
        if (func_080D3878(context->task)) {
            func_080D3864(context->task);
            context->task = 0;
            next_field(context);
        }
        break;
    case 23:
        func_080D37AC();
        context->current = 24;
        break;
    case 24:
        if (func_080D37C4())
            next_field(context);
        break;
    case 21:
        context->task = func_080D3508(0x15B, 0, 0);
        context->current = 22;
        break;
    case 22:
        if (func_080E2BDC(context->task))
            next_field(context);
        break;
    }
    return 1;
}
