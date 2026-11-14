#include "ffta.h"

// Complete [0x08074A54, 0x08074CE8): 660 bytes, including the literal pools.
// Target: f0b557464e464546e0b485b0071c654e654881460068654940180022924603210170634da6235b00e8180068ac225200a91809780d33ea1812780091052301930c240294c023a1f753fca4214900681800680e2100910121019102940e210d22c023a1f753fd534d042001210122012316f00eff041c301c3e210422a3f728fd021c281c211c0123c0f7ccfd381c222153f0def9061c03a970788000464d4019007808704a4611687078800040198278c07800021043414bc9180880d0200002804602240094019402940420cb214246012314f08ffb03aab07880004019017840780002084350704a461168b078800040198278c07800021043314bc91808800420009001940294cb214246012314f071fb03a9381c3a3000788870e0252d0206200090019402940420cf212a1c012314f060fb03a9381c3b300078c87008200090019402940420d3214246012314f051fb03a9381c3c30007808710a200090019402940420d7212a1c012314f042fb49460868134a811853460b80023281180b80114bc0185146018000240f4d104a9046104b9a464e46002c1dd103a800781ee00000b03c000218280003f50b0000e00900033ec00000447252083412000036120000381200003c120000f067550884ba510860b50006012c05d103a840788000401902683fe0022c15d1b879800040440168381c3a300078c0004018028831684088034bc91808809200521912682ae0000038120000032c13d1b879800040440068391c3b310978c9000918088880004019026830684988014b12e000003a120000b879800040440268381c3c300178c90089180888800040190268306849880b4bc01801805046111c0d22002314f0f2fed020800082440134042c8bdd05b038bc9846a146aa46f0bc01bc00473c120000

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 height;
    u8 unknown_2A[0x4C - 0x2A];
} TileRenderer;

typedef struct {
    u8 unknown_0000[0xBF5];
    u8 ready;
    u8 unknown_0BF6[0x1234 - 0xBF6];
    u16 values[5];
} State;

typedef struct __attribute__((packed)) {
    u16 name;
    u16 value;
} EncodedRecord;

typedef struct {
    u16 name;
    u16 value;
    u8 unknown_04[4];
} TableRecord;

typedef struct {
    u8 unknown_00[6];
    u8 kind;
    u8 unknown_07[0x3A - 0x07];
    u8 entries[3];
} Unit;

extern u8 data_02003CB0[];
extern State *data_03002818;
extern TileRenderer data_030009E0[];
extern const EncodedRecord data_08527244[];
extern const TableRecord *const g_table_0851BA84[];
extern const u8 *const g_table_085567F0[];

extern void func_08016344(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern const u8 *func_080C7EA4(const void *object, u32 selector);
extern void func_08089248(u32 index, u16 tile, u16 attributes,
    u8 x, u8 y, u8 width, u8 height);
extern void func_08089AAC(void *destination, const u8 *text, u16 count, u32 mode);

void func_08074A54(Unit *unit)
{
    u8 *buffer = data_02003CB0;
    const u8 *info;
    u8 ids[5];
    s32 i;
    const u8 *name;

    data_03002818->ready = 3;
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].stride, data_030009E0[4].height,
        0xC0, data_030009E0[4].stride, 5, 12);
    func_08016560(data_030009E0[4].first_plane, 14, 13, 0xC0, 14, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
        func_08018524(buffer, 0x3E, 4), 1);

    info = func_080C7EA4(unit, 0x22);
    ids[0] = (data_08527244 + info[1])->name;
    data_03002818->values[0] = (data_08527244 + info[1])->value;
    func_08089248(4, 0xCB, 0xD000, 1, 2, 2, 2);
    ids[1] = (data_08527244 + info[2])->name;
    data_03002818->values[1] = (data_08527244 + info[2])->value;
    func_08089248(4, 0xCB, 0xD000, 1, 4, 2, 2);
    ids[2] = unit->entries[0];
    func_08089248(4, 0xCF, 0xE000, 1, 6, 2, 2);
    ids[3] = unit->entries[1];
    func_08089248(4, 0xD3, 0xD000, 1, 8, 2, 2);
    ids[4] = unit->entries[2];
    func_08089248(4, 0xD7, 0xE000, 1, 10, 2, 2);

    data_03002818->values[2] = 0;
    data_03002818->values[3] = 0;
    data_03002818->values[4] = 0;

    for (i = 0; i <= 4; i++) {
        if (i == 0) {
            name = g_table_085567F0[ids[0]];
        } else if (i == 1) {
            name = g_table_085567F0[ids[1]];
        } else if (i == 2) {
            const TableRecord *records = g_table_0851BA84[unit->kind];
            u16 id = records[unit->entries[0]].name;

            data_03002818->values[2] = records[unit->entries[0]].value;
            name = g_table_085567F0[id];
        } else if (i == 3) {
            const TableRecord *records = g_table_0851BA84[unit->kind];

            name = g_table_085567F0[records[unit->entries[1]].name];
            data_03002818->values[3] = records[unit->entries[1]].value;
        } else {
            const TableRecord *records = g_table_0851BA84[unit->kind];

            name = g_table_085567F0[records[unit->entries[2]].name];
            data_03002818->values[4] = records[unit->entries[2]].value;
        }
        func_08089AAC((u8 *)0x0600B560 + i * 0x340, name, 13, 0);
    }
}
