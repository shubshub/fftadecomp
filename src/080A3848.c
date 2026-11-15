#include "ffta.h"

/* Target: complete [0x080A3848, 0x080A39F8), 432 bytes.
 * f0b557464e464546e0b482b0061c00911206120e0192081cf5f770feb0218900
 * 73181a782c215143321c203251180860187801301870002080461b7898455eda
 * 92462c2140464843311c20310918086801224244914600284ad0308a718a019a
 * 8bf0fcfc3068006824f0c6fc0006002808d00098f6f740ff0149087007e00000
 * 14f400020098f6f755ff274a1070002700240120404481462c21404648435246
 * 1518286800682af0fdf9000600280fd130682968026809681c48026041602006
 * 000e8bf00dfd8df055fb0006002805d10120a04007430134022ce2dd072f07d1
 * 2c2140464843311c2031091800200860c846b0229200b01800788045a1db0020
 * 814601218846202292199246371c4c3755465446206800280ad02c372c352c34
 * 012080441ae0000014f40002f0f300020e204146401a2c21021c4a431a480368
 * 281c391c9ef060fc18490a689721890070182c219ef056fc0122914440460d28
 * 02dc49460d29d5ddb0229200b118002008705246106800280dd02c2308780130
 * 08700006000e0d2805d808785843101800680028f2d102b038bc9846a146aa46
 * f0bc01bc00470000bcd43608b8d43608
 */

typedef struct {
    void *data;
} Object;

typedef struct {
    Object *object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0e[0x1e];
} SelectionEntry;

typedef struct {
    Object *object;
    u8 unknown_04[0x0c];
    u16 x;
    u16 y;
    u8 unknown_14[0x0c];
    SelectionEntry entries[15];
    u8 unknown_2b4[0x0c];
    u8 count;
} SelectionState;

typedef struct {
    u8 unknown_00[0x84];
    u8 selected;
} SelectionGlobals;

typedef void (*BufferCopier)(void *, const void *, u32);
typedef void (*BufferInitializer)(void *, u32);

extern SelectionGlobals g_state_0200F390;
extern void *data_0200F3F0[2];
extern BufferCopier const data_0836D4BC[];
extern BufferInitializer const g_callbacks_0836D4B8[];

extern Object *func_08099544(void *context);
extern void func_0812F2A4(u16 x, u16 y, u8 mode);
extern u8 func_080C8240(void *object);
extern u8 func_0809A740(void *context);
extern u8 func_0809A77C(void *context);
extern u8 func_080CDCEC(const void *object);
extern void func_0812F328(u8 index);
extern u8 func_08130FBC(void);

static inline void set_pair(void *first, void *second)
{
    data_0200F3F0[0] = first;
    data_0200F3F0[1] = second;
}

void func_080A3848(SelectionState *state, void *context, u8 mode)
{
    s32 i;
    s32 j;
    s32 retries;
    u32 mask;

    state->entries[state->count].object = func_08099544(context);
    state->count++;

    for (i = 0; i < state->count; i++) {
        if (state->entries[i].object == 0)
            continue;

        func_0812F2A4(state->x, state->y, mode);
        if (func_080C8240(state->object->data))
            g_state_0200F390.selected = func_0809A740(context);
        else
            g_state_0200F390.selected = func_0809A77C(context);

        mask = 0;
        for (j = 0; j < 3; j++) {
            if (!func_080CDCEC(state->entries[i].object->data)) {
                set_pair(state->object->data, state->entries[i].object->data);
                func_0812F328(j);
                if (func_08130FBC())
                    break;
            }
            mask |= 1 << j;
        }
        if (mask == 7)
            state->entries[i].object = 0;
    }

    retries = 0;
    i = 1;
    while (i < 14 && retries < 14) {
        if (state->entries[i - 1].object != 0) {
            i++;
        } else {
            data_0836D4BC[0](&state->entries[i - 1], &state->entries[i],
                             (14 - i) * sizeof(SelectionEntry));
            g_callbacks_0836D4B8[0](&state->entries[13],
                                    sizeof(SelectionEntry));
            retries++;
        }
    }

    for (state->count = 0; state->count < 14; state->count++) {
        if (state->entries[state->count].object == 0)
            break;
    }
}
