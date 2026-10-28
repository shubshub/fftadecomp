#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[2];
    u8 enabled;
    u8 unknown_06[0x46];
} Transfer0803DE40;

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 unknown_08[0x908];
    u8 selected;
} State0803DE40;

typedef struct {
    u8 unknown_00[0x14C];
    const void *resource;
} Resources0803DE40;

extern State0803DE40 *g_state_03002810;
extern Transfer0803DE40 data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_0201F48F;
extern u8 data_0201F490;
extern u16 data_03000000[];
extern u8 data_06009960[];
extern u8 data_0600A160[];
extern const u8 data_083917FA[];
extern const Resources0803DE40 data_085668B0;
extern const void *const g_table_08526680[];

extern void func_08141540(u32 value);
extern void func_08038D10(void *destination, const void *first,
                          const void *description, const void *second);
extern u16 func_080161BC(const void *resource);
extern void func_0803DACC(u32 mode);
extern void func_08015110(void *state, void *destination, const void *source,
                         u32 offset, u32 mode);
extern void func_0808A604(u32 channel, u32 command);

/* 0803DE40..0803E078: 568 bytes, including referenced literals. */
void func_0803DE40(u32 index)
{
    u8 *state = (u8 *)g_state_03002810 + index * 0xCC;
    u8 *phase = state + 0x987;

    switch (*phase) {
    case 0:
    {
        u8 *workspace = data_02003CB0;
        const void *resource;
        const void *description;
        const void **secondary;

        if ((data_030009E0[2].flags & 7) != 0)
            break;
        if ((data_030009E0[3].flags & 7) != 0)
            break;

        func_08141540(0x65);
        resource = g_table_08526680[
            (g_state_03002810->entries[0x6C + g_state_03002810->selected] & 0x7F)
            + 0x2CD];
        description = data_083917FA;
        secondary = (const void **)&data_085668B0.resource;
        func_08038D10(workspace, resource, description, *secondary);

        if (func_080161BC(workspace) > 24) {
            func_0803DACC(2);
            func_08015110((u8 *)g_state_03002810 + 0xC4C,
                         data_06009960, resource, 0, 1);
            func_08015110((u8 *)g_state_03002810 + 0xC4C,
                         data_0600A160, *secondary, 0, 1);
        } else {
            func_0803DACC(1);
            func_08038D10(workspace, resource, description, *secondary);
            func_08015110((u8 *)g_state_03002810 + 0xC4C,
                         data_06009960, workspace, 0, 1);
        }

        data_0201F490 = 4;
        data_030009E0[4].enabled = 1;
        func_0808A604(4, 11);
        data_0201F48F = 1;
        ((u8 *)g_state_03002810 + index * 0xCC)[0x987] = 2;
        break;
    }
    case 1:
        if (data_03000000[1] & 1) {
            data_0201F490 = 4;
            data_030009E0[4].enabled = 1;
            func_0808A604(4, 12);
            data_0201F48F = 1;
            ((u8 *)g_state_03002810 + index * 0xCC)[0x987] = 0xFD;
        }
        break;
    case 2:
        if (data_030009E0[data_0201F490].active == 0)
            *phase = data_0201F48F;
        break;
    case 0xFD:
        if (data_030009E0[data_0201F490].active == 0) {
            state[0x986] = 0xFF;
            ((u8 *)g_state_03002810 + index * 0xCC)[0x987] = 0xFF;
        }
        break;
    }
}
