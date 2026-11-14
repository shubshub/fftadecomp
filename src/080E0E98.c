// Target: complete [0x080E0E98, 0x080E11C2), 810 bytes:
// f0b586b0061c0f1c151c39880548814271d081420ddc012927d0012904dc00291ad07de1010100
// 0080204000814225d076e10848814200d13ae1814200dad5e00130814200d14de10130814200d1
// 5fe166e1000003010000b88aa870f88ae8707868a861b86828645ae103484a3001780021017054
// e10000400900033c24a87805281cdb062802dd0a2813d017e0a869fcf7e4fb0004000c042806d1
// a8699821fdf7e8f81420288022e0a8693c21fdf7e1f810e0a8699c21fdf7dcf818e03c21a87812
// 2800d15421a869fdf7d3f8a878092800d13224a869291d01235b42002200920194029203960122
// fdf795fa68633888013013e12888002805d0013828800004002800d00be1686b002803d0287900
// 2800d104e1a869a91d2a1c0832faf707ff0024a8780a2800d110240621685e2989240424146118
// 09040914254baa78d218127800922a1c1c320192224baa789200d21812680292039600220023f5
// f74ff8e862a878c0001c4940180096012104220023fef7befea86319480622ab5e298964182404
// 24140094002101910222f6f7faf81348311cf2f734ff286312480096012104220023fef7a4fee8
// 63a87806280cd137202880281c0c300823e95e2a89483a120412141423fff7d1fa38880130a4e0
// a85a39084c5a3908dc5a390868558f08c8d89408d45a3908a878062819d12888002802d0013828
// 8090e02c1c0c34201cfff7f8fa000600280bd1201cfff7d0fae8690622a95e0c23ea5e00232ff7
// 8cfb7ce0286bf2f722ff2863002876d1022022f76cfa174a118881431180e86af5f72bf8e86200
// 2869d1686bfaf7b9fc061c6e63002e62d104a806800f4c211c0f4a60f0b6fb6846123006808021
// 89006418211c0b4a60f0acfb059605a809490a4a60f0a4fba878042846d1102028803888013042
// e040090003203900034000000170000001c0ff0006100000012888013828800004002831d10748
// 311cf2f7a0fe286306480096012104220023fef710fea8633888013020e0bf5a3908845b390828
// 6bf2f7c3fe2863002817d1ab69052000210022faf7a0fe0348311cf2f780fe28633888013008e0
// c95a3908286bf2f7adfe2863002801d102203880002006b0f0bc02bc0847

#include "ffta.h"
#include "control_flags.h"

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u32 value;
    u8 unknown_0c[8];
    u16 selector;
    u16 variant;
} Descriptor080E0E98;

typedef struct {
    u16 countdown;
    u8 selector;
    u8 variant;
    u8 ready;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0a[2];
    InterpolationState motion;
    void *object;
    void *outputs[4];
    void *coordinate_task;
    void *script;
    void *overlay;
    void *first_records;
    void *second_records;
    u32 value;
} Payload080E0E98;

extern const u8 data_08395AA8[];
extern const void *const data_08395A4C[];
extern const u8 data_08395ADC[][8];
extern const u8 data_08395AD4[];
extern const u8 data_08395ABF[];
extern const u8 data_08395AC9[];
extern const u8 data_08395B84[];
extern const u8 data_088F5568[];
extern const u8 data_0894D8C8[];
extern u16 data_03003920[];
extern u8 data_0600FFC0[];

extern u16 func_080DD6F4(void *object);
extern void func_080DE10C(void *object, u16 value);
extern void *func_080DE4B0(void *object, u8 *ready, u8 mode, s8 event,
                          s8 repeat_count, u8 delay, u16 initial_delay,
                          void *parent);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080D6098(s16 x, s16 y, u16 z, u8 mode, u16 count,
                          void **outputs, const void *records, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void func_080D7220(const void *data, u8 first, u8 second, s16 x,
                          s16 y, u16 value);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *task);
