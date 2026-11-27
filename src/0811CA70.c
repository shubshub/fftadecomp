#include "control_flags.h"

// Target: complete [0x0811CA70, 0x0811CC9C), 556 bytes, including the
// literal pools at 0x0811CB00, 0x0811CB44, 0x0811CBD0, 0x0811CC4C and
// 0x0811CC98.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *unit;
} Descriptor0811CA70;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation0811CA70;

typedef struct {
    u16 counter;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    void *unit;
    void *handle;
    void *sprite;
    void *timeline;
    void *child;
    Interpolation0811CA70 interpolation;
    void *result;
} Payload0811CA70;

struct BgAffineSrc {
    s32 texX;
    s32 texY;
    s16 scrX;
    s16 scrY;
    s16 sx;
    s16 sy;
    u16 alpha;
};

struct BgAffineDst {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 dx;
    s32 dy;
};

extern const u8 data_08149FA4[];
extern const u8 data_083A6D04[];
extern const u8 data_083A6D5C[];
extern const u8 data_083A6D54[];
extern const u16 data_083A6D1C[];
extern const u8 data_088F104C[];
extern const u8 data_0894DB48[];
extern const u8 data_08949F18[];
extern u8 data_0600FFC0[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080DBDC8(void *unit, s16 *x, s16 *y);
extern s8 func_080DBC88(void *unit);
extern void *func_080D7A70(const void *resource, u8 palette, void *parent);
extern void *func_080D3AF8(void);
extern void func_08000B68(void *entry, u32 first, void *second, u16 count);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *handle);
extern void func_080DE10C(void *unit, u16 duration);
extern void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                           u16 value, void *parent);
extern void func_080D49FC(u32 first, u32 second, u32 third, s16 x, s16 y);
extern void func_0800BC90(u8 index, u8 enabled, u8 value);
extern void *func_080D4B64(u32 index, const void *resource, u16 size,
                           u32 type);
extern void func_08003620(u8 value);
extern u16 func_080035A8(u8 index);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void func_080E0608(Interpolation0811CA70 *state, s16 start, s16 end,
                          s16 duration);
extern void func_080E064C(Interpolation0811CA70 *state);
extern void func_08141864(const struct BgAffineSrc *src,
                          struct BgAffineDst *dst, s32 count);
extern void func_080032F8(const struct BgAffineDst *dst, u8 layer);
extern u8 func_080E0690(Interpolation0811CA70 *state);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D4D2C(void *sprite, u8 index);

u32 func_0811CA70(void *task, Descriptor0811CA70 *descriptor,
                  Payload0811CA70 *payload)
{
    u16 offsets[4];
    struct BgAffineSrc src;
    struct BgAffineDst dst;
    u8 index;

    switch (descriptor->phase) {
    case 0:
        func_081443FC(offsets, data_08149FA4, sizeof(offsets));
        payload->unit = descriptor->unit;
        func_080DBDC8(payload->unit, &payload->x, &payload->y);
        index = func_080DBC88(payload->unit);
        payload->handle = func_080D7A70(data_083A6D04, 2, task);
        payload->x += offsets[index];
        payload->y -= 0x26;
        func_08000B68(func_080D3AF8(), 0, data_0600FFC0, 0x10);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->handle = func_080D7ABC(payload->handle);
        if (payload->handle)
            break;
        func_080DE10C(payload->unit, 0x18);
        payload->result = func_080DFD8C(data_083A6D5C, 1, 4, 0, task);
        payload->counter = 0x14;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->counter)
            break;
        func_080D49FC(0, 2, 1, payload->x, payload->y);
        func_0800BC90(0, 0, 2);
        payload->sprite = func_080D4B64(0, data_088F104C, 0xBA, 6);
        func_08003620(1);
        g_control_flags_03000940.display |= func_080035A8(2);
        payload->timeline = func_080D3E9C(data_0894DB48, task);
        payload->child = func_080D4704(data_08949F18, task);
        func_080E0608(&payload->interpolation, 0, -0x80, 0x1C);
        payload->result = func_080DFD8C(data_083A6D54, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        func_080E064C(&payload->interpolation);
        src.texX = 0x2000;
        src.texY = 0x3000;
        src.scrX = payload->x;
        src.scrY = payload->y;
        src.sx = data_083A6D1C[payload->counter];
        src.sy = data_083A6D1C[payload->counter];
        src.alpha = payload->interpolation.current << 8;
        func_08141864(&src, &dst, 1);
        func_080032F8(&dst, 2);
        payload->counter++;
        if (func_080E0690(&payload->interpolation))
            descriptor->phase++;
        break;
    case 0x103:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        payload->child = func_080D4774(payload->child);
        if (payload->child)
            break;
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
