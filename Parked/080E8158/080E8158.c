/* 0x080E8158, 556 owned target bytes:
 * f0b54f464646c0b484b080460f1c151c398880204000814226d0814202dc00290cd0fbe00448814200d1bbe00130814200d1ebe0f2e0000001010000b88a2870f88a68707868a860a91c2a1d0023f5f7cffae860f5f7c6fa0006002800d1dde0a8880838a880d9e002202b5e41492878400040180088a9884018000400140090002002210022ecf70dfc3b492a78900040180168394852001218128800200623ecf7b4fc286102201bf7d2f9344a1188014311800222a85e0422a95e314b2a78d218127800922a1c143201922e4b2a789200d218126802924246039200220123edf72eff2862294928788000401800684146ebf727fe686225492a789000401800682449521812784146ecf75ffaa86269780120814608400226002800d00426a8681d491d4c2a78121913780096424601922a781219127802920c22f4f7a6fee8626978484608400822002800d010221349287880004018006804210a434146009101210023f7f765fd28633888013053e000006c7f39083c7f3908487f390840090003387f39082c7f3908607f3908507f39085c7f3908787f39088c7f3908b07f39080126286941420143cc0f0021ecf710fd2861002800d00026002c08d0002806d102201bf743f90f4a118881431180286aedf702ff2862002800d00026686aebf7e5fd6862002800d00026a86aecf714faa862002800d00026002e0dd03888013009e0000040090003e86af3f779fbe862002801d102203880002004b018bc9846a146f0bc02bc0847
 */
#include "ffta.h"

typedef struct CallbackDescriptor {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 flags;
} CallbackDescriptor;

typedef struct SelectorPollState {
    u8 selector;
    u8 flags;
    s16 position_x;
    s16 position_y;
    u8 unknown_06[2];
    void *wrapper;
    void *underlying;
    void *resource;
    u8 unknown_14[12];
    void *coordinate_task;
    void *sequence_task;
    void *single_task;
    void *wrapper_task;
    void *record_task;
} SelectorPollState;

void *func_080DD748(void *wrapper, s16 *position_x, s16 *position_y,
                   s16 *position_z);
u32 func_080DD73C(void *underlying);
void func_080D49FC(u8 first, u8 second, u16 third, s16 position_x,
                   s16 position_y);
void *func_080D4B64(u8 first, const void *record, u16 value, u8 mode);
u16 func_080035A8(u8 index);
void *func_080D6098(s16 position_x, s16 position_y, s16 position_z,
                   u8 mode, u16 count, void *output, const void *record,
                   void *parent);
void *func_080D3E9C(const void *record, void *parent);
void *func_080D4724(const void *record, void *parent, u16 value);
void *func_080DCFE4(void *wrapper, const void *record, u8 count, u16 delay,
                   u16 flags, void *parent, s16 initial_delay);
void *func_080DFD8C(const void *record, u8 count, u16 flags, u16 delay,
                   void *parent);
void *func_080D4D2C(void *resource, u8 mode);
void *func_080D6134(void *task);
void *func_080D3F08(void *task);
void *func_080D4774(void *task);
void *func_080DBA5C(void *task);

u32 func_080E8158(void *task, void *descriptor_data, void *payload)
{
    CallbackDescriptor *descriptor = descriptor_data;
    SelectorPollState *state = payload;
    u16 *resource_mask = (u16 *)0x03000940;
    const u8 *delays = (const u8 *)0x08397F8C;
    u32 all_finished;
    u32 had_resource;
    u16 mask;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        state->selector = descriptor->selector;
        state->flags = descriptor->flags;
        state->wrapper = descriptor->object;
        state->underlying = func_080DD748(state->wrapper, &state->position_x,
                                         &state->position_y, 0);
        if ((u8)func_080DD73C(state->underlying))
            state->position_y = (s16)((u16)state->position_y - 8);
        break;

    case 0x100:
        func_080D49FC(0, 2, 0, state->position_x,
                     (s16)(((const u16 *)0x08397F6C)[state->selector]
                           + (u16)state->position_y));
        state->resource = func_080D4B64(
            0, ((const void *const *)0x08397F3C)[state->selector],
            ((const u16 *)0x08397F48)[state->selector], 6);
        mask = func_080035A8(2);
        *resource_mask |= mask;
        state->coordinate_task = func_080D6098(
            state->position_x, state->position_y, 0, 1,
            ((const u8 *)0x08397F38)[state->selector], state->unknown_14,
            ((const void *const *)0x08397F2C)[state->selector], task);
        state->sequence_task = func_080D3E9C(
            ((const void *const *)0x08397F60)[state->selector], task);
        state->single_task = func_080D4724(
            ((const void *const *)0x08397F50)[state->selector], task,
            ((const u8 *)0x08397F5C)[state->selector]);
        flags = (state->flags & 1) ? 4 : 2;
        state->wrapper_task = func_080DCFE4(
            state->wrapper, (const void *)0x08397F78, 12,
            delays[state->selector], flags, task, delays[state->selector]);
        state->record_task = func_080DFD8C(
            ((const void *const *)0x08397FB0)[state->selector], 1,
            ((state->flags & 1) ? 0x10 : 8) | 4, 0, task);
        descriptor->phase++;
        break;

    case 0x101:
        all_finished = 1;
        had_resource = state->resource != 0;
        state->resource = func_080D4D2C(state->resource, 0);
        if (state->resource != 0)
            all_finished = 0;
        if (had_resource && state->resource == 0) {
            mask = func_080035A8(2);
            *resource_mask &= ~mask;
        }
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task != 0)
            all_finished = 0;
        state->sequence_task = func_080D3F08(state->sequence_task);
        if (state->sequence_task != 0)
            all_finished = 0;
        state->single_task = func_080D4774(state->single_task);
        if (state->single_task != 0)
            all_finished = 0;
        if (all_finished)
            descriptor->phase++;
        break;

    case 0x102:
        state->wrapper_task = func_080DBA5C(state->wrapper_task);
        if (state->wrapper_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
