#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
} MenuInput;

typedef struct {
    u8 status;
    u8 flags;
} MenuResult;

typedef struct {
    u8 unknown_00[0x5C];
    MenuResult *result;
} MenuContext;

typedef struct {
    u8 unknown_00[0x10];
    u8 page;
    u8 page_count;
} MenuSelection;

extern MenuInput data_03000000;
extern MenuContext g_state_0200F390;
extern MenuSelection g_state_020020D0;

void func_08141570(u32 channel, u32 sound);
void func_08141540(u32 sound);
void func_08013364(void);
void func_08011B30(u32 operation, u32 page);

static inline u32 complete_menu(MenuResult *result)
{
    func_08013364();
    result->status = 0;
    result->flags |= 1;
    return 1;
}

/* Complete target: [0x08023DBC, 0x08023E88), 204 bytes. */
u32 func_08023DBC(void)
{
    u32 changed = 0;
    u16 keys = data_03000000.pressed;
    MenuResult *result = g_state_0200F390.result;

    if (keys & 2) {
        func_08141570(1, 0x69);
        return complete_menu(result);
    }
    if (keys & 1) {
        func_08141540(0x64);
        return complete_menu(result);
    }
    if (keys & 0x10) {
        if (g_state_020020D0.page_count == 1) {
            return 0;
        }
        changed = 1;
        if (g_state_020020D0.page < g_state_020020D0.page_count - 1) {
            g_state_020020D0.page++;
        } else {
            g_state_020020D0.page = 0;
        }
    } else if (keys & 0x20) {
        if (g_state_020020D0.page_count == 1) {
            return 0;
        }
        changed = 1;
        if (g_state_020020D0.page != 0) {
            g_state_020020D0.page--;
        } else {
            g_state_020020D0.page = g_state_020020D0.page_count - 1;
        }
    }
    if (changed == 0) {
        return 0;
    }
    func_08141540(0x6D);
    func_08013364();
    func_08011B30(9, g_state_020020D0.page);
    return 1;
}
