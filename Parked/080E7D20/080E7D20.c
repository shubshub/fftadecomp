/* 0x080E7D20, complete target [0x080E7D20, 0x080E7F4C), 556 bytes.
 * f0b54f464646c0b484b080460f1c151c398880204000814228d0814202dc0029
 * 0cd0fbe00448814200d1bfe00130814200d1ebe0f2e0000001010000b88a2870
 * f88a68707868a860a91c2a1d0023f5f7ebfce860044801210091062100220023
 * ecf726fcdae000000c9c8e0802202b5e0421685e0090002002210022ecf72efe
 * 3e492a789000401801683d4852001218128800200623ecf7d5fe286102201bf7
 * f3fb384a1188014311800222a85e0422a95e354b2a78d218127800922a1c1432
 * 0192324b2a789200d218126802924246039200220123eef74ff9e8612c492878
 * 8000401800684146ecf748f82862294928788000401800684146ecf773fc6862
 * 25492a789000401800682449521812784146ecf777fca8626978012081460840
 * 0226002800d00426a8681d491d4c2a78121913780096424601922a7812191278
 * 02920c22f5f7bef8e8626978484608400822002800d010221349287880004018
 * 006804210a434146009101210023f7f77dff2863388801304fe00000c07c3908
 * cc7c390840090003a07c3908947c3908d47c3908a47c3908b07c3908bc7c3908
 * e47c3908f87c39081c7d3908286944420443e40f0021ecf729ff2861002c08d0
 * 00282bd102201bf75ffb0f4a1188814311802869002821d1e869eef71bf9e861
 * 00281bd1286aebf7ffff2862002815d1281c24300221ecf7e1fc000600280dd0
 * 3888013009e0000040090003e86af3f795fde862002801d102203880002004b0
 * 18bc9846a146f0bc02bc0847
 */

#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 flags;
} Descriptor080E7D20;

typedef struct {
    u8 selector;
    u8 flags;
    s16 coordinate_x;
    s16 coordinate_y;
    u8 unknown_06[2];
    void *wrapper;
    void *underlying;
    void *resource;
    u8 unknown_14[8];
    void *coordinate_task;
    void *sequence_task;
    void *children[2];
    void *wrapper_task;
    void *record_task;
} Payload080E7D20;

extern void *func_080DD748(void *wrapper, s16 *coordinate_x,
                          s16 *coordinate_y, s16 *coordinate_z);
extern void func_080D45D0(const void *record, u8 bank, u8 alternate,
                         u8 first, u8 count);
extern void func_080D49FC(u8 index, u8 mode, u16 value,
                         s16 coordinate_x, s16 coordinate_y);
extern void *func_080D4B64(u8 index, const void *record, u16 value, u8 mode);
extern u16 func_080035A8(u8 index);
extern void *func_080D6098(s16 coordinate_x, s16 coordinate_y,
                          s16 coordinate_z, u8 mode, u16 count,
                          void *storage, const void *record, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080D4704(const void *record, void *parent);
extern void *func_080D4724(const void *record, void *parent, u16 value);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                          u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_080D4D2C(void *resource, u8 mode);
extern void *func_080D6134(void *task);
extern void *func_080D3F08(void *task);
extern u32 func_080D48DC(void **tasks, u16 count);
extern void *func_080DBA5C(void *task);

u32 func_080E7D20(void *task, Descriptor080E7D20 *descriptor,
                  Payload080E7D20 *payload)
{
    const void *const *resource_records = (const void *const *)0x08397CC0;
    const u16 *resource_values = (const u16 *)0x08397CCC;
    const u8 *coordinate_counts = (const u8 *)0x08397CA0;
    const void *const *coordinate_records = (const void *const *)0x08397C94;
    const void *const *sequence_records = (const void *const *)0x08397CD4;
    const void *const *first_child_records = (const void *const *)0x08397CA4;
    const void *const *second_child_records = (const void *const *)0x08397CB0;
    const u8 *second_child_values = (const u8 *)0x08397CBC;
    const u8 *wrapper_delays = (const u8 *)0x08397CF8;
    const void *const *record_records = (const void *const *)0x08397D1C;
    u16 *shadow = (u16 *)0x03000940;
    u16 mask;
    u32 had_resource;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->flags = descriptor->flags;
        payload->wrapper = descriptor->object;
        payload->underlying = func_080DD748(payload->wrapper,
            &payload->coordinate_x, &payload->coordinate_y, 0);
        func_080D45D0((const void *)0x088E9C0C, 6, 0, 0, 1);
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, payload->coordinate_x, payload->coordinate_y);
        payload->resource = func_080D4B64(0, resource_records[payload->selector],
            resource_values[payload->selector], 6);
        mask = func_080035A8(2);
        *shadow |= mask;
        payload->coordinate_task = func_080D6098(payload->coordinate_x,
            payload->coordinate_y, 0, 1, coordinate_counts[payload->selector],
            payload->unknown_14, coordinate_records[payload->selector], task);
        payload->sequence_task = func_080D3E9C(
            sequence_records[payload->selector], task);
        payload->children[0] = func_080D4704(
            first_child_records[payload->selector], task);
        payload->children[1] = func_080D4724(
            second_child_records[payload->selector], task,
            second_child_values[payload->selector]);
        payload->wrapper_task = func_080DCFE4(payload->wrapper,
            (const void *)0x08397CE4, 0x0c, wrapper_delays[payload->selector],
            (payload->flags & 1) ? 4 : 2, task,
            wrapper_delays[payload->selector]);
        payload->record_task = func_080DFD8C(record_records[payload->selector],
            1, ((payload->flags & 1) ? 0x10 : 8) | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        had_resource = payload->resource != 0;
        payload->resource = func_080D4D2C(payload->resource, 0);
        if (had_resource && payload->resource == 0) {
            mask = func_080035A8(2);
            *shadow &= ~mask;
        }
        if (payload->resource != 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->sequence_task = func_080D3F08(payload->sequence_task);
        if (payload->sequence_task != 0)
            break;
        if ((u8)func_080D48DC(payload->children, 2) != 0)
            descriptor->phase++;
        break;
    case 0x102:
        payload->wrapper_task = func_080DBA5C(payload->wrapper_task);
        if (payload->wrapper_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
