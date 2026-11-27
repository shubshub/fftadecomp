#include "ffta.h"

/* Complete [0x0809D128, 0x0809D2F8): 464 bytes, 217 instructions.
 * f0b557464e464546e0b484b091469846061c0025331c08330024221c1868002800d189e0
 * b433b43401350c2df5dd002739607d68002d0fd19220400085f76cfb041c3b480268201c
 * 92214900a5f06af8201cdc3045807c603179012000250843307134480821c9198a464146
 * 8a00036850464946a5f058f83c1c6834404620702b483e1c6c360268301c4821a5f04af8
 * 2478a04679680191386881460c1c206051466160002340462083211cdc3102910d806583
 * 022003210422e08321846284a084a083201c263003702268117f0420084310772068fdf7
 * 9df9011c221c2832117008060396002801d0481e10702068c07f211c2731087020680022
 * 8a560b210023fbf79ff8206800210222fdf79cf9211c29310a78fd201040087048460268
 * 101cfc3000780e1c022809d045e00000b8d43608bcd43608201c0830371877e7101cfd30
 * 0078052837d0111cfe31101cff300023cb560078000600160090484651464246fdf7c2fe
 * 002826d001200299088050464146abf0fbfb01990883404601383c1c0c34012813dd4546
 * 023d484680300068002161560122a256fcf7bef9002802d0a0780130a070013d0434002d
 * edd1317802200843307001200399088004b038bc9846a146aa46f0bc01bc0047
 *
 * Starts a movement for an object in the first free one of the thirteen
 * 0xB4-byte slots of the movement manager: allocates the slot's movement
 * state on first use (func_0809D428), marks the manager active, copies the
 * route into the slot, clears the slot's status block and starts the
 * movement on the copied route (func_0809D464), then marks the slot active.
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
    u8 unknown_E0[0x44];
} MovementState;

typedef struct {
    u8 unknown_00[0x26];
    u8 value;
} ByteState;

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

/* An inlined copy of func_0809D428 (src/0809D428.c). */
static inline MovementState *alloc_movement(void)
{
    MovementState *movement = func_08022840(sizeof(*movement));
    Status *status;

    g_callbacks_0836D4B8[0](movement, sizeof(*movement));
    status = &movement->status;
    status->phase = 0;
    return movement;
}

/* func_0809D464 in line: this text compiled on its own is byte-identical to
 * [0x0809D464, 0x0809D58A).
 *
 * The ROM keeps the state pointer twice: the formal spilled at [sp, #4]
 * (0x0809D1BE) and read back only for the length store (0x0809D2A2), and a
 * copy in r4 (0x0809D1C4) that serves every other access and becomes the
 * route cursor (0x0809D2AA).  `point` starting out as `state`, with the
 * length stored after `point = route`, is the only source found that keeps
 * the second copy: without it the spill and the reload go and the frame is
 * 12 bytes, not 16 (0x0809D132).
 *
 * The test chain: on the movement_type != 2 path the ROM has only the
 * unconditional branch at 0x0809D254, with the free-slot search's found
 * block placed after it (0x0809D260). */
static inline void start_movement(MovementState *state, SceneObject *object,
                                  RoutePoint *route, s32 count)
{
    RoutePoint *point = (RoutePoint *)state;
    s32 found;
    s32 length;
    s32 last;
    s32 index;

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
    if (object->data->movement_type != 2)
        found = 0;
    else if (object->data->movement_mode == 5)
        found = 0;
    else {
        s8 x = object->data->destination_x;
        s8 z = object->data->destination_z;

        found = func_0809B014(object, route, count, x, z);
    }
    if (found) {
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

static inline MovementSlot *find_free_slot(MovementSlots *slots)
{
    s32 index;

    for (index = 0; index <= 12; ++index) {
        if (slots->slots[index].object == 0)
            return &slots->slots[index];
    }
    return 0;
}

void func_0809D128(void *work, SceneObject *object, RoutePoint *route,
                   s32 count)
{
    MovementSlots *slots = work;
    MovementSlot *slot = find_free_slot(slots);

    /* BUG: find_free_slot returns 0 when all thirteen slots are in use and
     * nothing checks it: slot->object is then written to 0x00000000
     * (0x0809D158) and slot->movement read from 0x00000004 (0x0809D15A,
     * 0x0809D1BC), inside the BIOS region, and the movement is started
     * through whatever that read returns. */
#ifdef BUGFIX
    if (slot == 0)
        return;
#endif
    slot->object = object;
    if (slot->movement == 0)
        slot->movement = alloc_movement();
    slots->flags |= 1;
    data_0836D4BC[0](slot->route, route, count * sizeof(RoutePoint));
    slot->count = count;
    g_callbacks_0836D4B8[0](&slot->active, 0x48);
    start_movement(slot->movement, slot->object, slot->route, slot->count);
    slot->active = 1;
}