extern void func_080E0608(InterpolationState *state, s16 start, s16 end,
                          s16 duration);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);
extern void func_080107D4(void *object, s16 x, s16 y, u8 z);
extern u32 func_080035A8(u8 layer);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_080DBED4(u8 selector, u8 flag, void *skip, void *arg);

static inline void fill16(const u16 *source, void *destination, u32 size)
{
    func_0814186C(source, destination, 0x01000000 | (size / 2));
}

u32 func_080E0E98(void *task, Descriptor080E0E98 *descriptor,
                  Payload080E0E98 *payload)
{
    u8 delay;
    u16 value;
    s16 offset;
    u16 first_zero;
    u16 second_zero;
    u32 third_zero;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->variant = descriptor->variant;
        payload->object = descriptor->object;
        payload->value = descriptor->value;
        break;
    case 1:
        g_control_flags_03000940.bldcnt_lo = 0;
        break;
    case 0x100:
        delay = 60;
        switch (payload->selector) {
        case 5:
        case 6:
            if (func_080DD6F4(payload->object) == 4) {
                func_080DE10C(payload->object, 0x98);
                payload->countdown = 20;
                goto next;
            }
            func_080DE10C(payload->object, 60);
            break;
        case 10:
            func_080DE10C(payload->object, 0x9C);
            goto next;
        default:
            value = 60;
            if (payload->selector == 18)
                value = 84;
            func_080DE10C(payload->object, value);
            if (payload->selector == 9)
                delay = 50;
            break;
        }
        payload->overlay = func_080DE4B0(payload->object, &payload->ready, 1,
                                         -1, 0, delay, 0, task);
    next:
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        if (payload->overlay != 0 && payload->ready == 0)
            break;
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        offset = 0;
        if (payload->selector == 10)
            offset = 16;
        payload->coordinate_task =
            func_080D6098(payload->x, payload->y + offset, 0, 0,
                          data_08395AA8[payload->selector],
                          payload->outputs,
                          data_08395A4C[payload->selector], task);
        payload->first_records =
            func_080DFD8C(data_08395ADC[payload->selector], 1, 4, 0, task);
        func_080D7220(data_088F5568, 0, 2, payload->x, payload->y + offset, 0);
        payload->script = func_080D3E9C(data_0894D8C8, task);
        payload->second_records = func_080DFD8C(data_08395AD4, 1, 4, 0, task);
        if (payload->selector == 6) {
            payload->countdown = 55;
            func_080E0608(&payload->motion, payload->y, payload->y - 72, 20);
        }
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->selector == 6) {
            if (payload->countdown != 0) {
                payload->countdown--;
                break;
            }
            if (!func_080E0690(&payload->motion)) {
                func_080E064C(&payload->motion);
                func_080107D4(payload->outputs[0], payload->x,
                              payload->motion.current, 0);
                break;
            }
        }
        payload->script = func_080D3F08(payload->script);
        if (payload->script != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->overlay = func_080DBA5C(payload->overlay);
        if (payload->overlay != 0)
            break;
        first_zero = 0;
        fill16(&first_zero, data_03003920, 0x80);
        second_zero = 0;
        fill16(&second_zero, data_03003920 + 0x100, 0xE0);
        third_zero = 0;
        func_08141868(&third_zero, data_0600FFC0, 0x01000010);
        if (payload->selector == 4) {
            payload->countdown = 16;
            descriptor->phase++;
        } else {
            descriptor->phase = 2;
        }
        break;
    case 0x103:
        if (--payload->countdown == 0) {
            payload->script = func_080D3E9C(data_08395ABF, task);
            payload->first_records =
                func_080DFD8C(data_08395B84, 1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x104:
        payload->script = func_080D3F08(payload->script);
        if (payload->script == 0) {
            func_080DBED4(5, 0, 0, payload->object);
            payload->script = func_080D3E9C(data_08395AC9, task);
            descriptor->phase++;
        }
        break;
    case 0x105:
        payload->script = func_080D3F08(payload->script);
        if (payload->script == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
