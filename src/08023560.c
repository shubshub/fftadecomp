#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00;
    u8 active;
    u8 phase;
    u8 sound;
    u16 selection;
    u8 mode;
    u8 action;
    u8 message;
    u8 saved_sound;
    u16 saved_selection;
    u8 unknown_0C;
    u8 timer;
    u8 unknown_0E[0x4E];
    u8 *object;
    u8 unknown_60[0x34];
    u16 flags;
} MenuState;

typedef struct {
    const void *resource;
    u8 unknown_04[4];
    const void *argument;
    u8 unknown_0C[0xA];
    s16 choice;
    u8 unknown_18[0x94];
    u16 index;
} ResourceState;

typedef struct {
    u16 id;
    u8 unknown_02[26];
} ResourceEntry;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} TilemapSurface;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern MenuState g_state_0200F390;
extern ResourceState g_state_020020D0;
extern const ResourceEntry data_0855187C[];
extern const void *g_table_085567F0[];
extern const u8 data_08497418[];
extern BufferCopier data_0836D4BC[];
extern TilemapSurface data_030008B0;
extern TilemapSurface data_03000990;
extern void func_0802542C(u8 sound);
extern s32 func_08025464(void);
extern s32 func_080254A0(void);
extern void func_080A9548(void);
extern void *func_0802D72C(u8 first);
extern void func_0802D704(void *object);
extern u8 func_0802B880(void *task);
extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                         u16 index, u8 *status, u8 *mode);
extern u16 func_08014778(const u8 *text);
extern u16 func_08018CB8(u8 *destination, s8 width);
extern void func_080185C8(void *context, void *buffer, void *resource,
                          void *secondary, u16 tile);
extern void func_08018624(s8 x, u8 y, u16 text, u8 width, u16 value,
                          const void *argument);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern u8 func_080C95A8(u16 selector);
extern void func_08016A98(u16 *destination, u8 width, u8 height, u16 value,
                          u16 stride);
extern u16 func_08018790(void);
extern void func_08018AA8(void);
extern u16 func_080294D8(void);
extern void func_080A9528(void);
extern u32 func_080294FC(void);
extern void *func_0802B70C(Unit *unit, u32 flags);

/* Complete [0x08023560, 0x08023988): 1064 bytes, 389 instructions,
   including the literal pools and the sixteen-entry jump table at 0x0802358C. */
