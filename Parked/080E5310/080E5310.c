/* 0x080E5310: 296 target bytes, including referenced literals and alignment.
 * 70b584b0051c0e1c141c3188012900d182e0012902dc002905d07de080204000
 * 814251d078e000910020022100220023eff75cfb1c491d4a00200623eff70afc
 * a06102201ef728f9194a1188014311801848291ceff7cef920621748291ceef7
 * 95fde06104200090201d01901348029003957820602100220123f0f785fe6061
 * 0f48009001950220002100220023f4f799fa60620b480095012104220023faf7
 * edfca06238e0000068d98e081b03000040090003989494089cd69408186e3908
 * 686f3908ac6f3908e069eef795fde061002821d1206aeff7c5f9206200281bd1
 * a0690021eff79afca061002814d102201ef7d2f80b4a1188814311806069f0f7
 * 91fe6061002807d1606af4f7a3fb6062002801d102203080002004b070bc02bc
 * 0847000040090003
 */
#include "ffta.h"

typedef struct EffectSequenceWork {
    u8 unknown_00[0x14];
    void *coordinate_child;
    void *resource;
    void *sequence_child;
    void *effect_child;
    void *motion_child;
    void *record_child;
} EffectSequenceWork;

extern u16 func_080035A8(u8 index);
extern void func_080D49FC(u8 first, u8 second, u16 third, s16 fourth, s16 fifth);
extern void *func_080D4B64(u8 index, const void *record, u16 value, u8 mode);
extern void *func_080D4704(const void *record, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void *buffer, const void *record, void *parent);
extern void *func_080D98D4(u8 index, u16 first, u16 second, u16 third,
                           const void *record, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void *func_080D4D2C(void *resource, u8 mode);
extern void *func_080D6134(void *task);
extern void *func_080D9B64(void *task);

u32 func_080E5310(void *task, void *descriptor, void *payload)
{
    u16 *phase = descriptor;
    EffectSequenceWork *work = payload;
    u16 *shadow = (u16 *)0x03000940;
    u16 mask;

    switch (*phase) {
    case 0:
        func_080D49FC(0, 2, 0, 0, 0);
        work->resource = func_080D4B64(0, (const void *)0x088ED968, 0x31B, 6);
        mask = func_080035A8(2);
        *shadow |= mask;
        work->effect_child = func_080D4704((const void *)0x08949498, task);
        work->sequence_child = func_080D3E9C((const void *)0x0894D69C, task);
        work->coordinate_child = func_080D6098(120, 96, 0, 1, 4,
                                               (u8 *)work + 4,
                                               (const void *)0x08396E18, task);
        work->motion_child = func_080D98D4(2, 0, 0, 0,
                                           (const void *)0x08396F68, task);
        work->record_child = func_080DFD8C((const void *)0x08396FAC, 1, 4, 0, task);
        break;
    case 1:
        break;
    case 0x100:
        work->sequence_child = func_080D3F08(work->sequence_child);
        if (work->sequence_child != 0)
            break;
        work->effect_child = func_080D4774(work->effect_child);
        if (work->effect_child != 0)
            break;
        work->resource = func_080D4D2C(work->resource, 0);
        if (work->resource != 0)
            break;
        mask = func_080035A8(2);
        *shadow &= ~mask;
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (work->coordinate_child != 0)
            break;
        work->motion_child = func_080D9B64(work->motion_child);
        if (work->motion_child != 0)
            break;
        *phase = 2;
        break;
    }
    return 0;
}
