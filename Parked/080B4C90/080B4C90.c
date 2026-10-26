#include "ffta.h"

/* 0x080B4C90..0x080B4D6E: 222 bytes, 98 instructions, including pools. */
typedef struct {
    u8 category;
    u8 unknown_01[3];
} CategoryEntry;

typedef struct {
    void *context;
    void *object;
    u8 unknown_08[0x1E];
    u16 flags;
} SelectionContext;

typedef struct {
    u8 unknown_00[0x60];
    SelectionContext selection;
} SelectionGlobals;

extern const CategoryEntry data_08553E70[];
extern SelectionGlobals g_state_0200F390;
extern u32 func_080CCD50(u16 identifier, u8 selector);
extern u8 func_080C8298(const void *object);
extern u8 func_0812E470(const void *object);
extern void func_0812F2A4(u16 identifier, u16 value, u8 mode);
extern u8 func_080C8240(const void *object);
extern void func_0812F34C(void *object);
extern void func_0812F328(u8 index);
extern u8 func_08130FBC(void);

static inline u8 category_requires_check(u16 identifier)
{
    u8 required = 1;
    const u8 *categories = (const u8 *)func_080CCD50(identifier, 9);
    s32 i;

    for (i = 0; i < 3; i++) {
        if (data_08553E70[categories[i]].category == 0x1C) {
            required = 0;
        }
    }
    return required;
}

u32 func_080B4C90(void *context, void *object, u16 identifier, u16 value)
{
    u32 success;
    if ((identifier == 0 || category_requires_check(identifier)) &&
        func_080C8298(object)) {
        return 0;
    }
    if (identifier == 0) {
        success = func_0812E470(object);
    } else {
        SelectionGlobals *globals;
        SelectionContext *state;
        u32 found;
        s8 i;

        func_0812F2A4(identifier, value, 0);
        globals = &g_state_0200F390;
        globals->selection.flags = func_080C8240(object) ? 0x80 : 0;
        found = 0;
        i = 0;
        state = &globals->selection;
        for (; i < 3; i++) {
            state->context = context;
            state->object = object;
            func_0812F34C(0);
            func_0812F328((u8)i);
            if (func_08130FBC()) {
                found = 1;
            }
        }
        success = found;
    }
    if (success) {
        return 1;
    }
    return 0;
}
