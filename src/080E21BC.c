#include "ffta.h"
#include "control_flags.h"

// Target 0x080E21BC, 476 bytes (complete span including literal pool):
// f0b586b0061c0f1c151c398880204000814218d0814202dc00290bd0cce00448814225d00130814200d185e0c4e0000001010000b88aa870f88a28717868e860b8682863b8e03224e8683c21fbf780ffe868e91c01235b42002200920194029203960122fcf746f9a86238880130a2e0a86a002803d0e878002800d19ce0e868a91d2a1c0832f9f7c1fd06202b5e28892038000400140090002002210022f2f7cffb1d491d4a00200623f2f77dfce861022021f79bf91a4a1188014311801948311cf1f70dfe28621748311cf2f73cfa68620621685e0822a95e144baa78d218127800922a1c10320192114baa789200d21812680292039600220123f3f7eefea8610c480096022104220023fdf760fde862388801304ee070188f08cf0300004009000390d69408f0c59408a85a39084c5a3908ac5b3908e8690021f2f718fde861002838d1286af1f700fe2862002832d1022021f74af91a4a118881431180686af2f729fa6862002825d1a869f3f703ffa86100281fd1a86af9f791fb061cae62002e18d104a806800f4c211c0f4a5ff08efa684612300680802189006418211c0b4a5ff084fa059605a809490a4a5ff07cfa02203880002006b0f0bc02bc0847000040090003203900034000000170000001c0ff000610000001

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    void *unknown_08;
    u8 unknown_0C[8];
    u16 field_14;
    u16 field_16;
} Descriptor080E21BC;

typedef struct {
    u16 unknown_00;
    u8 style;
    u8 finished;
    u8 unknown_04;
    u8 unknown_05;
    s16 x;
    s16 y;
    void *object;
    void *outputs[2];
    void *coordinate_child;
    void *sprite;
    void *effect_child;
    void *particle_child;
    void *event_child;
    void *record_child;
    void *unknown_30;
} Work080E21BC;

extern const u8 data_088F1870[];
extern const u8 data_0894D690[];
extern const u8 data_0894C5F0[];
extern const u8 data_08395AA8[];
extern const void *const data_08395A4C[];
extern const u8 data_08395BAC[];
extern u16 data_03003920[];
extern u32 data_0600FFC0[];

extern void func_080DE10C(void *object, u16 command);
extern void *func_080DE4B0(void *object, u8 *result, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *parent);
extern void *func_080DBA5C(void *object);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u32 index, u32 type, u32 flags, s16 x, s16 y);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u32 index);
extern void *func_080D3E9C(const void *resource, void *context);
extern void *func_080D4704(const void *, void *);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void **outputs, const void *entries, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D4D2C(void *resource, u8 mode);
extern void *func_080D3F08(void *handle);
extern void *func_080D4774(void *task);
extern void *func_080D6134(void *handle);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);

static inline void fill_halfwords(const u16 *source, u16 *destination,
                                  u32 control)
{
    func_0814186C(source, destination, control);
}

u32 func_080E21BC(void *task, Descriptor080E21BC *descriptor,
                  Work080E21BC *work)
{
    u16 zero_a;
    u16 zero_b;
    u32 zero_c;
    u16 *buffer;

    switch (descriptor->phase) {
    case 0:
        work->style = descriptor->field_14;
        work->unknown_04 = descriptor->field_16;
        work->object = descriptor->object;
        work->unknown_30 = descriptor->unknown_08;
        break;
    case 0x100: {
        u8 delay = 0x32;

        func_080DE10C(work->object, 0x3C);
        work->event_child = func_080DE4B0(work->object, &work->finished, 1,
                                          -1, 0, delay, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (work->event_child != 0 && work->finished == 0)
            break;
        func_080DBDC8(work->object, &work->x, &work->y);
        func_080D49FC(0, 2, 0, work->x, work->y - 0x20);
        work->sprite = func_080D4B64(0, data_088F1870, 0x3CF, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        work->effect_child = func_080D3E9C(data_0894D690, task);
        work->particle_child = func_080D4704(data_0894C5F0, task);
        work->coordinate_child = func_080D6098(work->x, work->y, 0, 1,
            data_08395AA8[work->style], work->outputs,
            data_08395A4C[work->style], task);
        work->record_child = func_080DFD8C(data_08395BAC, 2, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        work->sprite = func_080D4D2C(work->sprite, 0);
        if (work->sprite)
            break;
        work->effect_child = func_080D3F08(work->effect_child);
        if (work->effect_child)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        work->particle_child = func_080D4774(work->particle_child);
        if (work->particle_child)
            break;
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (work->coordinate_child)
            break;
        work->event_child = func_080DBA5C(work->event_child);
        if (work->event_child)
            break;
        zero_a = 0;
        buffer = data_03003920;
        fill_halfwords(&zero_a, buffer, 0x01000040);
        zero_b = 0;
        buffer += 0x100;
        fill_halfwords(&zero_b, buffer, 0x01000070);
        zero_c = 0;
        func_08141868(&zero_c, data_0600FFC0, 0x01000010);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
