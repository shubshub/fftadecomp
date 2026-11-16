#include "ffta.h"

// 0x0809D128..0x0809D2F8: 464 bytes, 217 instructions.

typedef struct {
    s8 x;
    s8 z;
    u8 height;
    u8 unknown_03;
} RoutePoint;

typedef struct {
    u8 unknown_00[0xFC];
    u8 movement_type;
    u8 movement_mode;
    s8 destination_x;
    s8 destination_z;
} ObjectData;

typedef struct {
    ObjectData *data;
    u8 unknown_04[0x18];
    u8 flags;
    u8 unknown_1D[2];
    u8 direction;
    u8 unknown_20[0x60];
    void *owner;
} SceneObject;

typedef struct {
    u16 counter;
    u16 phase;
} Status;

typedef struct {
    SceneObject *object;
    RoutePoint *route;
    u8 unknown_08[0x10];
    u16 length;
    u16 index;
    u16 current;
    u16 initial;
    u16 phase_b;
    u16 phase_c;
    u16 phase_d;
    u8 state;
    s8 direction;
    u8 frame;
    u8 flags;
    u8 unknown_2A[0xB2];
    Status status;
    u8 unknown_E0[0x44];
} MovementState;

typedef struct {
    SceneObject *object;
    MovementState *movement;
    RoutePoint route[24];
    u8 count;
    u8 unknown_69[3];
    u16 active;
    u8 unknown_6E[0x46];
} MovementSlot;

typedef struct {
    u32 unknown_00;
    u8 flags;
    u8 unknown_05[3];
    MovementSlot slots[13];
} MovementSlots;

extern void *func_08022840(u32 size);
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC[])(void *, const void *, u32);
u32 func_0809A53C(SceneObject *object);
void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);
void func_0809A570(void *object, u32 clear, u32 set);
s32 func_0809B014(SceneObject *object, RoutePoint *route, s32 count,
                 s8 destination_x, s8 destination_z);
s32 func_08148A98(RoutePoint *route, s32 count);
SceneObject *func_08099644(void *owner, s8 x, s8 z);

static inline void set_phases(MovementState *state, u16 a, u16 b, u16 c,
                              u16 d)
{
    state->initial = a;
    state->phase_b = b;
    state->phase_c = c;
    state->phase_d = d;
    state->current = a;
}

static inline void set_state(MovementState *state, u8 value)
{
    state->state = value;
}

static inline void start_movement(MovementState *state, SceneObject *object,
                                  RoutePoint *route, s32 count)
{
    s32 index;

    state->object = object;
    state->route = route;
    state->length = count;
    state->status.counter = 0;
    state->index = 0;
    set_phases(state, 2, 3, 4, 2);
    set_state(state, 0);
    state->object->flags |= 4;
    state->frame = func_0809A53C(state->object);
    if (state->frame != 0)
        state->frame--;
    state->direction = state->object->direction;
    func_0809836C(state->object, 11, state->direction, 0);
    func_0809A570(state->object, 0, 2);
    state->flags &= ~2;
    if (object->data->movement_type == 2 &&
        object->data->movement_mode != 5) {
        s8 x = object->data->destination_x;
        s8 z = object->data->destination_z;

        if (func_0809B014(object, route, count, x, z)) {
            state->status.counter = 1;
            state->length = func_08148A98(route, count);
            for (index = 1; index < count - 1; index++) {
                if (func_08099644(object->owner, route[index].x,
                                  route[index].z))
                    route[index].height++;
            }
            state->flags |= 2;
        }
    }
}

static inline MovementSlot *find_free_slot(MovementSlots *slots)
{
    s32 index;

    for (index = 0; index < 13; index++) {
        if (slots->slots[index].object == 0)
            return &slots->slots[index];
    }
    return 0;
}

void func_0809D128(MovementSlots *slots, SceneObject *object,
                   RoutePoint *route, s32 count)
{
    MovementSlot *slot = find_free_slot(slots);

    slot->object = object;
    if (slot->movement == 0) {
        MovementState *movement = func_08022840(sizeof(MovementState));

        g_callbacks_0836D4B8[0](movement, sizeof(MovementState));
        movement->status.phase = 0;
        slot->movement = movement;
    }
    slots->flags |= 1;
    data_0836D4BC[0](slot->route, route, count * sizeof(RoutePoint));
    slot->count = count;
    g_callbacks_0836D4B8[0](&slot->active, 0x48);
    start_movement(slot->movement, slot->object, slot->route, slot->count);
    slot->active = 1;
}
