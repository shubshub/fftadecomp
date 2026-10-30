#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 category;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xDE];
} SceneRecord081258CC;

typedef struct {
    SceneRecord081258CC records[24];
    u8 unknown_18C0[0x22E4];
    u32 flags;
} SceneState081258CC;

typedef void (*BufferInitializer081258CC)(void *destination, u32 size);

extern SceneState081258CC g_state_02000080;
extern BufferInitializer081258CC const g_callbacks_0836D4B8[];
extern u8 func_080C8364(const SceneRecord081258CC *record);
extern u8 func_080C8194(const void *record, u8 category);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_080CB4C0(void *record);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer081258CC callback);

/* Target: complete [0x081258CC, 0x08125938), 108 bytes.
 * 70b5174c174826181725207900281ed0201ca2f741fd0006002818d0201c0821a2f7
 * 52fc0006002803d034200121a3f73bfe201ca5f7defd0b480268201c842149001cf0
 * 9dfc3068082108433060013d842040002418002dd7da70bc01bc004780000002a43b
 * 0000b8d43608
 */
void func_081258CC(void)
{
    SceneRecord081258CC *record = g_state_02000080.records;
    u32 *flags = &g_state_02000080.flags;
    s32 remaining;

    for (remaining = 23; remaining >= 0; remaining--, record++) {
        if (record->category && func_080C8364(record)) {
            if (func_080C8194(record, 8))
                func_080C9574(0x34, 1);
            func_080CB4C0(record);
            func_0814224C(record, sizeof(*record), g_callbacks_0836D4B8[0]);
            *flags |= 8;
        }
    }
}
