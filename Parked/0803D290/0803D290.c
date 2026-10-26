#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1d];
    u8 name;
} Data0803D290;

typedef struct {
    u32 unknown_00;
    Data0803D290 *data;
    u8 unknown_008[0xc44];
    u8 text_state[1];
} State0803D290;

extern State0803D290 *g_state_03002810;
extern const u16 *const g_table_08526680[];
extern const u16 *const data_085668B0[];
extern u8 data_060099E0[];
extern void func_08015110(void *, void *, const u16 *, u32, u32);
extern u32 func_0808B8E4(u32, u32, u32, u32);
extern void func_0808B858(u32, u32, u32, u32);
extern void func_0808B7C0(u32, u32, u32, u32, u32);

/* 0x0803D290..0x0803D320: 144 bytes, 54 instructions. */
void func_0803D290(void)
{
    const u16 *text;

    if (g_state_03002810->data->name) {
        s16 text_index = g_state_03002810->data->name;
        text_index += 0x2cd;
        text = g_table_08526680[text_index];
    } else {
        text = data_085668B0[0];
    }
    func_08015110(g_state_03002810->text_state, data_060099E0, text, 0, 1);
    func_0808B858(4, func_0808B8E4(4, 1, 1, 2), 0, 20);
    func_0808B7C0(4, func_0808B8E4(4, 1, 1, 2), 0xcb, 16, 0xc000);
}
