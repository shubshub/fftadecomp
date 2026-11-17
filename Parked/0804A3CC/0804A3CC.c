#include "ffta.h"

// Complete target: [0x0804A3CC, 0x0804A4CC), 256 bytes, 96 instructions.

typedef struct {
    u8 unknown_000[0xC4C];
    u8 text[1];
} MenuState;

extern u8 data_02003CB0[];
extern u8 data_06009960[];
extern const u8 data_083917FA[];
extern const u8 *const g_table_08526680[];
extern const u8 *const data_085668B0[];
extern MenuState *g_state_03002810;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08038D10(u8 *destination, const u8 *first,
                          const u8 *second, const u8 *third);
extern void func_08038CF0(u8 *destination, const u8 *first, const u8 *second);
extern void func_080142DC(u8 *text, u32 value, u32 digits);
extern void *func_0808B92C(u32 width, void *tiles, u16 x, u32 y);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);

void func_0804A3CC(u8 index, u8 count)
{
    u8 *first = data_02003CB0;
    u8 *second = first + 0x100;
    u8 number[16];
    u16 zero = 0;

    func_0814186C(&zero, data_06009960, 0x01000D00);
    func_08038D10(first, g_table_08526680[index + 0x2CD],
                  data_083917FA, data_085668B0[27]);
    func_08015110(g_state_03002810->text,
                  func_0808B92C(4, data_06009960, 0, 0), first, 0, 1);
    if (count != 0) {
        func_080142DC(number, count, 2);
        func_08038CF0(second, number, data_085668B0[24]);
        func_08015110(g_state_03002810->text,
                      func_0808B92C(4, data_06009960, 0, 2), second, 0, 1);
    } else {
        func_08015110(g_state_03002810->text,
                      func_0808B92C(4, data_06009960, 0, 2),
                      data_085668B0[69], 0, 1);
    }
}
