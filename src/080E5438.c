#include "ffta.h"

/* Target [0x080E5438, 0x080E54C6):
70b583b0061c0d1c141c2988012939d0012902dc002908d034e08020400081420ed00130814225d02ce06868e060a98a2171a21c211c0023f8f76af9a06021e02179012008400223002800d00423e06807490822134300930196002202920c220023f7f7a3fd20612888013009e00000906f39082069f6f7d5fa2061002801d102202880002003b070bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
} EffectDescriptor;

typedef struct {
    s16 x;
    s16 y;
    u8 selector;
    u8 unknown_05[3];
    void *underlying;
    void *object;
    void *child;
} EffectWork;

extern void *func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DBA5C(void *child);

u32 func_080E5438(void *task, void *descriptor_arg, void *payload_arg)
{
    EffectDescriptor *descriptor = descriptor_arg;
    EffectWork *work = payload_arg;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        work->object = descriptor->object;
        work->selector = descriptor->selector;
        work->underlying = func_080DD748(work->object, &work->x, &work->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        flags = (work->selector & 1) ? 4 : 2;
        work->child = func_080DCFE4(work->object, (const void *)0x08396F90,
                                  12, 0, flags | 8, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        work->child = func_080DBA5C(work->child);
        if (work->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
