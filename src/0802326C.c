#include "ffta.h"

/* 0x0802326C..0x0802339E: 306 bytes. */
typedef struct {
    u8 unknown_00;
    u8 active;
    u8 phase;
    u8 sound;
    u16 selection;
    u8 mode;
    u8 action;
    u8 message;
    u8 unknown_09[4];
    u8 timer;
    u8 unknown_0E[0x86];
    u16 flags;
} MenuState;

typedef struct {
    const void *resource;
    u8 unknown_04[0xA8];
    u16 index;
} ResourceState;

typedef struct {
    u16 id;
    u8 unknown_02[26];
} ResourceEntry;

extern MenuState g_state_0200F390;
extern ResourceState g_state_020020D0;
extern const ResourceEntry data_0855187C[];
extern const void *g_table_085567F0[];
extern void func_08025324(u32 size);
extern void func_0802B63C(u32 size);
extern void func_0802B6A0(void);
extern void func_08025374(void);
extern void func_08025448(u32 sound);
extern u32 func_080254A0(void);
extern u32 func_080233A0(u32 value);
extern u32 func_08023488(void);
extern u32 func_08023560(void);
extern u32 func_08023988(void);
extern u32 func_08023A40(void);
extern u32 func_08023AA0(void);
extern u32 func_08023AF4(void);

void func_0802326C(void *context, u8 *state)
{
    switch (*state) {
    case 0:
        func_08025324(0x1600);
        func_0802B63C(0x2E00);
        *state = 1;
        break;
    case 0xFF:
        func_0802B6A0();
        func_08025374();
        break;
    case 1:
        if (g_state_0200F390.phase == 0)
            break;
        g_state_0200F390.active = 1;
        if (g_state_0200F390.phase == 2) {
            g_state_0200F390.phase = 1;
            func_08025448(g_state_0200F390.sound);
            if (g_state_0200F390.flags & 0x20) {
                u16 resource = g_state_0200F390.flags & 0x40;

                if (resource) {
                    u32 offset = g_state_020020D0.index * sizeof(ResourceEntry);
                    const ResourceEntry *entry = (const ResourceEntry *)((const u8 *)data_0855187C + offset);

                    g_state_020020D0.resource = g_table_085567F0[entry->id];
                    g_state_0200F390.message = 0x2E;
                } else {
                    g_state_020020D0.resource = 0;
                    g_state_0200F390.message = 0x2D;
                }
            }
            g_state_0200F390.timer = 8;
            switch (g_state_0200F390.selection) {
            case 0xD:
            case 0xE:
            case 0xF:
                g_state_0200F390.action = 1;
                g_state_0200F390.mode = 2;
                *state = 0x11;
                break;
            case 0x14:
            case 0x15:
            case 0x16:
                g_state_0200F390.action = 8;
                g_state_0200F390.mode = 2;
                *state = 0x11;
                break;
            }
        } else {
            *state = func_080233A0((u8)func_080254A0());
        }
        break;
    case 0x10:
        *state = func_08023488();
        break;
    case 0x11:
        *state = func_08023560();
        break;
    case 0x12:
        *state = func_08023988();
        break;
    case 0x13:
        *state = func_08023A40();
        break;
    case 0x14:
        *state = func_08023AA0();
        break;
    case 0x15:
        *state = func_08023AF4();
        break;
    }
}
