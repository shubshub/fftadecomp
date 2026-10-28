#include "ffta.h"

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
    SceneObject *object;
    RoutePoint *route;
    u8 unknown_08[0x10];
    u16 length;
    u16 index;
    u16 initial_phase;
    u16 phase_a;
    u16 phase_b;
    u16 phase_c;
    u16 phase_d;
    u8 state;
    s8 direction;
    u8 frame;
    u8 flags;
    u8 unknown_2A[0xB2];
    u16 adjusted;
} MovementState;

u32 func_0809A53C(SceneObject *object);
void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);
void func_0809A570(void *object, u32 clear, u32 set);
s32 func_0809B014(SceneObject *object, RoutePoint *route, s32 count,
                 s8 destination_x, s8 destination_z);
s32 func_08148A98(RoutePoint *route, s32 count);
SceneObject *func_08099644(void *owner, s8 x, s8 z);

void func_0809D464(MovementState *state, SceneObject *object,
                   RoutePoint *route, s32 count)
{
    s32 index;
    RoutePoint *point;

    state->object = object;
    state->route = route;
    state->length = count;
    state->adjusted = 0;
    state->index = 0;
    state->phase_a = 2;
    state->phase_b = 3;
    state->phase_c = 4;
    state->phase_d = 2;
    state->initial_phase = 2;
    state->state = 0;
    state->object->flags |= 4;
    state->frame = func_0809A53C(state->object);
    if (state->frame != 0)
        state->frame--;
    state->direction = state->object->direction;
    func_0809836C(state->object, 11, state->direction, 0);
    func_0809A570(state->object, 0, 2);
    state->flags &= ~2;

    if (object->data->movement_type == 2 &&
        object->data->movement_mode != 5 &&
        func_0809B014(object, route, count,
                     object->data->destination_x,
                     object->data->destination_z)) {
        state->adjusted = 1;
        state->length = func_08148A98(route, count);
        for (index = 1, point = route + 1; index < count - 1; index++, point++) {
            if (func_08099644(object->owner, point->x, point->z))
                point->height++;
        }
        state->flags |= 2;
    }
}
