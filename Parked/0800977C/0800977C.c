/* 0x0800977C..0x08009888: 268 target bytes, including seventeen literal words. */
#include "ffta.h"

typedef void (*ClearBuffer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x30];
} SourceRecord;

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    u8 unknown_00[0x438];
    u16 count;
    u8 unknown_43A[2];
    SourceRecord *records;
} InitializationData;

typedef struct {
    u8 unknown_00[0x1f64];
    u32 amount;
    u8 unknown_1F68[0x21d];
    u8 initialized;
    u8 unknown_2186[0x2e];
    u8 slots[9][2];
    u8 unknown_21C6[0xdfa];
    u32 tail;
    u8 unknown_2FC4[0xce4];
} MainState;

extern ClearBuffer const g_callbacks_0836D4B8[];
extern MainState g_state_02000000;
extern SceneRecord g_state_02000080[];
extern const InitializationData g_table_0854CD7C;
extern const u8 g_table_0851BA4E[];

void *memcpy(void *destination, const void *source, unsigned long size);
void func_08002824(u32 value);
void func_080C9340(void);
void func_080099C4(void);
void func_080C9644(void *destination, void *source, u8 levelOverride);
void func_080CC0DC(void);
s32 func_080CA900(u16 identifier, u8 quantity);

void func_0800977C(void)
{
    SourceRecord *source;
    u16 count;
    u32 index;
    s32 slot;

    g_callbacks_0836D4B8[0](&g_state_02000000, sizeof(g_state_02000000));
    g_callbacks_0836D4B8[0]((void *)0x02003cb0, 0x4000);
    func_08002824(1);
    memcpy(&g_state_02000000.tail, g_table_0851BA4E, 4);
    func_080C9340();
    func_080099C4();
    count = g_table_0854CD7C.count;
    source = g_table_0854CD7C.records;
    for (index = 0; index < count; index++) {
        func_080C9644(&g_state_02000080[index], source, 0);
        source++;
    }
    func_080CC0DC();
    for (slot = 8; slot >= 0; slot--)
        g_state_02000000.slots[slot][0] = 1;
    g_state_02000000.amount = 5000;
    func_080CA900(0x16a, 10);
    func_080CA900(0x16f, 4);
    func_080CA900(0x175, 4);
    func_080CA900(0x177, 2);
    *(u8 *)0x0300284c = 0;
    *(u8 *)0x0300280c = 0;
    g_state_02000000.initialized = 1;
}
