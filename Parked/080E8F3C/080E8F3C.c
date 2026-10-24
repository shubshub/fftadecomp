/* 0x080E8F3C, complete target [0x080E8F3C, 0x080E921C), 736 bytes.
 * f0b5474680b484b080460f1c161c398880246400a1421dd0a14202dc00290bd051e10448814200d194e00130814200d1f8e048e101010000b88a3070f88a70707868f060b11d321c08320023f4f7defb306138e1394d0620335e3089103800040014009000240194281c00210222eef7fff90621725e3389103b1b041b149c462f49b078400040180023c05e0090b078400040180021405e01900294281c02216346edf727ffb0780130b0703078012805d180221201101c7389c018708102201af7d4fa1f4a1188014311801e484146eaf746ff306271780124201c08400223002800d00423f0683278910089188900164a89180093454601953c2202920c223723f3f7d1ff70622320b0807178201c08400822002800d010220d49307880004018006804210a434146009101210023f6f78efeb06238880130c3e0d04e8f08448439084009000330d7940884843908bc843908b0781f282ad813480623f25e3389103b1b041b14104cb178490009190025495f0091b178490009190024095f0191718902910221edf7b4feb0780130b070307801281bd180252d01281c71894018708114e00000d04e8f084484390820280dd119480623f25e3389103b1b041b1400940194002102910221edf792feb0880138b0800004002874d1f068f4f731fa0006002811d00624305f0825715f02220092321c14320192094a02924246039200220123ecf7a9fff0610520b0801f20b0703888013054e00000d04e8f08148439080125b08800280fd13078002805d1b07800280bd00138b07008e080235b01181c74890019708101e00138b08020480621725e3389103b1b041b1498461d4cb178490009190023c95e0091b178490009190024095f01917189029102214346edf737fe306a002800d10025eaf79dfe3062002816d1002d06d002201af7e5f90e4a118881431180f069ecf7a4fff061002807d1706af2f732fc7062002801d102203880002004b008bc9846f0bc02bc0847d04e8f084484390840090003
 */

#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 mode;
    u16 flags;
} Descriptor080E8F3C;

typedef struct {
    u8 mode;
    u8 flags;
    u8 curve_index;
    u8 unknown_03;
    u16 timer;
    s16 coordinate_x;
    s16 coordinate_y;
    u16 angle;
    void *wrapper;
    void *underlying;
    u8 unknown_14[8];
    void *coordinate_task;
    void *sequence_task;
    void *wrapper_task;
    void *record_task;
} Payload080E8F3C;

extern void *func_080DD748(void *wrapper, s16 *coordinate_x,
                          s16 *coordinate_y, s16 *coordinate_z);
extern void func_080D73AC(const void *record, u8 bank, u8 layer,
                         s16 coordinate_x, s16 coordinate_y, u8 flags);
extern void func_080D6E30(const void *record, u8 layer,
                         s16 coordinate_x, s16 coordinate_y,
                         s16 scale_x, s16 scale_y, u16 angle);
extern u16 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080DCFE4(void *wrapper, const void *record, u8 count,
                          u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern u32 func_080DD580(const void *wrapper);
extern void *func_080D6098(s16 coordinate_x, s16 coordinate_y,
                          s16 coordinate_z, u8 mode, u16 count,
                          void *storage, const void *record, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080E8F3C(void *task, Descriptor080E8F3C *descriptor,
                  Payload080E8F3C *payload)
{
    const void *affine_record = (const void *)0x088F4ED0;
    const s16 *curve = (const s16 *)0x08398444;
    const u8 *wrapper_records = (const u8 *)0x08398484;
    const void *const *record_records = (const void *const *)0x083984BC;
    u16 *shadow = (u16 *)0x03000940;
    u16 mask;
    u32 had_sequence;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->flags = descriptor->flags;
        payload->wrapper = descriptor->object;
        payload->underlying = func_080DD748(payload->wrapper,
            &payload->coordinate_x, &payload->coordinate_y, 0);
        break;
    case 0x100:
        func_080D73AC(affine_record, 0, 2, payload->coordinate_x,
            (s16)(payload->coordinate_y - 16), 0);
        func_080D6E30(affine_record, 2, payload->coordinate_x,
            (s16)(payload->coordinate_y - 16), curve[payload->curve_index],
            curve[payload->curve_index], 0);
        payload->curve_index++;
        if (payload->mode == 1)
            payload->angle += 0x800;
        mask = func_080035A8(2);
        *shadow |= mask;
        payload->sequence_task = func_080D3E9C((const void *)0x0894D730, task);
        payload->wrapper_task = func_080DCFE4(payload->wrapper,
            wrapper_records + payload->mode * 20, 12, 55,
            (payload->flags & 1) ? 4 : 2, task, 60);
        payload->timer = 35;
        payload->record_task = func_080DFD8C(record_records[payload->mode],
            1, ((payload->flags & 1) ? 0x10 : 8) | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->curve_index <= 31) {
            func_080D6E30(affine_record, 2, payload->coordinate_x,
                (s16)(payload->coordinate_y - 16), curve[payload->curve_index],
                curve[payload->curve_index], payload->angle);
            payload->curve_index++;
            if (payload->mode == 1)
                payload->angle += 0x800;
        } else if (payload->curve_index == 32) {
            func_080D6E30(affine_record, 2, payload->coordinate_x,
                (s16)(payload->coordinate_y - 16), 0x100, 0x100, 0);
        }
        payload->timer--;
        if (payload->timer == 0) {
            if ((u8)func_080DD580(payload->wrapper) != 0)
                payload->coordinate_task = func_080D6098(payload->coordinate_x,
                    payload->coordinate_y, 0, 1, 2, payload->unknown_14,
                    (const void *)0x08398414, task);
            payload->timer = 5;
            payload->curve_index = 31;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (payload->timer == 0) {
            if (payload->mode == 0) {
                if (payload->curve_index != 0)
                    payload->curve_index--;
            } else {
                payload->angle += 0x1000;
            }
        } else {
            payload->timer--;
        }
        func_080D6E30(affine_record, 2, payload->coordinate_x,
            (s16)(payload->coordinate_y - 16), curve[payload->curve_index],
            curve[payload->curve_index], payload->angle);
        had_sequence = payload->sequence_task != 0;
        payload->sequence_task = func_080D3F08(payload->sequence_task);
        if (payload->sequence_task != 0)
            break;
        if (had_sequence) {
            mask = func_080035A8(2);
            *shadow &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->wrapper_task = func_080DBA5C(payload->wrapper_task);
        if (payload->wrapper_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
