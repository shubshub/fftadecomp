#include "ffta.h"
#include "effect_task.h"

/* 0x081009A8..0x08100CFE: complete 854-byte target. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 mode;
} Descriptor081009A8;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 unknown_06;
    u8 mode;
    u8 property;
    u8 ready;
    u16 unknown_0a;
    void *output;
    void *coordinate_result;
    void *actor_object;
    void *actor;
    void *initial_child;
    void *position_children[1];
    void *coordinate_child;
    void *resource_child;
    void *first_child;
    void *second_child;
    void *effect_child;
    void *animation_child;
    void *record_child;
    InterpolationState motion[2];
} Payload081009A8;

typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;

extern const u8 data_0839E99C[];
extern const u8 data_0839E9F8[];
extern const Position data_088F5B0C;
extern const u8 data_0894D7E4[];
extern const u8 data_0894A8D0[];
extern const u8 data_089484DC[];
extern const u8 data_0839E9CC[];
extern const u8 data_0839E9FC[];
extern const u8 data_0839E9E4[];
extern const u8 data_0839EA04[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D7220(const Position *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern u8 func_080E0690(InterpolationState *);
extern void func_080E064C(InterpolationState *);
extern void func_080107D4(void *, s16, s16, u16);
extern void func_080D7468(const Position *, u8, s16, s16);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern u8 func_080DD580(void *);
extern u16 func_080DD6F4(const void *);
extern void func_080DE10C(void *, u16);
extern void *func_080DF978(void *, u32, u32, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

extern u8 func_080DE1F0(void *);

u32 func_081009A8(void *task, Descriptor081009A8 *descriptor,
                  Payload081009A8 *payload)
{
    u8 mode;
    u8 status;
    u8 index;
    u16 kind;
    u16 attribute;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->actor = descriptor->object;
        mode = 4;
        if (payload->mode != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor,
            data_0839E99C, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        status = func_080D3B54(payload->actor);
        if (status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->animation_child = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready, data_0839E9F8,
            5, status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->actor, 0);
        payload->countdown = 20;
        descriptor->phase++;
    case 0x102:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        status = func_080D8B4C();
        if (status != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        func_080D7220(&data_088F5B0C, 0, 2, payload->x,
            (s16)(payload->y - 16), status);
        payload->resource_child = func_080D3E9C(data_0894D7E4, task);
        payload->first_child = func_080D4704(data_0894A8D0, task);
        payload->second_child = func_080D4704(data_089484DC, task);
        payload->coordinate_child = func_080D6098(payload->x,
            (s16)(payload->y - 16), 0, 0, 1, payload->position_children,
            data_0839E9CC, task);
        payload->record_child = func_080DFD8C(data_0839E9FC, 1, 4, 0, task);
        func_080E0608(&payload->motion[0], (s16)(payload->y - 16),
            payload->y, 34);
        func_080E0608(&payload->motion[1], (s16)(payload->y - 16),
            (s16)(payload->y - 24), 34);
        descriptor->phase++;
        break;
    case 0x103:
        if (!func_080E0690(&payload->motion[0])) {
            func_080E064C(&payload->motion[0]);
            func_080E064C(&payload->motion[1]);
            for (index = 0; index < 1; index++) {
                if (payload->position_children[index] != 0)
                    func_080107D4(payload->position_children[index], payload->x,
                        payload->motion[0].current, 0);
            }
            func_080D7468(&data_088F5B0C, 2, payload->x,
                payload->motion[1].current);
            break;
        }
        payload->resource_child = func_080D3F08(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->property = func_080DD580(payload->actor_object);
        if (payload->property != 0) {
            attribute = 12;
            kind = func_080DD6F4(payload->coordinate_result);
            if (kind == 8 || kind == 15)
                attribute = 0x44;
            func_080DE10C(payload->coordinate_result, attribute);
            payload->effect_child = func_080DF978(payload->coordinate_result,
                30, 35, task);
        }
        descriptor->phase++;
        break;
    case 0x104:
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        payload->effect_child = func_080DCFE4(payload->actor_object,
            data_0839E9E4, 12, 0, 4, task, 0);
        if (payload->property != 0)
            payload->record_child = func_080DFD8C(data_0839EA04, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        if (!func_080DE1F0(payload->output))
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
