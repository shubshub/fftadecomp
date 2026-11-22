#include "ffta.h"

/* Complete target: [0x080CE4DC, 0x080CE8A6), 970 bytes, 349 instructions,
 * including two alignment bytes at 0x080CE4FE, the literal words for
 * g_table_0855AE4C and the jump table at 0x080CE500, and the 65-entry jump
 * table at 0x080CE508.
 * 00b50004000c09060a0e4621414305480b18402a00d9d5e19000034940180068874600004cae
 * 550808e50c080ce60c0812e60c0816e60c081ae60c0824e60c082ce60c0840e60c0852e60c08
 * 62e60c0868e60c086ce60c0872e60c0876e60c087ce60c0880e60c0888e60c0890e60c08a0e6
 * 0c08a8e60c08b8e60c08b8e60c08bee60c08c4e60c08cae60c08d0e60c08d6e60c08dce60c08
 * e2e60c08e8e60c08eee60c08f6e60c08fce60c0804e70c080ae70c0812e70c081ae70c0822e7
 * 0c082ae70c0832e70c083ae70c0842e70c084ae70c0852e70c0858e70c086ae70c0870e70c08
 * 82e70c088ee70c089ee70c08b4e70c08c0e70c08d6e70c08ece70c08f6e70c0806e80c0812e8
 * 0c0824e80c0836e80c083ee80c0846e80c0856e80c085ee80c0870e80c0882e80c088ae80c08
 * 197858781ee1987835e0987843e099788909d8780f2245e0d8784006400f3ae1181c41300178
 * 01300078000208430121084030e1181c413001780130007800020843400823e1d978c9091879
 * 03221040400008431fe159799879f3e0d8791ae1197a587aeee0987a15e1d97a187be9e0587b
 * 10e1987b4007400f0ce1997bc908d87b02e0d97bc908187c072210404001084300e1187c8006
 * 400ffce0197c8909587c3f22104080000843f4e0181c1230f1e0181c1630eee0181c1a30ebe0
 * 181c1e30e8e0181c2230e5e0181c2230b6e0181c2430b3e0181c2630b0e0181c2830ade0181c
 * 35300078d5e0181c333086e0181c34300078cee0181c2a30cbe0181c2a300078c7e0181c2b30
 * 0078c3e0181c2c300078bfe0181c2d300078bbe0181c2e300078b7e0181c2f300078b3e0181c
 * 30300078afe0181c31300078abe0181c32300078a7e0181c363050e0181c4130017801300078
 * 00020843000997e0181c373044e0181c41300178013000780002084340098be0181c38300078
 * 0007000f89e0181c38300278120901300078072122e0181c39300278d2080130007801210840
 * 4001104376e0181c3a300078c006000f70e0181c3a3002785209013000780f210840c0001043
 * 65e0181c3b30027812090130007803210840000110435ae0181c3c300078800855e0181c3d30
 * 0078fcf752fe0004000c4de0181c3e300178c820484347e0181c413001780130007800020843
 * 80083ae0181c413001780130007800020843c00831e0181c3f30007831e0181c403000782de0
 * 181c43300178013000780002084325e0181c4530007821e0181c413001780130007800020843
 * 800914e0181c413001780130007800020843c0090be0181c4230007807e0181c413001780130
 * 007800020843400a0121084000e0002002bc0847
 */

/* One 0x46-byte row of g_table_0855AE4C.  Byte 2 bits 3-5 are `kind` as
 * src/080CF060.c declares them, `field_0E` and `field_10` are the halfword
 * bit-fields src/080D29D4.c declares at 0x0E-0x11 (the eleven bits between
 * them are split 8 and 3 here, as selectors 16 and 17 read them at
 * 0x080CE690 and 0x080CE6A0), the halfword at 0x41 is `flags` as
 * src/080D2D54.c declares it, and byte 0x45 is `category` as src/08019758.c
 * declares it.  Every other member is named by its offset.  Selectors 3, 7,
 * 15, 16, 18, 47, 48, 50 and 51 read fields that cross a byte boundary,
 * which the ROM extracts with two byte loads. */
