#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 phase;
    u8 field_119A;
    u8 unknown_119B;
    u8 field_119C;
    u8 unknown_119D[0xD];
    u8 selected;
    u8 unknown_11AB[0x9D];
    void *entries[130];
} State0805E924;

extern State0805E924 *data_0200F448;
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_08060DEC(u8 index, u8 value);
extern void func_0805F44C(u8 id);
extern void func_0805F540(void *const *entries, s32 count);
extern void func_0805F4D8(u8 id, u8 mode);
extern u8 func_08060E0C(u8 index);
extern void func_080613D0(void);
extern s16 func_0805F4AC(void);

/* Target [0x0805E924, 0x0805EA0C), 232 complete bytes:
 * 10b5164c2068164940180078002831d1002000211e220a23cbf7c0fc05200221
 * 02f052fa052000f07ffd21680d4a88180d4bc9180978023100f0f0fd20680849
 * 4018012202702068084bc01809210170206807494018027037e0000048f40002
 * 9c11000048120000aa1100009a110000991100000520002100f09cfd052002f0
 * 33fa0006020e022a0dd02168104bc8180078801880000f4a8918091808680028
 * 01d002f003fd0c4a10680c4bc0180021017010680a4940180a2101701068094a
 * 80180121017000f05ffd10bc01bc0047aa1100004812000048f400029c110000
 * 9a11000099110000
 */
void func_0805E924(void)
{
    if (data_0200F448->field_119C == 0) {
        func_0802A2C0(0, 0, 30, 10);
        func_08060DEC(5, 2);
        func_0805F44C(5);
        func_0805F540(data_0200F448->entries,
                      data_0200F448->selected + 2);
        data_0200F448->field_119C = 1;
        data_0200F448->field_119A = 9;
        data_0200F448->phase = 1;
    } else {
        u8 index;

        func_0805F4D8(5, 0);
        index = func_08060E0C(5);
        if (index != 2) {
            void *entry = data_0200F448->entries[data_0200F448->selected + index];

            if (entry != 0)
                func_080613D0();
        }
        data_0200F448->field_119C = 0;
        data_0200F448->field_119A = 10;
        data_0200F448->phase = 1;
        func_0805F4AC();
    }
}
