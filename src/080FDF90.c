// Target: complete [0x080FDF90, 0x080FE232), 674 bytes.
#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Point080FDF90;

typedef struct {
    u16 phase;
    u16 unknown_02;
    const Point080FDF90 *from;
    const Point080FDF90 *to;
    u8 unknown_0c[8];
    u16 palette;
    u16 direction;
} Descriptor080FDF90;

typedef struct {
    u16 palette;
    u16 unknown_02;
    Point080FDF90 from;
    Point080FDF90 to;
    u16 duration;
    u8 unknown_16[0x80];
    s8 direction;
    u8 unknown_97;
    void *sprite;
    void *parts[4];
    s16 path_x[60];
    s16 path_y[60];
    s16 path_z[60];
    void *motion;
} Payload080FDF90;

typedef struct {
    s16 x;
    s16 y;
} Offset080FDF90;

typedef struct {
    Offset080FDF90 entries[4];
} OffsetTable080FDF90;

typedef void (*BufferCopier080FDF90)(void *destination, const void *source,
                                     u32 size);

extern const BufferCopier080FDF90 data_0836D4BC[];
extern const OffsetTable080FDF90 data_08149DB4;
extern const u16 data_08149DC4[];

extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_080D5FD8(u16 id, u8 layer, s16 x, s16 y, s16 width,
                           u32 tiles, u8 bank, void *parent);
extern void func_08010884(void *object, u8 enabled);
extern void func_0801115C(void *object, u8 enabled);
extern void func_080111A8(void *object, u8 enabled);
extern void **func_08010FEC(void *object);
extern void *func_08011348(void *entries, const void *data, u16 index,
                           u8 layer, s16 x, s16 y, s16 width, u16 tile,
                           u8 mode, u16 attributes);
extern u32 func_08141898(u32 value);
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void *func_080D6238(void *scene, const Point080FDF90 *from,
                           const Point080FDF90 *to, u16 delay, u16 duration,
                           s16 *x, s16 *y, s16 *z, u16 behavior,
                           void *parent);
extern u8 func_080D63C8(void *motion);
extern void func_080D659C(void *motion, void **part, u16 value);
extern u8 func_080D6478(void *motion);
extern void func_080D6524(void *motion);
extern void func_08011428(void *object);
extern void func_080D5F74(void **objects, u16 count);

u32 func_080FDF90(void *task, Descriptor080FDF90 *descriptor,
                  Payload080FDF90 *payload)
{
    const BufferCopier080FDF90 *copy;

    switch (descriptor->phase) {
    case 0:
        payload->palette = descriptor->palette;
        payload->direction = descriptor->direction;
        copy = data_0836D4BC;
        copy[0](&payload->from, descriptor->from, 8);
        copy[0](&payload->to, descriptor->to, 8);
        break;
    case 1:
        break;
    case 0x100: {
        OffsetTable080FDF90 offsets = data_08149DB4;
        void **entries;
        u8 i;

        payload->from.x += offsets.entries[payload->direction].x;
        payload->from.y += 0x18;
        payload->from.z += offsets.entries[payload->direction].y;
        payload->to.y += 0x18;
        payload->sprite = func_080D5FD8(payload->palette, 2, payload->from.x,
            payload->from.y, payload->from.z, 0x06017BA0, 8, task);
        func_08010884(payload->sprite, 1);
        func_0801115C(payload->sprite, 0);
        entries = func_08010FEC(payload->sprite);
        for (i = 0; i < 4; i++) {
            payload->parts[i] = func_08011348(*entries, 0, 0, 2,
                payload->from.x, payload->from.y, payload->from.z, 0x3DD,
                8, 0x86);
            func_0801115C(payload->parts[i], 0);
            func_080111A8(payload->parts[i], 1);
        }
        descriptor->phase++;
        break;
    }
    case 0x101: {
        s16 dx = payload->to.x - payload->from.x;
        s16 dy = payload->to.y - payload->from.y;
        s16 dz = payload->to.z - payload->from.z;
        u32 squared;
        u16 distance;

        squared = dx * dx;
        squared += dz * dz;
        squared <<= 8;
        distance = (u16)func_08141898(squared) >> 4;
        squared = distance * distance;
        squared += dy * dy;
        squared <<= 8;
        distance = (u16)func_08141898(squared) >> 4;
        payload->duration = func_08141870(distance, 6);
        if (payload->duration <= 2)
            payload->duration = 3;
        payload->motion = func_080D6238(&payload->sprite, &payload->from,
            &payload->to, 0x10, payload->duration, payload->path_x,
            payload->path_y, payload->path_z, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102: {
        u16 values[4];
        u8 i;

        func_081443FC(values, data_08149DC4, sizeof(values));
        if (func_080D63C8(payload->motion) == 0)
            break;
        for (i = 0; i < 4; i++)
            func_080D659C(payload->motion, &payload->parts[i], values[i]);
        descriptor->phase++;
        break;
    }
    case 0x103:
        break;
    case 0x104:
        if (func_080D6478(payload->motion) == 0)
            break;
        func_080D6524(payload->motion);
        payload->motion = 0;
        func_08011428(payload->sprite);
        payload->sprite = 0;
        func_080D5F74(payload->parts, 4);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
