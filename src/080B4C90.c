#include "ffta.h"

typedef struct {
    u8 handler;
    u8 unknown_01[3];
} Record080B4C90;

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

extern const Record080B4C90 data_08553E70[];
extern SelectionGlobals g_state_0200F390;
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080C8298(const void *object);
extern u8 func_0812E470(const void *unit);
extern void func_0812F2A4(u16 first, u16 second, u8 kind);
extern u8 func_080C8240(void *data);
extern void func_0812F34C(u32 value);
extern void func_0812F328(u8 index);
extern u8 func_08130FBC(void);

/* Complete target: [0x080B4C90, 0x080B4D6E), 222 bytes, 98 instructions,
 * including the two literal pools. */
u8 func_080B4C90(void *context, void *object, u16 identifier, u16 value)
{
    if (identifier != 0) {
        u8 required = 1;
        const u8 *entry = (const u8 *)func_080CCD50(identifier, 9);
        s32 i;

        for (i = 0; i < 3; i++) {
            if (data_08553E70[entry[i]].handler == 0x1C) {
                required = 0;
            }
        }
        if (required && func_080C8298(object)) {
            return 0;
        }
    } else if (func_080C8298(object)) {
        return 0;
    }
    if (identifier == 0) {
        if (!func_0812E470(object)) {
            return 0;
        }
    } else {
        u32 found;
        s8 i;

        func_0812F2A4(identifier, value, 0);
        g_state_0200F390.selection.flags = func_080C8240(object) ? 0x80 : 0;
        found = 0;
        for (i = 0; i < 3; i++) {
            SelectionContext *state = &g_state_0200F390.selection;

            state->context = context;
            state->object = object;
            func_0812F34C(0);
            func_0812F328((u8)i);
            if (func_08130FBC()) {
                found = 1;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}
