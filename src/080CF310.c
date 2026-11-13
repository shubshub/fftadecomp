#include "ffta.h"

// Complete target: [0x080CF310, 0x080CF51C), 524 bytes.
// f0b54f464646c0b4041c0e1c1206150e22786078032108400002104346214143114809188846
// f079faf75af80006020e40463c300178fc200840002802d0880890420ed0002d11d040463d30
// 007800280cd02179884204d0002807d06479a04204d10020cce000004cae55085b4c707a2178
// 73f095fb0006000e6178051c4d430234708b217873f08ff9617848432d180234f08b217873f0
// 87f9617848432d180234301c01210122fbf722f8217873f07bf9617848432d180234301c0121
// 0122fbf752f8217873f06ff9617848432d180234301c02210122fbf70af8217873f063f96178
// 48432d180234301c02210122fbf73af8217873f057f9617848432d180234301cf9f702f80006
// 000e012801d160782d180234301cf8f7f8ff0006002801d160782d18f079f9f7daff00064446
// 3b3423781b0941463c310978032211400901000e1943884206d16800401980000a2173f029f9
// 051c40463a3003781e201840002816d01e481e221a401d49401812185b0920780f210840c000
// 11781843814207d3e900491b0801401a642173f00bf9051c002743224244914644208044341c
// 2a3403262088002807d00a21fbf771f90004000cb84200d9071c0234013e002ef0daed194a46
// 11784246107800020843a84208da012111e000002a7e520800000002b4210000401b02210928
// 06dd03211d2803dd0521312800dc0421081c18bc9846a146f0bc02bc0847

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_02[2];
    u8 field_04;
    u8 field_05;
} __attribute__((packed)) Record080CF310;

typedef struct {
    u8 unknown_00[7];
    u8 category;
    u8 unknown_08;
    u8 field_09;
    u8 unknown_0A[0x10];
    u16 field_1A;
    u8 unknown_1C[2];
    u16 field_1E;
    u8 unknown_20[0xA];
    u16 entries[4];
} Unit080CF310;

typedef struct {
    u8 unknown_00[0x3A];
    u8 unknown_3A_0 : 1;
    u8 slot : 4;
    u16 threshold : 7;
    u16 bonus_category : 6;
    u8 category : 6;
    u8 field_3D;
    u8 unknown_3E[5];
    u16 limit;
    u8 unknown_45;
} __attribute__((packed)) Metadata080CF310;

extern const Metadata080CF310 g_table_0855AE4C[];
extern const u8 data_08527E2A[];
typedef struct {
    u8 unknown_0000[0x21B4];
    u8 slots[16][2];
} State080CF310;

extern State080CF310 g_state_02000000;
extern u8 func_080C93F0(u8 category);
extern s32 func_080CA400(const void *object, u8 flags, u8 enabled);
extern s32 func_080CA478(const void *object, u8 flags, u8 enabled);
extern u8 func_080C841C(const void *object);
extern s32 func_080CA7A4(u16 entry, u8 selector);

u8 func_080CF310(const Record080CF310 *record, const Unit080CF310 *unit, u8 check)
{
    const Metadata080CF310 *metadata = &g_table_0855AE4C[record->id];
    const u8 *weight;
    u8 category = func_080C93F0(unit->category);
    s32 score;
    u16 best;
    s32 i;
    s32 margin;
    u8 result;

    if (metadata->category && metadata->category == category)
        return 0;
    if (check) {
        if (metadata->field_3D && metadata->field_3D == record->field_04)
            return 0;
        if (metadata->field_3D && metadata->field_3D == record->field_05)
            return 0;
    }

    weight = data_08527E2A;
    score = unit->field_09 / weight[0] * weight[1];
    weight += 2;
    score += unit->field_1A / weight[0] * weight[1];
    weight += 2;
    score += unit->field_1E / weight[0] * weight[1];
    weight += 2;
    score += func_080CA400(unit, 1, 1) / weight[0] * weight[1];
    weight += 2;
    score += func_080CA478(unit, 1, 1) / weight[0] * weight[1];
    weight += 2;
    score += func_080CA400(unit, 2, 1) / weight[0] * weight[1];
    weight += 2;
    score += func_080CA478(unit, 2, 1) / weight[0] * weight[1];
    weight += 2;
    if (func_080C841C(unit) == 1)
        score += weight[1];
    weight += 2;
    if (func_080C841C(unit) == 0)
        score += weight[1];

    if (func_080C93F0(unit->category) == metadata->bonus_category)
        score = score * 12 / 10;

    if (metadata->slot) {
        if (g_state_02000000.slots[metadata->slot][0] >= metadata->threshold)
            score = score * 105 / 100;
    }

    best = 0;
    for (i = 0; i < 4; i++) {
        if (unit->entries[i]) {
            u16 value = func_080CA7A4(unit->entries[i], 10);

            if (value > best)
                best = value;
        }
    }
    score += best;

    if (metadata->limit < score) {
        result = 1;
    } else {
        margin = metadata->limit - score;
        if (margin <= 9)
            result = 2;
        else if (margin <= 29)
            result = 3;
        else if (margin <= 49)
            result = 4;
        else
            result = 5;
    }
    return result;
}
