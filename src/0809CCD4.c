#include "ffta.h"

typedef struct {
    u8 unknown_00[0xFC];
    u8 value_fc;
    u8 value_fd;
} Object0809CCD4;

typedef struct {
    Object0809CCD4 *object;
    u8 unknown_04[4];
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0e[0x11];
    s8 layer;
} Record0809CCD4;

typedef struct {
    Record0809CCD4 *record;
    s16 x;
    s16 y;
    s16 effect;
    s8 dx;
    s8 dy;
    u8 flags;
    s8 timer;
    u8 unknown_0e[2];
    s32 target;
    s32 value_14;
    s32 velocity;
    u16 state;
    u16 depth;
    u16 stack[8];
} Context0809CCD4;

extern u8 func_080CD92C(const void *object);
extern u8 func_080CDADC(const void *object);
extern s32 func_08099C1C(void *object, s8 x, s8 y);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern u32 func_08099C64(const void *object);
extern void func_080A92E4(s16 mode, s16 x, s16 height, s16 y, u32 effect);
extern void func_08141520(u16 sound);

#define PUSH_STATE(context) \
    ((context)->stack[(context)->depth++] = (context)->state)

static inline s32 step_toward(s16 target, s16 *position, s8 delta)
{
    s16 start = *position;
    s16 before;
    s16 after;
    s32 moving;

    *position = delta + *position;
    before = target - start;
    after = target - *position;
    if ((before <= 0 && after >= 0) || (before >= 0 && after <= 0)) {
        *position = target;
        moving = 0;
    } else {
        moving = 1;
    }
    return moving;
}

/* Complete [0x0809CCD4, 0x0809D126): 1106 bytes, 508 instructions.
 * Target:
 * f0b581b0041c217bfe2008402073a08b0b2800d918e280000149401800688746f8cc0908
 * 28cd090834cd0908d2ce09088acf0908e0cf0908d8d00908e8d00908b8d00908c8d00908
 * f8d0090802d1090818d10908207b0121014321730120a0830420265e23681f1c08371889
 * 0a22a25612181a81311c00040014081a891a0904090c0d1c00040214002a04dc08040028
 * 04da002a05db2804002802dc3e80002000e00120071c0621655e1e1c0c3698890b22a256
 * 12189a81291c00040014081a891a0904090c0b1c00040214002a04dc0804002804da002a
 * 05db1804002802dc3580002000e00120002f00d0ace1002800d0a9e120680168081cfc30
 * 0078022804d0081cfd300078042863d1081c30f0a3fd000600285dd12068006830f074fe
 * 0006002856d120680189c90409168289d2041216fcf708ff010123680a22985e81421fd1
 * 1f229a56181c04210023fbf7a3fa0b23a383e08b411ce1830004c00b221c203210180380
 * 0823a38310206073e08b411ce1830004c00b121813800720a08361e1401a401008182061
 * 0a26995f401a002800da404260611868fc300078022807d11f229a56181c02210023fbf7
 * 73fa06e01f229a56181c01210023fbf76bfa2068802149000222fdf767fb0320a08339e1
 * 20680189c90409168289d2041216fcf7b1fe0003206120680a21405e000260610020a061
 * 0220a08324e16069a169401860619939a1612269824204db002902dc6261002200e00122
 * 2168606900124881002a00d00ee10b23a3830822a05e002829d020681f22825605210023
 * fbf72afa217b022008400006050e002d0dd10826a05f23680822995e5a89303212041214
 * 0c269b5f00950cf0d1f98920a4f0ecfae18b481ce0830904c90b201c20304018a18b0180
 * a9e0e08b411ce1830004c00b221c2032101803800723a38310206073e08b411ce1830004
 * c00b12181380a383c8e025680a20295e2069411a002900da49426069411a081c0621a5f0
 * 89fb011c002900dc01216889401a688122680a21505e2169814200daace0518120680189
 * c90409168289d2041216fcf723fe000120610420a0839de025680a22a95e2069401a0028
 * 00da404206260621a5f060fb011c002900d101216889401a688122680a21505e21698142
 * 00da83e05181206802210022fdf7a8fa0b22a28303206073e08b411ce1830004c00b231c
 * 2033181802800822a283e08b411ce1830004c00b181802800a22a283e08b411ce1830004
 * c00b18180280a283e08b411ce1830004c00b18180280a283e08b411ce1830004c00b1818
 * 0280a683e08b411ce1830004c00b181806800722a283e08b411ce1830004c00b18180280
 * 0522a283e08b411ce1830004c00b1b181a800920a08331e0617b0d20205600281fdd481e
 * 607329e020681f22825600210023fbf74bf914e020681f22825603210023fbf743f90ce0
 * 20681f22825604210023fbf73bf904e02068fcf7b3fd00280cd0e08b0138e0830004c00b
 * 211c203109180888a08301e0002000e0012001b0f0bc02bc0847
 */
