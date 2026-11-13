#include "ffta.h"

// Complete [0x08074908, 0x08074A54): 332 bytes, including the literal pool.
// Target: f0b557464e464546e0b484b00390454800684549401802210170444da6225200a8180068ac235b00e91809780133ea1812780091052301930c240294c023a1f7fdfca4214900681800680e2100910121019102940e210d22c023a1f7fdfd344d042001210122012316f0b8ff041c31483e211c22a3f7d2fd021c281c211c0123c0f776fe002290462b4b9a4691464046440003982a30001905882849680140180688274f4f44281c56f0f4ff021c1207d02109065218120c1a2041464143214bc9180904090c02342406240e00940220019002900420012314f032fc1548291c56f0caff1348391c4022ccf03bff1648b600361837685046391c0d22002315f051f8d020800082448144012188444246042abcdd04b038bc9846a146aa46f0bc01bc004718280003f50b0000e00900033ec00000b03c000260b5000680d15108e0b40006a701000080665208

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
    u8 unknown_000[0xBF5];
    u8 ready;
} State;

typedef struct {
    u16 name;
    u8 unknown_02[0x1E];
} LookupRecord;

typedef struct {
    u8 unknown_00[0x2A];
    u16 ids[5];
} EntryList;

extern u8 data_02003CB0[];
extern State *data_03002818;
extern TileRenderer data_030009E0[];
extern u8 data_0600B4E0[];
extern const LookupRecord g_table_0851D180[];
extern const u8 *const g_table_08526680[];

extern void func_08016344(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *destination, u8 width, u8 height,
    u16 flags, u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern u8 func_080CB99C(u16 id);
extern void func_08089248(u32 index, u16 tile, u16 attributes,
    u8 x, u8 y, u8 width, u8 height);
extern void func_080CB980(void *buffer, u32 id);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08089AAC(void *destination, const u8 *text, u16 count, u32 mode);

void func_08074908(EntryList *list)
{
    u8 *buffer = data_02003CB0;
    u8 *tiles = data_0600B4E0;
    s32 i;
    s32 id;
    u16 name;
    const u8 *ptr;
    u8 *text;

    data_03002818->ready = 2;
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].stride, data_030009E0[4].height,
        0xC0, data_030009E0[4].stride, 5, 12);
    func_08016560(data_030009E0[4].first_plane, 14, 13, 0xC0, 14, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
        func_08018524(buffer, 0x3E, 0x1C), 1);
    for (i = 0, text = (u8 *)0x0600B560; i < 5; text += 0x340, i++) {
        id = list->ids[i];
        name = g_table_0851D180[id].name;
        ptr = tiles + i * 0x340;
        func_08089248(4, 0x1A7 + i * 26, (func_080CB99C(id) + 13) << 12,
            1, i * 2 + 2, 2, 2);
        func_080CB980(buffer, id);
        func_0814186C(buffer, (void *)ptr, 0x40);
        ptr = g_table_08526680[name];
        func_08089AAC(text, ptr, 13, 0);
    }
}
