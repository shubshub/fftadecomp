#include "ffta.h"

/* Target [0x080E6714, 0x080E691A):
f0b584b0051c0f1c141c398880204000814235d0814202dc00290bd0eee00448814200d1bae00130814200d1dee0e5e001010000b88a2070f88a60707868a060a11c221d0023f6f7f5ffe060607800280ad1044801210091062100220023edf72dffcbe01ca38e08044801210091062100220223edf722ffc0e000001ca38e080220235e0421605e0090002002210022eef72af93749384a00200623eef7d8f92061012125f7f4fa02201cf7f3fe334a1188014311800222a05e0422a15e304b6278d21812780092221c143201922d4b62789200d21812680292039500220123eff750fc20622848291cedf74dfb60622648291cedf77cffa0622548291cedf777ffe062a06a0121edf7c0ffe06a0121edf7bcff21780126301c08400223002800d00423a0686278910089188900194a891800930195322202920c223223f6f7c7fb20632178301c08400822002800d010221149607880004018006804210a43009501210023f9f787fa60633888013043e000007cdb8e08c603000040090003d0743908c8743908bcd794085495940864959408d47439080c753908606a41420143ce0fedf726fb051c6562002d25d1002e10d0201c28300221eef733f820690021eef71dfa256102201cf763fe064a118881431180206aeff722fc206200280cd13888013008e040090003206bf5f7abf82063002801d102203880002004b0f0bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 flags;
    u16 variant;
} EffectDescriptor;

typedef struct {
    u8 flags;
    u8 variant;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    void *object;
    void *underlying;
    void *resource;
    u8 unknown_14[12];
    void *coordinate_child;
    void *sequence_child;
    void *effect_children[2];
    void *wrapper_child;
    void *record_child;
} EffectWork;

extern void *func_080DD748(void *object, s16 *first, s16 *second, s16 *third);
extern void func_080D45D0(const void *record, u8 slot, u8 bank, u8 first, u8 count);
extern void func_080D49FC(u8 first, u8 second, u16 third, s16 x, s16 y);
extern void *func_080D4B64(u8 first, const void *record, u16 value, u8 mode);
extern void func_0800BDA4(void *resource, u8 enabled);
extern u16 func_080035A8(u8 index);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                         void *buffer, const void *records, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080D4704(const void *record, void *parent);
extern void func_080D47A0(void *child, u8 enabled);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void *func_080D3F08(void *child);
extern void func_080D4938(void **children, u16 count);
extern void func_080D4D14(void *resource, u8 mode);
extern void *func_080D6134(void *child);
extern void *func_080DBA5C(void *child);

u32 func_080E6714(void *task, void *descriptor_arg, void *payload_arg)
{
    EffectDescriptor *descriptor = descriptor_arg;
    EffectWork *work = payload_arg;
    u16 *display_mask = (u16 *)0x03000940;
    u16 flags;
    u32 had_sequence;

    switch (descriptor->phase) {
    case 0:
        work->flags = descriptor->flags;
        work->variant = descriptor->variant;
        work->object = descriptor->object;
        work->underlying = func_080DD748(work->object, &work->x, &work->y, 0);
        if (work->variant == 0)
            func_080D45D0((const void *)0x088EA31C, 6, 0, 0, 1);
        else
            func_080D45D0((const void *)0x088EA31C, 6, 0, 2, 1);
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, work->x, work->y);
        work->resource = func_080D4B64(0, (const void *)0x088EDB7C, 0x3C6, 6);
        func_0800BDA4(work->resource, 1);
        *display_mask |= func_080035A8(2);
        work->coordinate_child = func_080D6098(
            work->x, work->y, 0, 1, ((const u8 *)0x083974D0)[work->variant],
            work->unknown_14, ((const void *const *)0x083974C8)[work->variant], task);
        work->sequence_child = func_080D3E9C((const void *)0x0894D7BC, task);
        work->effect_children[0] = func_080D4704((const void *)0x08949554, task);
        work->effect_children[1] = func_080D4704((const void *)0x08949564, task);
        func_080D47A0(work->effect_children[0], 1);
        func_080D47A0(work->effect_children[1], 1);
        flags = (work->flags & 1) ? 4 : 2;
        work->wrapper_child = func_080DCFE4(
            work->object, (const u8 *)0x083974D4 + 20 * work->variant,
            12, 50, flags, task, 50);
        flags = (work->flags & 1) ? 0x10 : 8;
        work->record_child = func_080DFD8C(
            ((const void *const *)0x0839750C)[work->variant], 1, flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        had_sequence = work->sequence_child != 0;
        work->sequence_child = func_080D3F08(work->sequence_child);
        if (work->sequence_child == 0) {
            if (had_sequence) {
                func_080D4938(work->effect_children, 2);
                func_080D4D14(work->resource, 0);
                work->resource = 0;
                *display_mask &= ~func_080035A8(2);
            }
            work->coordinate_child = func_080D6134(work->coordinate_child);
            if (work->coordinate_child == 0)
                descriptor->phase++;
        }
        break;
    case 0x102:
        work->wrapper_child = func_080DBA5C(work->wrapper_child);
        if (work->wrapper_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
