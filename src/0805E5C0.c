#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 phase;
    u8 field_119A;
    u8 unknown_119B;
    u8 field_119C;
    u8 unknown_119D[6];
    u8 selection;
    u8 unknown_11A4[6];
    u8 selected;
    u8 unknown_11AB[0x9D];
    void *entries[130];
} MenuState;

extern MenuState *data_0200F448;
extern u8 func_08060DD4(void);
extern s16 func_08060DC4(void);
extern void func_0805DE30(u16 index);
extern void func_0805F540(void *const *entries, s32 count);
extern void func_0805F59C(u8 kind, u16 value);
extern u32 func_0805D1C0(u8 option);
extern void func_08061028(void *context, u8 entry);
extern void func_080133B0(u16 value);
extern u8 func_08060E0C(u8 index);
extern void func_080613D0(void);
extern void func_0805F4D8(u8 id, u8 mode);

/* Complete [0x0805E5C0, 0x0805E798): 472 bytes.
 * f0b502f007fc0006000e012800dadfe0022841dd042800dddae01a4c20681a49
 * 40180078002800d0b6e002f0ebfb0004000cfff71dfc251c2968144fc819144e
 * 89190978023100f09bff2868114a80180178052000f0c2ff2c680120fef7d0fd
 * 011c0906090e201c02f0fefc80204001b4f7befe052002f0e9fb0006020e022a
 * 72d065e048f400029c11000048120000aa110000a3110000114d2c68114be018
 * 0078002824d10120fef7aafd011c0906090e201c02f0d8fc80204001b4f798fe
 * 286808494018012101702868064a80180a2101702868054bc01803216ee00000
 * 48f400029c1100009a110000991100000520002100f010ff052002f0a7fb0006
 * 020e022a0dd029680c4bc8180078801880000b4a891809180868002801d002f0
 * 77fe084a1068084bc018002101701068064940180a21017010683ce0aa110000
 * 4812000048f400029c1100009a11000029688819007880188000c91909180868
 * 002801d002f054fe074a1068074bc018012101701068064940180a2101701068
 * 044a8018032119e048f400029c1100009a110000991100000520002100f0bcfe
 * 2068084bc018002101702068064940180a2101702068054a8018012101700120
 * 07e000009c1100009a110000991100000020f0bc02bc0847
 */
u8 func_0805E5C0(void)
{
    switch (func_08060DD4()) {
    case 1:
    case 2:
        if (data_0200F448->field_119C == 0) {
            func_08061028(data_0200F448, func_0805D1C0(1));
            func_080133B0(0x1000);
            data_0200F448->field_119C = 1;
            data_0200F448->field_119A = 10;
            data_0200F448->phase = 3;
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
        }
        return 1;
    case 3:
    case 4:
        if (data_0200F448->field_119C == 0) {
            u8 index;

            func_0805DE30(func_08060DC4());
            func_0805F540(data_0200F448->entries, data_0200F448->selected + 2);
            func_0805F59C(5, data_0200F448->selection);
            func_08061028(data_0200F448, func_0805D1C0(1));
            func_080133B0(0x1000);
            index = func_08060E0C(5);
            if (index != 2) {
                void *entry = data_0200F448->entries[data_0200F448->selected + index];

                if (entry != 0)
                    func_080613D0();
            }
            data_0200F448->field_119C = 1;
            data_0200F448->field_119A = 10;
            data_0200F448->phase = 3;
        } else {
            func_0805F4D8(5, 0);
            data_0200F448->field_119C = 0;
            data_0200F448->field_119A = 10;
            data_0200F448->phase = 1;
        }
        return 1;
    }
    return 0;
}
