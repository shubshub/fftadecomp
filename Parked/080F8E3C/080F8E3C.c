#include "ffta.h"

// Target [0x080F8E3C, 0x080F9094), 600 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u8 kind;
    u8 unknown_15;
    u16 mode;
} Descriptor080F8E3C;

typedef struct {
    u16 unknown_00;
    u16 value;
    u32 unknown_04[4];
} Settings080F8E3C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u8 index;
    u8 mode;
    u8 ready;
    u8 unknown_09[3];
    void *object;
    void *coordinate_result;
    void *source;
    void *initial_child;
    void *sprite_child;
    void *animation_child;
    void *object_child;
    void *scene_child;
    Settings080F8E3C settings;
    void *record_child;
} Payload080F8E3C;

typedef void (*CopyBuffer080F8E3C)(void *, const void *, u32);

extern const void *const data_0839C354[];
extern const u8 data_08149D64[];
extern const u8 data_08149D68[];
extern const u8 data_0839C39C[];
extern const void *const data_0839C388[];
extern const u16 data_0839C394[];
extern const void *const data_0839C360[];
extern const u8 data_0839C3A0[][8];
extern const CopyBuffer080F8E3C data_0836D4BC[];
extern const Settings080F8E3C data_0839C36C;
extern const u16 data_0839C380[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern void *func_080D5CC0(const void *, u8, s16, s16, u16, u8, u8, u8);
extern void func_08011118(void *, u8);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_08011484(void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_080F8E3C(void *task, Descriptor080F8E3C *descriptor,
                  Payload080F8E3C *payload)
{
    u8 mode;
    u8 failed;
    s8 slot;
    void *selected;
    u8 first[4];
    u8 second[4];

    switch (descriptor->phase) {
    case 0:
        payload->index = descriptor->kind - 0x71;
        payload->mode = descriptor->mode;
        payload->source = descriptor->object;
        mode = 2;
        if (payload->mode != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->source,
            data_0839C354[payload->index], mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        func_081443FC(first, data_08149D64, sizeof(first));
        func_081443FC(second, data_08149D68, sizeof(second));
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        failed = func_080D3B54(payload->source);
        if (failed) {
            descriptor->phase = 2;
            break;
        }
        payload->scene_child = func_080DDF68(payload->source,
            &payload->object, 0x54, 1, &payload->ready, data_0839C39C,
            0, 0, task);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        slot = func_080DBC88(payload->object);
        payload->sprite_child = func_080D5CC0(data_0839C388[payload->index],
            first[slot], payload->x, payload->y,
            data_0839C394[payload->index], 6, 0, 1);
        func_08011118(payload->sprite_child, second[slot]);
        payload->animation_child = func_080D4724(
            data_0839C360[payload->index], task, 0x1E);
        payload->record_child = func_080DFD8C(data_0839C3A0[payload->index],
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->source, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        selected = func_080DD4A4(payload->source, 0);
        payload->coordinate_result = func_080DD748(selected,
            &payload->x, &payload->y, 0);
        data_0836D4BC[0](&payload->settings, &data_0839C36C,
            sizeof(payload->settings));
        payload->settings.value = data_0839C380[payload->index];
        payload->object_child = func_080DCFE4(selected, &payload->settings,
            12, 0, 4, task, 0);
        descriptor->phase++;
        break;
    case 0x102:
        payload->sprite_child = func_08011484(payload->sprite_child);
        if (payload->sprite_child != 0)
            break;
        if (func_080DE1F0(payload->object) == 0)
            break;
        payload->animation_child = func_080D4774(payload->animation_child);
        if (payload->animation_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
