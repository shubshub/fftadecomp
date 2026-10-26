#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[0xC8];
} MenuSlot;

typedef struct {
    u8 unknown_00[0x6C];
    u8 entries[1];
} MenuWindow;

typedef struct {
    void *owner;
    MenuWindow *window;
    u8 unknown_08[0x910 - 8];
    u8 selection;
    u8 unknown_911[0x984 - 0x911];
    MenuSlot slots[3];
    u8 unknown_BE8[0xC4C - 0xBE8];
    u8 text_state[1];
} MenuContext;

typedef struct {
    u8 busy;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[2];
    u8 status;
    u8 unknown_06[0x46];
} RenderObject;

typedef struct {
    u16 held;
    u16 pressed;
} Input;

extern MenuContext *g_state_03002810;
extern RenderObject data_030009E0[];
extern u8 data_02003CB0[];
extern const u8 *g_table_08526680[];
extern const u8 *data_085668B0[];
extern u8 data_06009960[];
extern u8 data_0600A160[];
extern u8 data_0201F48E;
extern u8 data_0201F48D;
extern Input data_03000000;

void func_08038CF0(u8 *destination, const u8 *first, const u8 *second);
u32 func_080161BC(const u8 *text);
void func_0803DACC(u32 lines);
void func_08015110(void *context, void *destination, const u8 *text,
                   u32 mode, u32 spacing);
void func_0808A604(u32 object, u32 command);

/* Complete target: [0x0803DC1C, 0x0803DE40), 548 bytes. */
void func_0803DC1C(s32 slot)
{
    switch (g_state_03002810->slots[slot].state) {
    case 0: {
        u8 *text = data_02003CB0;
        const u8 *name;
        const u8 **suffix;
        s32 name_id;

        if ((data_030009E0[2].flags & 7) ||
            (data_030009E0[3].flags & 7))
            break;

        name_id = 0x2CD +
            g_state_03002810->window->entries[g_state_03002810->selection];
        name = g_table_08526680[name_id];
        suffix = data_085668B0;
        suffix += 54;
        func_08038CF0(text, name, *suffix);
        if ((u16)func_080161BC(text) > 24) {
            func_0803DACC(2);
            func_08015110(g_state_03002810->text_state,
                           data_06009960, name, 0, 1);
            func_08015110(g_state_03002810->text_state,
                           data_0600A160, *suffix, 0, 1);
        } else {
            func_0803DACC(1);
            func_08038CF0(text, name, *suffix);
            func_08015110(g_state_03002810->text_state,
                           data_06009960, text, 0, 1);
        }
        data_0201F48E = 4;
        {
            RenderObject *object = data_030009E0;
            object += 4;
            object->status = 1;
        }
        func_0808A604(4, 11);
        data_0201F48D = 1;
        g_state_03002810->slots[slot].state = 2;
        break;
    }
    case 1:
        if (data_03000000.pressed & 1) {
            data_0201F48E = 4;
            {
                RenderObject *object = data_030009E0;
                object += 4;
                object->status = 1;
            }
            func_0808A604(4, 12);
            data_0201F48D = 1;
            g_state_03002810->slots[slot].state = 0xFD;
        }
        break;
    case 2:
        if (!data_030009E0[data_0201F48E].busy)
            g_state_03002810->slots[slot].state = data_0201F48D;
        break;
    case 0xFD:
        if (!data_030009E0[data_0201F48E].busy) {
            g_state_03002810->slots[slot].result = 0xFF;
            g_state_03002810->slots[slot].state = 0xFF;
        }
        break;
    case 0xFF:
        break;
    }
}
