// Target: complete [0x08101A8C, 0x08101CCC), 576 bytes, 237 instructions.
// The structures are offset views of the observed accesses only.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor08101A8C;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 status;
    u8 index;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0a[2];
    void *status_child;
    void *actor_object;
    void *coordinate_result;
    void *selected_object;
    void *second_sprite;
    void *first_sprite;
    void *coordinate_child;
    u8 unknown_28[4];
    void *actor;
    void *initial_child;
    void *actor_child;
    void *record_child;
} Payload08101A8C;

extern const u8 data_0839ED34[];
extern const u8 data_08149DD8[4];
extern const u8 data_08149DDC[4];
extern const u8 data_08502560[];
extern const u8 data_08502ED8[];
extern const u8 data_0839ED90[];
extern const u8 data_0839ED64[];
extern const u8 data_0839ED98[];
extern const u8 data_0839ED7C[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_08102B48(void *, u8, u8 *, void *);
extern void *func_080DD47C(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DBCD4(void *, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011118(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_08011484(void *);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_08102BA8(void *);
extern void *func_080DBA5C(void *);

u32 func_08101A8C(void *task, Descriptor08101A8C *descriptor,
                  Payload08101A8C *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u8 mode;

        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor,
            data_0839ED34, mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->status_child = func_08102B48(payload->actor, 2,
            &payload->status, task);
        if (payload->status_child == 0) {
            descriptor->phase = 2;
            break;
        }
        descriptor->phase++;
        break;
    case 0x101:
    {
        u8 kinds[4];
        u8 enables[4];

        func_081443FC(kinds, data_08149DD8, sizeof(kinds));
        func_081443FC(enables, data_08149DDC, sizeof(enables));
        if (payload->status == 0)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x103;
            break;
        }
        payload->actor_object = func_080DD47C(payload->actor);
        payload->selected_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->selected_object,
            &payload->x, &payload->y, 0);
        payload->index = func_080DBCD4(payload->coordinate_result,
            payload->actor_object);
        payload->first_sprite = func_080D5CC0(data_08502560,
            kinds[payload->index], payload->x, payload->y, 0x395, 7, 0, 0);
        payload->second_sprite = func_080D5CC0(data_08502ED8, 6,
            payload->x, payload->y, 0x3B3, 6, 0, 0);
        func_08011118(payload->first_sprite, enables[payload->index]);
        if (payload->index > 1)
            func_08011118(payload->second_sprite, 1);
        payload->record_child = func_080DFD8C(data_0839ED90, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102:
        payload->first_sprite = func_08011484(payload->first_sprite);
        if (payload->first_sprite != 0)
            break;
        if (func_080DD580(payload->selected_object) != 0) {
            payload->coordinate_child = func_080D6098(payload->x, payload->y,
                0, 1, 1, payload->unknown_28, data_0839ED64, task);
            payload->record_child = func_080DFD8C(data_0839ED98, 1, 4, 0,
                task);
        }
        payload->actor_child = func_080DCFE4(payload->selected_object,
            data_0839ED7C, 12, 0x28, 4, task, 0);
        descriptor->phase++;
        break;
    case 0x103:
        payload->second_sprite = func_08011484(payload->second_sprite);
        if (payload->second_sprite != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->status_child = func_08102BA8(payload->status_child);
        if (payload->status_child != 0)
            break;
        payload->actor_child = func_080DBA5C(payload->actor_child);
        if (payload->actor_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