u32 func_08023560(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        func_0802542C(g_state_0200F390.sound);
        g_state_0200F390.mode = 1;
        break;
    case 1:
        {
            s16 result;

            if ((result = func_08025464()) != 0) {
                s16 choice;

                if (result < 0) {
                    g_state_0200F390.phase = 0x80;
                    g_state_0200F390.active = 0;
                    return 1;
                }
                choice = func_080254A0();
                g_state_0200F390.saved_selection = g_state_0200F390.selection;
                g_state_0200F390.saved_sound = g_state_0200F390.sound;
                switch (choice) {
                case 0x109:
                    g_state_0200F390.sound = 0xE;
                    g_state_0200F390.selection = 0x15;
                    g_state_0200F390.message = 0x30;
                    break;
                case 0x94:
                case 0xD3:
                    g_state_0200F390.sound = 0xD;
                    g_state_0200F390.selection = 0x14;
                    g_state_0200F390.message = (choice == 0x94) ? 0x2B : 0x2C;
                    break;
                case 0x21:
                    g_state_0200F390.sound = 0xF;
                    g_state_0200F390.selection = 0x16;
                    g_state_0200F390.flags |= 0x20;
                    if (g_state_0200F390.flags & 0x40) {
                        const ResourceEntry *entry =
                            &data_0855187C[g_state_020020D0.index];

                        g_state_020020D0.resource = g_table_085567F0[entry->id];
                        g_state_0200F390.message = 0x2E;
                    } else {
                        g_state_020020D0.resource = 0;
                        g_state_0200F390.message = 0x2D;
                    }
                    break;
                default:
                    g_state_0200F390.phase = 0;
                    g_state_0200F390.active = 0;
                    return 1;
                }
                func_080A9548();
                func_0802D704(func_0802D72C(1));
                g_state_0200F390.action = 5;
                g_state_0200F390.mode = 4;
            }
        }
        break;
    case 2:
        if (g_state_0200F390.timer != 0) {
            g_state_0200F390.timer--;
            if (g_state_0200F390.timer != 0)
                break;
        }
        g_state_0200F390.mode = g_state_0200F390.action;
        break;
    case 3:
        if (func_0802B880(func_0802D72C(1)) & 2)
            g_state_0200F390.mode = g_state_0200F390.action;
        break;
    case 4:
        if ((func_0802B880(func_0802D72C(1)) & 3) == 3)
            g_state_0200F390.mode = g_state_0200F390.action;
        break;
    case 5:
        g_state_0200F390.timer = 4;
        g_state_0200F390.action = 6;
        g_state_0200F390.mode = 2;
        break;
    case 6:
        func_0802542C(g_state_0200F390.sound);
        g_state_0200F390.mode = 8;
        break;
    case 8:
        {
            u8 *object = func_08022840(0x4D8);
            u8 *text;
            u8 *message;

            g_state_0200F390.object = object;
            text = object + 0x3D8;
            message = object + 0x458;
            func_08013E9C(message, data_08497418, text,
                          g_state_0200F390.message, 0, 0);
            g_state_020020D0.argument = g_state_020020D0.resource;
            func_08018CB8(text, (0xC0 - (u8)func_08014778(message)) >> 1);
            data_0836D4BC[0](text + 3, message, 0xFD);
            func_080185C8(g_state_0200F390.object, text,
                          &data_030008B0, &data_03000990, 0xE0);
            func_08018624(-1, 1, 0xFFFF, 0x18, 0, g_state_020020D0.resource);
            func_0802A2C0(2, 1, 0x1A, 2);
            g_state_0200F390.action = 7;
            g_state_0200F390.mode = 0xA;
        }
        break;
    case 7:
        if (func_080C95A8(13) == 1)
            g_state_0200F390.timer = 4;
        else
            g_state_0200F390.timer = 2;
        g_state_0200F390.action = 0xB;
        g_state_0200F390.mode = 2;
        break;
    case 10:
        if (func_08018790())
            g_state_0200F390.mode = g_state_0200F390.action;
        break;
    case 11:
        if ((g_state_020020D0.choice = func_08025464()) != 0) {
            func_08018AA8();
            g_state_0200F390.action = 9;
            g_state_0200F390.mode = 0xA;
        }
        break;
    case 9:
        if (func_080C95A8(13) == 1)
            g_state_0200F390.timer = 4;
        else
            g_state_0200F390.timer = 2;
        func_08016A98(data_03000990.tilemap + 0x22, 0x1A, 2, 0, 0x20);
        func_08016A98(data_030008B0.tilemap + 0x22, 0x1A, 2, 0, 0x20);
        g_state_0200F390.action = 0xC;
        g_state_0200F390.mode = 2;
        break;
    case 12:
        {
            s16 choice = g_state_020020D0.choice;

            func_0802A2C0(0, 0, 0, 0);
            func_08022854(g_state_0200F390.object);
            g_state_0200F390.object = 0;
            if (g_state_0200F390.selection == 0x16
                && !(g_state_0200F390.flags & 0x40))
                g_state_020020D0.index = func_080294D8();
            if (choice >= 0) {
                g_state_0200F390.phase = 0;
                g_state_0200F390.active = 0;
                g_state_0200F390.mode = 0xF;
            } else {
                func_080A9528();
                func_0802B70C((Unit *)func_080294FC(), 0);
                g_state_0200F390.phase = 2;
                g_state_0200F390.flags &= ~0x20;
                g_state_0200F390.flags &= ~0x40;
                g_state_0200F390.selection = g_state_0200F390.saved_selection;
                g_state_0200F390.sound = g_state_0200F390.saved_sound;
                g_state_0200F390.action = 0xF;
                g_state_0200F390.mode = 3;
            }
        }
        break;
    case 15:
        return 1;
    }
    return 0x11;
}
