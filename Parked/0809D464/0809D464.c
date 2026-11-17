#include "ffta.h"

/* Complete [0x0809D464, 0x0809D58A): 294 bytes, 141 instructions.
 * f0b557464e464546e0b481b082460f1c161c1d1c544627606660002300202583dc210919
 * 894608806083022003210422e08321846284a084a083201c263003702268117f04200843
 * 10772068fdf744f8011c221c283211700806002801d0481e10702068c07f211c27310870
 * 206800228a560b210023faf747ff206800210222fdf744f8211c29310a78fd2010400870
 * 3a68101cfc300078884602283bd1101cfd300078052836d0111cfe31101cff300023cb56
 * 0078000600160090381c311c2a1cfdf775fd002825d0012049460880301c291cabf0aefa
 * 51460883681e341d012812dd023d381c80300068002161560122a256fcf774f8002802d0
 * a0780130a070013d0434002dedd140460178022008434146087001b038bc9846a146aa46
 * f0bc01bc0047
 *
 * Not a match (286 bytes).  The ROM keeps the state pointer in two registers:
 * sl, set at 0x0809D470 and read only by the length store at 0x0809D53C, and
 * r4, copied from it at 0x0809D478, which serves every other state access and
 * becomes the route cursor at 0x0809D542.  This source keeps it in r4 alone.
 */

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
    u8 mode;
    u8 flags;
    u8 unknown_2A[0xB2];
    Status status;
} MovementState;

typedef struct {
    u8 unknown_00[0x26];
    u8 value;
} ByteState;

u32 func_0809A53C(SceneObject *object);
void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);
void func_0809A570(void *object, u32 clear, u32 set);
s32 func_0809B014(SceneObject *object, RoutePoint *route, s32 count,
                  s8 destination_x, s8 destination_z);
s32 func_08148A98(RoutePoint *route, s32 count);
SceneObject *func_08099644(void *owner, s8 x, s8 z);

/* An inlined copy of func_0809D620 (src/0809D620.c). */
static inline void inlined_0809D620(Rec5 *rec, u16 a, u16 b, u16 c, u16 d) {
    rec->f2 = a;
    rec->f3 = b;
    rec->f4 = c;
    rec->f5 = d;
    rec->f1 = a;
}

/* An inlined copy of func_0809D638 (src/0809D638.c). */
static inline void inlined_0809D638(ByteState *state, u8 value)
{
    state->value = value;
}

void func_0809D464(MovementState *state, SceneObject *object,
                   RoutePoint *route, s32 count)
{
    RoutePoint *point;
    s32 i;

    state->object = object;
    state->route = route;
    state->length = count;
    state->status.counter = 0;
    state->index = 0;
    inlined_0809D620((Rec5 *)state, 2, 3, 4, 2);
    inlined_0809D638((ByteState *)state, 0);
    state->object->flags |= 4;
    state->mode = func_0809A53C(state->object);
    if (state->mode != 0)
        state->mode--;
    state->direction = state->object->direction;
    func_0809836C(state->object, 11, state->direction, 0);
    func_0809A570(state->object, 0, 2);
    state->flags &= ~2;
    if (object->data->movement_type == 2 && object->data->movement_mode != 5) {
        s8 x = object->data->destination_x;
        s8 z = object->data->destination_z;

        if (func_0809B014(object, route, count, x, z)) {
            state->status.counter = 1;
            state->length = func_08148A98(route, count);
            point = route + 1;
            for (i = 1; i < count - 1; i++, point++) {
                if (func_08099644(object->owner, point->x, point->z))
                    point->height++;
            }
            state->flags |= 2;
        }
    }
}
