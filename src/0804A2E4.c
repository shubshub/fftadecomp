#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
    u16 name;
} Selection;

typedef struct {
    u8 unknown_00[4];
    Selection *selection;
    u8 unknown_008[0xC44];
    u8 text[1];
} MenuState;

typedef struct {
    const u8 *entries[26];
    const u8 *label;
} TextResources;

extern u8 data_02003CB0[];
extern const u8 data_08391800[];
extern const u8 data_08391803[];
extern const u8 data_083917FA[];
extern const u8 *g_table_0855A64C[];
extern TextResources data_085668B0;
extern MenuState *g_state_03002810;
extern u8 data_06009960[];
extern void func_08038D80(u8 *destination, const u8 *format, ...);
extern u32 func_080161BC(const void *text);
extern void *func_0808B92C(u32 width, void *tiles, u16 x, u32 y);
extern void func_08015110(void *context, void *tiles, const void *text, u32 mode, u32 spacing);

/* Complete target: [0x0804A2E4, 0x0804A3CC), 232 bytes. */
void func_0804A2E4(void)
{
    u8 *buffer = data_02003CB0;

    func_08038D80(buffer, data_08391800,
                  g_table_0855A64C[g_state_03002810->selection->name],
                  data_08391803, data_083917FA, data_085668B0.label);
    if ((u16)func_080161BC(buffer) <= 25) {
        func_08015110(g_state_03002810->text,
                      func_0808B92C(4, data_06009960, 0, 0), buffer, 0, 1);
    } else {
        func_08015110(g_state_03002810->text,
                      func_0808B92C(4, data_06009960, 0, 0),
                      g_table_0855A64C[g_state_03002810->selection->name], 0, 1);
        func_08015110(g_state_03002810->text,
                      func_0808B92C(4, data_06009960, 0, 2),
                      data_085668B0.label, 0, 1);
    }
}
