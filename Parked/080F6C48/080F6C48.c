#include "ffta.h"

// Target: complete [0x080F6C48, 0x080F6E74), 556 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 side;
    u16 flags;
    u16 variant;
} Descriptor080F6C48;

typedef struct {
    u8 flags;
    s8 side;
    u8 variant;
    u8 unknown_03[3];
    s16 x;
    s16 y;
    s16 z;
    void *actor;
    void *position;
    void *objects[2];
    void *resource;
    void *animation;
    void *record;
} Payload080F6C48;

typedef struct {
    u8 unknown_00[20];
} AnimationEntry080F6C48;

struct Resource080D5E80;

extern const s8 data_08149D2C[4], data_08149D30[4], data_08149D34[4],
    data_08149D38[4];
extern const struct Resource080D5E80 data_085000D8;
extern const u8 data_08949DD8[], data_0894848C[];
extern const AnimationEntry080F6C48 data_0839BA28[];
extern const u8 data_0839BA60[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD73C(void *);
extern void func_080DB838(void *);
extern void *func_080D5E80(const struct Resource080D5E80 *, u16, s16, s16,
                           s16, u16, u8);
extern void func_08011118(void *, u8);
extern void func_08010884(void *, u8);
extern void func_08011058(void *, s8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D5F24(void **, u16);
extern void *func_080DBA5C(void *);

u32 func_080F6C48(void *task, Descriptor080F6C48 *descriptor,
                  Payload080F6C48 *payload)
{
    s8 first_a[4];
    s8 first_b[4];
    u8 palettes[4];
    s8 second_a[4];
    s8 second_b[4];
    s8 *first[2];
    s8 *second[2];
    u8 i;
    u8 mode;
    u8 bits;

    switch (descriptor->phase) {
    case 0:
        payload->side = descriptor->side;
        payload->flags = descriptor->flags;
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        payload->position = func_080DD748(payload->actor, &payload->x,
                                          &payload->y, &payload->z);
        if (func_080DD73C(payload->position))
            payload->y += 16;
        func_080DB838(payload->position);
        break;
    case 1:
        break;
    case 0x100:
        func_081443FC(first_a, data_08149D2C, sizeof(first_a));
        func_081443FC(first_b, data_08149D30, sizeof(first_b));
        first[0] = first_a;
        first[1] = first_b;
        func_081443FC(palettes, data_08149D34, sizeof(palettes));
        func_081443FC(second_a, data_08149D38, sizeof(second_a));
        func_081443FC(second_b, data_08149D2C, sizeof(second_b));
        second[0] = second_a;
        second[1] = second_b;
        for (i = 0; i < 2; i++) {
            if (first[i][payload->side] == -1)
                continue;
            payload->objects[i] = func_080D5E80(&data_085000D8, first[i][payload->side],
                payload->x, payload->y, payload->z, 0x392, 6);
            func_08011118(payload->objects[i], palettes[payload->side]);
            if (second[i][payload->side] == 0)
                func_08010884(payload->objects[i], 1);
            else
                func_08011058(payload->objects[i], second[i][payload->side]);
        }
        if (payload->variant == 0)
            payload->resource = func_080D4704(data_08949DD8, task);
        else
            payload->resource = func_080D4704(data_0894848C, task);
        if (payload->flags & 1)
            mode = 4;
        else
            mode = 2;
        payload->animation = func_080DCFE4(payload->actor,
            &data_0839BA28[payload->variant], 12, 26, mode, task, 26);
        if (payload->flags & 1)
            bits = 16;
        else
            bits = 8;
        payload->record = func_080DFD8C(data_0839BA60, 1, bits | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!func_080D5F24(payload->objects, 2))
            break;
        payload->resource = func_080D4774(payload->resource);
        if (payload->resource)
            break;
        payload->animation = func_080DBA5C(payload->animation);
        if (!payload->animation)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
