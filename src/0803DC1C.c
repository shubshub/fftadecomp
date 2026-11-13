#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 phase;
    u8 unknown_04[0xC8];
} MenuSlot;
typedef struct {
    u8 unknown_00[0x6C];
    u8 entries[1];
} MenuWindow;
typedef struct {
    void *owner;
    MenuWindow *window;
    u8 unknown_08[0x908];
    u8 selected;
    u8 unknown_911[0x73];
    MenuSlot slots[3];
    u8 unknown_BE8[0x64];
    u8 text_state[1];
} MenuContext;
typedef struct {
    u8 active;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[2];
    u8 enabled;
    u8 unknown_06[0x46];
} Transfer;
typedef struct {
    u8 unknown_000[0xD8];
    const u8 *resource;
} ResourceTable;
extern MenuContext *g_state_03002810;
extern Transfer data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_0201F48D;
extern u8 data_0201F48E;
extern u16 data_03000000[];
extern u8 data_06009960[];
extern u8 data_0600A160[];
extern const u8 *data_085668B0[];
extern const u8 *const g_table_08526680[];
extern void func_08038CF0(u8 *destination, const u8 *first,
                         const u8 *second);
extern u16 func_080161BC(const u8 *text);
extern void func_0803DACC(u32 mode);
extern void func_08015110(void *context, void *destination, const u8 *text,
                         u32 mode, u32 spacing);
extern void func_0808A604(u32 object, u32 command);

// Complete [0x0803DC1C, 0x0803DE40): 548 bytes.
void func_0803DC1C(u32 index)
{
    MenuContext *context = g_state_03002810;
    u8 *record = (u8 *)context + index * sizeof(MenuSlot);
    u8 *phase = record + 0x987;

    switch (*phase) {
    case 0: {
        u8 *workspace = data_02003CB0;
        const u8 *resource;
        const u8 **secondary;
        ResourceTable *resource_table;
        Transfer *transfer;
        u16 resource_id;
        if (data_030009E0[2].flags & 7)
            break;
        if (data_030009E0[3].flags & 7)
            break;
        resource_id = 0x2CD + g_state_03002810->window->entries[g_state_03002810->selected];
        resource = g_table_08526680[resource_id];
        resource_table = (ResourceTable *)data_085668B0;
        secondary = &resource_table->resource;
        func_08038CF0(workspace, resource, *secondary);
        if (func_080161BC(workspace) > 24) {
            func_0803DACC(2);
            func_08015110(g_state_03002810->text_state,
                         data_06009960, resource, 0, 1);
            func_08015110(g_state_03002810->text_state,
                         data_0600A160, *secondary, 0, 1);
        } else {
            func_0803DACC(1);
            func_08038CF0(workspace, resource, *secondary);
            func_08015110(g_state_03002810->text_state,
                         data_06009960, workspace, 0, 1);
        }
        data_0201F48E = 4;
        transfer = data_030009E0;
        transfer += 4;
        transfer->enabled = 1;
        func_0808A604(4, 11);
        data_0201F48D = 1;
        g_state_03002810->slots[index].phase = 2;
        break;
    }
    case 1:
        if (data_03000000[1] & 1) {
            Transfer *transfer;
            data_0201F48E = 4;
            transfer = data_030009E0;
            transfer += 4;
            transfer->enabled = 1;
            func_0808A604(4, 12);
            data_0201F48D = 1;
            g_state_03002810->slots[index].phase = 0xFD;
        }
        break;
    case 2:
        if (data_030009E0[data_0201F48E].active == 0)
            *phase = data_0201F48D;
        break;
    case 0xFD:
        if (data_030009E0[data_0201F48E].active == 0) {
            g_state_03002810->slots[index].result = 0xFF;
            g_state_03002810->slots[index].phase = -1;
        }
        break;
    case 0xFF:
        break;
    }
}
