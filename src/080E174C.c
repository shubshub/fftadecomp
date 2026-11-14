#include "ffta.h"

// Target 0x080E174C..0x080E1A38 (748 bytes, complete span including literal pool):
// f0b54f464646c0b486b080460f1c151c39880648814260d081420edc012900d152e1012904dc00291ad04de1010100008020
// 4000814230d046e10848814200d1cee0814200dab3e00130814200d105e10130814200d117e136e1000003010000b88aa871
// 0006000e0c2805d1b5214900081cfa8a801808e00e2802d1f88ac93003e00f2802d1f88ae530a880f88aa87078682861b868
// 286316e12869291c0a312a1c0c32faf7eafaa8790d2812d12869faf744fa000600160122012800dc00222869002100914346
// 019305210423fdf7c1ff686238880130f5e0686afaf718f9061c6e62002e00d0eee0202028812869fef738f80006002801d0
// 1020288101208146a8790d2823d00d2802dc0c2802d031e00f282fdca8880a216a5eab8929895b1a1b041b14002100910849
// 019107210291414603910021f4f7a8fb6861a8790f2818d10322914615e00000007e01061648a9780a23ea5eab892c891b1b
// 1b041b14f624a40000940724019402960396f4f700fa6861686900212ff749fc28693c21fcf71dfc2869e91d01235b420024
// 0094352201920294424603924a46fcf7e1fd2862388801308de00000306b5008e879002800d187e0686901212ff728fc0648
// 43460093012104220023fef738faa8621e2028803888013074e08c5b3908288801382880000400286dd10a21685ea9892031
// 2a89891a09040914144baa79d218127800922a1c18320192114baa799200d218126802924246039200220023f4f794fbe861
// a879c0000b49401843460093012104220023fef702faa862686901212ff70bfc06202880388801303ae0a85a39084c5a3908
// dc5a39082888002809d0013828800004040c002c03d168692ff734fd6c61e869f4f7b6fbe861002822d1388801301ee0286a
// faf741f8061c2e62002e18d104a806800f4c211c0f4a5ff03eff684612300680802189006418211c0b4a5ff034ff059605a8
// 09490a4a5ff02cff02203880002006b018bc9846a146f0bc02bc0847203900034000000170000001c0ff000610000001

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    void *unknown_08;
    u8 unknown_0C[8];
    u16 selector;
    u16 index;
} Descriptor080E174C;

typedef struct {
    u16 countdown;
    u8 index;
    u8 unknown_03;
    u16 sprite;
    u8 selector;
    u8 ready;
    u16 offset;
    u16 x;
    u16 y;
    u8 unknown_0E[2];
    void *object;
    void *sprite_object;
    void *outputs[1];
    void *animation;
    void *fade_out;
    void *flash;
    void *effect;
    u8 unknown_2C[4];
    void *unknown_30;
} Work080E174C;

extern const u8 data_08506B30[];
extern u8 data_06017E00[];
extern const u8 data_08395B8C[];
extern const u8 data_08395AA8[];
extern const void *const data_08395A4C[];
extern const u8 data_08395ADC[][8];
extern u16 data_03003920[];
extern u32 data_0600FFC0[];

extern void func_080DBDC8(void *object, u16 *x, u16 *y);
extern s8 func_080DBC88(void *object);
extern void *func_080DF7A0(void *object, u32 first, u32 second, u32 third,
                          u32 fourth, void *parent);
extern void *func_080DBA5C(void *task);
extern u8 func_080DF8B0(void *object);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void *func_080D5FD8(u16 id, u8 layer, s16 x, s16 y, u16 width,
                           u32 tiles, u8 bank, void *parent);
extern void func_0801115C(void *object, u8 enabled);
extern void func_080111A8(void *object, u8 enabled);
extern void func_08011428(void *object);
extern void func_080DE10C(void *object, u16 value);
extern void *func_080DE4B0(void *object, u8 *ready, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void *buffer, const void *records, void *parent);
extern void *func_080D6134(void *task);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);

static inline void fill_halfwords(const u16 *source, u16 *destination, u32 control)
{
    func_0814186C(source, destination, control);
}

u32 func_080E174C(void *task, Descriptor080E174C *descriptor, Work080E174C *work)
{
    u16 zero_a;
    u16 zero_b;
    u32 zero_c;
    void *child;
    u16 *buffer;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        work->selector = descriptor->selector;
        if (work->selector == 12)
            work->sprite = descriptor->index + 0x16A;
        else if (work->selector == 14)
            work->sprite = descriptor->index + 0xC9;
        else if (work->selector == 15)
            work->sprite = descriptor->index + 0xE5;
        work->index = descriptor->index;
        work->object = descriptor->object;
        work->unknown_30 = descriptor->unknown_08;
        break;
    case 1:
        break;
    case 0x100:
        func_080DBDC8(work->object, &work->x, &work->y);
        if (work->selector == 13) {
            s32 kind = func_080DBC88(work->object);
            u32 high = 1;

            if (kind <= 1)
                high = 0;
            work->flash = func_080DF7A0(work->object, 5, high, 4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x101:
        child = func_080DBA5C(work->flash);
        work->flash = child;
        if (child != 0)
            break;
        work->offset = 0x20;
        if (func_080DF8B0(work->object) != 0)
            work->offset = 0x10;
        mode = 1;
        switch (work->selector) {
        case 12:
        case 14:
        case 15:
            work->sprite_object = func_080D5FD8(work->sprite, 0, work->x,
                                                work->y - work->offset, 0,
                                                (u32)data_06017E00, 7, task);
            if (work->selector == 15)
                mode = 3;
            break;
        case 13:
            work->sprite_object = func_080D5CC0(data_08506B30, work->index,
                                                work->x, work->y - work->offset,
                                                0x3D8, 7, 0, 0);
            break;
        }
        func_0801115C(work->sprite_object, 0);
        func_080DE10C(work->object, 0x3C);
        work->fade_out = func_080DE4B0(work->object, &work->ready, mode, -1, 0,
                                       0x35, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (work->ready == 0)
            break;
        func_0801115C(work->sprite_object, 1);
        work->effect = func_080DFD8C(data_08395B8C, 1, 4, 0, task);
        work->countdown = 0x1E;
        descriptor->phase++;
        break;
    case 0x103:
        if (--work->countdown != 0)
            break;
        work->animation = func_080D6098(work->x, work->y + 0x20 - work->offset,
                                        0, 0, data_08395AA8[work->selector],
                                        work->outputs,
                                        data_08395A4C[work->selector], task);
        work->effect = func_080DFD8C(data_08395ADC[work->selector], 1, 4,
                                     0, task);
        func_080111A8(work->sprite_object, 1);
        work->countdown = 6;
        descriptor->phase++;
        break;
    case 0x104:
        if (work->countdown != 0 && --work->countdown == 0) {
            func_08011428(work->sprite_object);
            work->sprite_object = 0;
        }
        work->animation = func_080D6134(work->animation);
        if (work->animation == 0)
            descriptor->phase++;
        break;
    case 0x105:
        child = func_080DBA5C(work->fade_out);
        work->fade_out = child;
        if (child != 0)
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
