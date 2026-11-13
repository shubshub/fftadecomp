// Target: complete [0x080E9554, 0x080E97F4), 672 bytes.
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    s16 selector;
} Descriptor080E9554;

typedef struct {
    u8 kind;
    u8 attached;
    u8 unknown_02[2];
    s16 x;
    s16 y;
    void *underlying;
    u8 storage[4];
    void *coordinate_task;
    void *sprite;
    void *first_effect;
    void *second_effect;
    void *sequence;
    void *wrapper;
    void *record_task;
    u16 first_palette[16];
    u16 second_palette[16];
    void *tiles;
} Payload080E9554;

extern u16 data_03003980[];
extern u8 data_06005800[];
extern const u8 data_088EA1F4[];
extern const u8 data_088ED5BC[];
extern const u8 data_083985A8[];
extern const u8 data_083985C0[];
extern const u8 data_08949374[];
extern const u8 data_08949F18[];
extern const u8 data_0894D69C[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080D45D0(const void *resource, u8 first, u8 second,
                          u8 third, u8 fourth);
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *pointer);
extern void *func_080D3AF8(void);
extern void func_08000A98(void *record, const void *source,
                          void *destination, u16 count);
extern void func_080D8CD4(void *wrapper);
extern void func_080D38B4(void);
extern u8 func_0801BDB0(void);
extern void *func_080DD4A4(void *wrapper, u8 index);
extern void *func_080DD760(void *source, s16 *x, s16 *y, s16 *z, s16 offset);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u8 index, u8 type, u16 flags, s16 x, s16 y);
extern void func_0800BC4C(u32 index, u32 value);
extern void *func_080D4B64(u8 index, const void *resource, u16 size, u8 type);
extern void func_0800BDA4(void *sprite, u8 enabled);
extern u16 func_080035A8(u8 index);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void *storage, const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void func_080D47DC(void *task, u16 value);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080DFD8C(const void *resource, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D6134(void *task);
extern void func_080D4D14(void *sprite, u32 flags);

u32 func_080E9554(void *task, Descriptor080E9554 *descriptor,
                  Payload080E9554 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u16 fill;
        u16 *fill_source;

        payload->kind = 0;
        payload->attached = 0;
        if (descriptor->selector == 0x61) {
            payload->kind = 1;
        } else if (descriptor->selector == 0x18C) {
            payload->kind = 2;
            payload->attached = 1;
        }
        if (payload->attached == 0)
            payload->wrapper = descriptor->object;
        else
            payload->underlying = descriptor->object;
        func_0814186C(data_03003980, payload->first_palette, 16);
        func_0814186C(data_03003980 + 0x100, payload->second_palette, 16);
        /* CpuFill16(0, data_03003980, 32): the SDK's vu16 temporary,
         * spelled through a pointer until fftadecomp-kit#164. */
        fill_source = &fill;
        *fill_source = 0;
        func_0814186C(fill_source, data_03003980, 0x01000010);
        func_080D45D0(data_088EA1F4, 9, 1, 0, 1);
        payload->tiles = func_0800A654(0x800);
        func_08000A98(func_080D3AF8(), data_06005800, payload->tiles, 0x400);
        if (payload->attached == 0)
            func_080D8CD4(payload->wrapper);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (func_0801BDB0() != 0)
            break;
        if (payload->attached == 0) {
            void *source = func_080DD4A4(payload->wrapper, 0);

            if (payload->kind == 0)
                payload->underlying = func_080DD760(source, &payload->x,
                    &payload->y, 0, -2);
            else
                payload->underlying = func_080DD760(source, &payload->x,
                    &payload->y, 0, -1);
        } else
            func_080DBDC8(payload->underlying, &payload->x, &payload->y);
        func_080D49FC(0, 2, 0, payload->x, (s16)(payload->y - 8));
        func_0800BC4C(0, 1);
        payload->sprite = func_080D4B64(0, data_088ED5BC, 0x240, 9);
        func_0800BDA4(payload->sprite, 1);
        g_control_flags_03000940.display |= func_080035A8(2);
        payload->coordinate_task = func_080D6098(payload->x, payload->y, 0, 1,
            1, payload->storage, data_083985A8, task);
        payload->first_effect = func_080D4704(data_08949374, task);
        payload->second_effect = func_080D4704(data_08949F18, task);
        func_080D47DC(payload->first_effect, 9);
        payload->sequence = func_080D3E9C(data_0894D69C, task);
        if (payload->attached == 0)
            payload->record_task = func_080DFD8C(data_083985C0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->sequence = func_080D3F08(payload->sequence);
        if (payload->sequence != 0)
            break;
        payload->first_effect = func_080D4774(payload->first_effect);
        if (payload->first_effect != 0)
            break;
        payload->second_effect = func_080D4774(payload->second_effect);
        if (payload->second_effect != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        func_08000A98(func_080D3AF8(), payload->tiles, data_06005800, 0x400);
        descriptor->phase++;
        break;
    case 0x102:
        func_0814186C(payload->first_palette, data_03003980, 16);
        func_0814186C(payload->second_palette, data_03003980 + 0x100, 16);
        func_0800A668(payload->tiles);
        payload->tiles = 0;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
