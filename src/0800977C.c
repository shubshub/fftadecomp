#include "ffta.h"

/* 0x0800977C..0x08009888, 268 bytes: 88 instructions and seventeen literal words.
 * f0b5314d314c32492a68201c38f160fd30488021c9012a6838f15afd0120f9f743f8
 * bf20800124182b49201c04223af127febff0c7fd00f007f928488722d20081180f88
 * 2649401801680025bd420ed20c1c002623483018211c0022bff034ff303484225200
 * b6180135bd42f2d3c2f077fc0121154e08251b4ab01801700238013d002dfada0024
 * 1848311818480860b52040000a21c1f075f816480421c1f071f815480421c1f06df8
 * 14480221c1f069f81348047013480470134ab11801200870f0bc01bc0047b8d43608
 * 00000002a83c0000b03c00024eba51087ccd54083c04000080000002c4210000641f
 * 0000881300006f01000075010000770100004c2800030c28000385210000
 */

typedef void (*ClearBuffer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x30];
} SourceRecord;

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

/* The count/records pair func_080CA744 walks as its InitializationHeader. */
typedef struct {
    u8 unknown_000[0x438];
    u16 count;                      /* +0x438 */
    u8 unknown_43A[2];
    SourceRecord *records;          /* +0x43C */
} InitializationData;

/* The game state at 0x02000000, 0x3CA8 bytes (the size of the first clear). */
typedef struct {
    u8 unknown_0000[0x1F64];
    u32 total;                      /* +0x1F64, func_0806EBF8 */
    u8 unknown_1F68[0x21D];
    u8 unknown_2185;
    u8 unknown_2186[0x2E];
    u8 slots[16][2];                /* +0x21B4, func_08046854 */
    u8 unknown_21D4[0xDEC];
    u8 options[4];                  /* +0x2FC0, func_08008954 */
    u8 unknown_2FC4[0xCE4];
} GameState;

extern ClearBuffer g_callbacks_0836D4B8[];
extern GameState g_state_02000000;
extern SceneRecord g_state_02000080[];
extern const InitializationData g_table_0854CD7C;
extern const u8 g_table_0851BA4E[];
extern u8 data_02003CB0[];
extern u8 data_0300284C;
extern u8 data_0300280C;

void *func_081443FC(void *destination, const void *source, u32 size);
void func_08002824(u32 value);
void func_080C9340(void);
void func_080099C4(void);
void func_080C9644(void *destination, void *source, u8 levelOverride);
void func_080CC0DC(void);
s32 func_080CA900(u16 identifier, u8 quantity);

void func_0800977C(void)
{
    SourceRecord *records;
    u32 count;
    s32 i;

    g_callbacks_0836D4B8[0](&g_state_02000000, sizeof(g_state_02000000));
    g_callbacks_0836D4B8[0](data_02003CB0, 0x4000);
    func_08002824(1);
    func_081443FC(g_state_02000000.options, g_table_0851BA4E, 4);
    func_080C9340();
    func_080099C4();
    count = g_table_0854CD7C.count;
    records = g_table_0854CD7C.records;
    for (i = 0; i < count; i++)
        func_080C9644(&g_state_02000080[i], &records[i], 0);
    func_080CC0DC();
    for (i = 0; i < 9; i++)
        g_state_02000000.slots[i][0] = 1;
    g_state_02000000.total = 5000;
    func_080CA900(0x16A, 10);
    func_080CA900(0x16F, 4);
    func_080CA900(0x175, 4);
    func_080CA900(0x177, 2);
    data_0300284C = 0;
    data_0300280C = 0;
    g_state_02000000.unknown_2185 = 1;
}
