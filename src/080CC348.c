/* 0x080CC348..0x080CC3C8: 128 bytes, 54 instructions, including a pool.
 * Target bytes:
 * f0b5041c0d1c161c2406240e2d043606360e13482d182d0c2906090e201c00f02ff8
 * 0006000e071c77430e4824010e49401824182678341c3b190c49e800401b40184279
 * 520980791f210840c0001043011c8b4210dd8c420ad300200de00000000096fe0000
 * 00027f2e0000248c5208801b0004000c00e0381cf0bc02bc0847
 *
 * Clamps a gain to the room left under a table limit: the gain is
 * func_080CC3C8(category, index) * count, the current value is byte 7 of
 * the 16-byte record at 0x02002E78 + category * 16 (one of the 20 records
 * func_080CCB94 and func_080CCBC4 walk and func_080CC510 clears), and the
 * limit is the eight-bit field at bit 45 of the seven-byte entry of
 * data_08528C24 that func_080CC3C8 reads.  Both bit-field runs use
 * unsigned short containers.  For data_08528C24 that is also what the
 * unsigned "limit > 99" test (bls) in func_08058908 needs: a u32 container
 * compiles that test signed.  func_080CC3C8, func_080CC510, func_080593E0
 * and func_08058C48 compile unchanged with u16 containers.
 */
#include "ffta.h"

typedef struct {
    u16 field_00 : 5;
    u16 field_05 : 5;
    u16 field_0A : 5;
    u16 field_0F : 5;
    u16 field_14 : 5;
    u16 field_19 : 5;
    u16 field_1E : 5;
    u16 field_23 : 5;
    u16 field_28 : 5;
    u16 limit : 8;
    u16 unknown_35 : 3;
} __attribute__((packed)) ProgressionInfo;

typedef struct {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u16 field_06 : 8;
    u16 identifier : 8;
    u16 field_08;
    u16 field_0A;
    u16 field_0C;
    u16 field_0E;
} __attribute__((packed)) ProgressionRecord;

typedef struct {
    u8 unknown_0000[0x2E78];
    ProgressionRecord records[20];
} ProgressionState;

extern ProgressionState g_state_02000000;
extern const ProgressionInfo data_08528C24[];
extern u8 func_080CC3C8(u8 selector, u8 index);

u16 func_080CC348(u8 category, u16 index, u8 count)
{
    s32 increase;

    index -= 0x16A;
    increase = func_080CC3C8(category, index) * count;
    if (increase + g_state_02000000.records[category].identifier
        > data_08528C24[index].limit) {
        if (g_state_02000000.records[category].identifier
            >= data_08528C24[index].limit)
            return 0;
        return data_08528C24[index].limit
            - g_state_02000000.records[category].identifier;
    }
    return increase;
}
