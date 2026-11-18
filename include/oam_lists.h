#ifndef OAM_LISTS_H
#define OAM_LISTS_H

#include "ffta.h"

typedef struct AffineMatrix {
    s16 pa, pb, pc, pd;
} AffineMatrix;

typedef unsigned long long u64;
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 data_03000028;
extern u8 data_03002F58;
extern s32 data_03002C50[2];
extern s32 data_03002F60[2];
extern s32 data_03000020[2];
extern s32 data_03003168[2];
extern u64 data_03002C58[2][0x30];
extern u64 data_03002F68[2][0x20];
extern u64 data_03000030[2][0x80];
extern u64 data_03003170[2][0x10];
extern u8 data_03003270[2][32];
extern AffineMatrix data_030032B0[2][32];
extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);

#define HIDDEN_OAM_ENTRY 0x00F800A8

static inline void HideEntries(u64 *entry, s32 count)
{
    for (; count > 0; count--)
        *entry++ = HIDDEN_OAM_ENTRY;
}

#endif
