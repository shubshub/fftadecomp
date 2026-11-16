#include "ffta.h"

/* Complete [0x0809D464, 0x0809D58A): 294 bytes, 141 instructions.
   NOT A CLEAN MATCH: the bytes are identical only because `point` starts out
   holding `state`, a value the function never reads through it.  The ROM
   keeps one register (r4) for both the state pointer of the first half and
   the route cursor of the loop, and the entry copy of the first argument
   (sl) for the one store after func_08148A98.  No ordinary reason for that
   initial value has been found. */

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
} MovementState;

u32 func_0809A53C(SceneObject *object);
void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);
void func_0809A570(void *object, u32 clear, u32 set);
s32 func_0809B014(SceneObject *object, RoutePoint *route, s32 count,
                 s8 destination_x, s8 destination_z);
s32 func_08148A98(RoutePoint *route, s32 count);
SceneObject *func_08099644(void *owner, s8 x, s8 z);

/* The ROM also keeps these two as functions of their own, func_0809D620 and
   func_0809D638; here they are expanded in line. */
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

void func_0809D464(MovementState *state, SceneObject *object,
                   RoutePoint *route, s32 count)
{
    RoutePoint *point = (RoutePoint *)state;
    s32 length;
    s32 last;
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
            length = func_08148A98(route, count);
            point = route;
            state->length = length;
            last = count - 1;
            point++;
            for (index = 1; index < last; index++, point++) {
                if (func_08099644(object->owner, point->x, point->z))
                    point->height++;
            }
            state->flags |= 2;
        }
    }
}