typedef struct {
    u16 value_00;
    u8 value_02_low : 3;
    u8 kind : 3;
    u8 value_02_03 : 6;
    u8 value_03_middle : 3;
    u8 value_03_04 : 3;
    u8 unknown_04_high : 6;
    u16 value_05;
    u8 value_07;
    u16 value_08;
    u8 value_0A;
    u16 value_0B;
    u8 value_0D;
    u16 value_0E_low : 3;
    u16 field_0E : 8;
    u16 value_0F_10 : 8;
    u16 value_10_middle : 3;
    u16 field_10 : 8;
    u16 unknown_11_high : 2;
    u8 values_12[4];
    u8 values_16[4];
    u8 values_1A[4];
    u8 values_1E[4];
    u16 values_22[4];
    u8 values_2A[9];
    u8 value_33;
    u8 value_34;
    u8 value_35;
    u8 value_36;
    u8 value_37;
    u8 value_38_low : 4;
    u8 value_38_39 : 7;
    u8 value_39_3A : 6;
    u8 value_3A_middle : 4;
    u8 value_3A_3B : 7;
    u8 value_3B_3C : 6;
    u8 value_3C_high : 6;
    u8 value_3D;
    u8 value_3E;
    u8 value_3F;
    u8 value_40;
    u16 flags;
    u16 value_43;
    u8 category;
} __attribute__((packed)) ItemMetadata;

extern const ItemMetadata g_table_0855AE4C[];
extern u32 func_080CB4A4(u8 code);

u32 func_080CE4DC(u16 index, u8 selector)
{
    const ItemMetadata *record = &g_table_0855AE4C[index];

    switch (selector) {
    case 0:
        return record->value_00;
    case 1:
        return record->value_02_low;
    case 2:
        return record->kind;
    case 3:
        return record->value_02_03;
    case 4:
        return record->value_03_middle;
    case 5:
        /* Each flag selector tests one bit of `flags`, as src/080D2E78.c
         * does.  Bit 0 keeps its own `movs r1, #1; ands r0, r1` at
         * 0x080CE63A; the other bits share the copy at 0x080CE89A. */
        return (record->flags & 0x0001) != 0;
    case 6:
        return (record->flags & 0x0002) != 0;
    case 7:
        return record->value_03_04;
    case 8:
        return record->value_05;
    case 9:
        return record->value_07;
    case 10:
        return record->value_08;
    case 11:
        return record->value_0A;
    case 12:
        return record->value_0B;
    case 13:
        return record->value_0D;
    case 14:
        return record->value_0E_low;
    case 15:
        return record->field_0E;
    case 16:
        return record->value_0F_10;
    case 17:
        return record->value_10_middle;
    case 18:
        return record->field_10;
    case 19:
    case 20:
        return (u32)record->values_12;
    case 21:
        return (u32)record->values_16;
    case 22:
        return (u32)record->values_1A;
    case 23:
        return (u32)record->values_1E;
    case 24:
        return (u32)record->values_22;
    case 25:
        return record->values_22[0];
    case 26:
        return record->values_22[1];
    case 27:
        return record->values_22[2];
    case 28:
        return record->values_22[3];
    case 29:
        return record->value_35;
    case 30:
        return record->value_33 * 200;
    case 31:
        return record->value_34;
    case 32:
        return (u32)record->values_2A;
    case 33:
        return record->values_2A[0];
    case 34:
        return record->values_2A[1];
    case 35:
        return record->values_2A[2];
    case 36:
        return record->values_2A[3];
    case 37:
        return record->values_2A[4];
    case 38:
        return record->values_2A[5];
    case 39:
        return record->values_2A[6];
    case 40:
        return record->values_2A[7];
    case 41:
        return record->values_2A[8];
    case 42:
        return (u16)func_080CB4A4(record->value_36);
    case 43:
        return (record->flags & 0x0010) != 0;
    case 44:
        return (u16)func_080CB4A4(record->value_37);
    case 45:
        return (record->flags & 0x0020) != 0;
    case 46:
        return record->value_38_low;
    case 47:
        return record->value_38_39;
    case 48:
        return record->value_39_3A;
    case 49:
        return record->value_3A_middle;
    case 50:
        return record->value_3A_3B;
    case 51:
        return record->value_3B_3C;
    case 52:
        return record->value_3C_high;
    case 53:
        return (u16)func_080CB4A4(record->value_3D);
    case 54:
        return record->value_3E * 200;
    case 55:
        return (record->flags & 0x0004) != 0;
    case 56:
        return (record->flags & 0x0008) != 0;
    case 57:
        return record->value_3F;
    case 58:
        return record->value_40;
    case 59:
        return record->value_43;
    case 60:
        return record->category;
    case 61:
        return (record->flags & 0x0040) != 0;
    case 62:
        return (record->flags & 0x0080) != 0;
    case 63:
        return (record->flags & 0x0100) != 0;
    case 64:
        return (record->flags & 0x0200) != 0;
    }
    return 0;
}