s32 func_0809CCD4(Context0809CCD4 *context)
{
    s32 moving_x;
    s32 moving_y;
    s32 distance;
    s32 step;
    s32 falling;

    context->flags &= ~1;
    switch (context->state) {
    case 0:
        context->flags |= 1;
        context->state = 1;
    case 1:
        moving_x = step_toward(context->x, &context->record->x, context->dx);
        moving_y = step_toward(context->y, &context->record->y, context->dy);
        if (moving_x || moving_y)
            break;
        if ((context->record->object->value_fc == 2 ||
             context->record->object->value_fd == 4) &&
            !func_080CD92C(context->record->object) &&
            !func_080CDADC(context->record->object)) {
            Record0809CCD4 *record;
            s32 ground = func_08099C1C(context->record,
                                       context->record->x >> 5,
                                       context->record->y >> 5) * 16;

            record = context->record;
            if (ground == record->height) {
                func_0809836C(record, 4, record->layer, 0);
                context->state = 11;
                PUSH_STATE(context);
                context->state = 8;
                context->timer = 16;
                PUSH_STATE(context);
                context->state = 7;
                break;
            }
            context->target = ground + ((record->height - ground) >> 1);
            distance = context->target - record->height;
            if (distance < 0)
                distance = -distance;
            context->value_14 = distance;
            if (record->object->value_fc == 2)
                func_0809836C(record, 2, record->layer, 0);
            else
                func_0809836C(record, 1, record->layer, 0);
            func_0809A570(context->record, 0x100, 2);
            context->state = 3;
            break;
        }
        context->target = func_08099C1C(context->record,
                                        context->record->x >> 5,
                                        context->record->y >> 5) << 12;
        context->value_14 = context->record->height << 8;
        context->velocity = 0;
        context->state = 2;
        break;
    case 2:
        context->value_14 += context->velocity;
        context->velocity -= 0x99;
        if (context->target >= context->value_14 && context->velocity <= 0) {
            context->value_14 = context->target;
            falling = 0;
        } else {
            falling = 1;
        }
        context->record->height = context->value_14 >> 8;
        if (falling)
            break;
        context->state = 11;
        if (context->effect) {
            func_0809836C(context->record, 5, context->record->layer, 0);
            if (!(context->flags & 2))
                func_080A92E4(context->effect, context->record->x,
                              context->record->height + 0x30,
                              context->record->y, 0);
            func_08141520(0x89);
            PUSH_STATE(context);
            context->state = 9;
            break;
        }
        PUSH_STATE(context);
        context->state = 7;
        context->timer = 16;
        PUSH_STATE(context);
        context->state = 7;
        break;
    case 3: {
        Record0809CCD4 *record = context->record;

        step = context->target - record->height;
        if (step < 0)
            step = -step;
        step = context->value_14 - step;
        step /= 6;
        if (step <= 0)
            step = 1;
        record->height -= step;
        if (context->target >= context->record->height) {
            context->record->height = context->target;
            context->target = func_08099C1C(context->record,
                                            context->record->x >> 5,
                                            context->record->y >> 5) * 16;
            context->state = 4;
        }
        break;
    }
    case 4: {
        Record0809CCD4 *record = context->record;

        distance = context->target - record->height;
        if (distance < 0)
            distance = -distance;
        step = distance / 6;
        if (step == 0)
            step = 1;
        record->height -= step;
        if (context->target >= context->record->height) {
            context->record->height = context->target;
            func_0809A570(context->record, 2, 0);
            context->state = 11;
            context->timer = 3;
            PUSH_STATE(context);
            context->state = 8;
            PUSH_STATE(context);
            context->state = 10;
            PUSH_STATE(context);
            context->state = 10;
            PUSH_STATE(context);
            context->state = 10;
            PUSH_STATE(context);
            context->state = 6;
            PUSH_STATE(context);
            context->state = 7;
            PUSH_STATE(context);
            context->state = 5;
            PUSH_STATE(context);
            context->state = 9;
        }
        break;
    }
    case 7:
        if (context->timer > 0) {
            context->timer--;
            break;
        }
        context->state = context->stack[--context->depth];
        break;
    case 8:
        func_0809836C(context->record, 0, context->record->layer, 0);
        context->state = context->stack[--context->depth];
        break;
    case 5:
        func_0809836C(context->record, 3, context->record->layer, 0);
        context->state = context->stack[--context->depth];
        break;
    case 6:
        func_0809836C(context->record, 4, context->record->layer, 0);
        context->state = context->stack[--context->depth];
        break;
    case 10:
        context->state = context->stack[--context->depth];
        break;
    case 9:
        if (func_08099C64(context->record))
            context->state = context->stack[--context->depth];
        break;
    case 11:
        return 0;
    }
    return 1;
}
