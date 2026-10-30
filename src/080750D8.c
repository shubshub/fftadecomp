#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 field_06;
} Object080750D8;

typedef struct {
    u8 unknown_000[0x68C];
    u8 text_state[0];
} TextContext080750D8;

extern const u8 *data_085668B0[];
extern TextContext080750D8 *data_03002818;
extern u8 data_0600BA60[];

extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(int index, u16 *destination, u16 tile,
                         u16 count, u16 flags);
extern void func_08015110(void *context, void *destination, const u8 *text,
                         u32 mode, u32 spacing);

/* Target [0x080750D8, 0x080751AC), 212 bytes:
 * 10b581b01449cc310c68807905282fd8042001210022072316f0f8fb0f4a111c0180
 * 042001210122062316f0effb011c0b4ac0200002009004200a2316f054fb08480068
 * 08494018084901220092221c00239ff7f1ff2ee0b06856080cd00000d30100001828
 * 00038c06000060ba0006042001210022072316f0c8fb104a111c0180042001210122
 * 062316f0bffb011c0c4ac0200002009004200a2316f024fb09480068094940180949
 * 01220092221c01239ff7c1ff01b010bc01bc004700000cd00000d301000018280003
 * 8c06000060ba0006
 */
void func_080750D8(Object080750D8 *object)
{
    const u8 *text = data_085668B0[0x33];

    if (object->field_06 <= 5) {
        *func_0808B8E4(4, 1, 0, 7) = 0xD00C;
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 6),
                     0x1D3, 10, 0xC000);
        func_08015110(data_03002818->text_state, data_0600BA60,
                     text, 0, 1);
    } else {
        *func_0808B8E4(4, 1, 0, 7) = 0xD00C;
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 6),
                     0x1D3, 10, 0xC000);
        func_08015110(data_03002818->text_state, data_0600BA60,
                     text, 1, 1);
    }
}
