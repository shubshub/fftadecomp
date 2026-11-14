#include "script_entry.h"

// Complete target: [0x08023AF4, 0x08023DBA), 710 bytes, 244 instructions.

typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    const void *current;
    void *source;
    u8 unknown_08[4];
    u16 id;
    u8 unknown_0E[2];
    u8 unknown_10;
    u8 kind;
    u8 unknown_12;
    u8 unknown_13[0xB4 - 0x13];
    u8 slot;
} Request;

typedef struct {
    u8 unknown_0000[0x20D0];
    Request request;
    u8 unknown_2188[0x2FC4 - 0x2188];
    u8 buffer[0x3C28 - 0x2FC4];
    u16 pending;
    u8 index;
} GlobalState;

typedef struct {
    u8 unknown_00;
    u8 active;
    u8 phase;
    u8 unknown_03[3];
    u8 mode;
    u8 unknown_07[0x5C - 7];
    u8 *object;
} MenuState;

extern GlobalState g_state_02000000;
extern Request g_state_020020D0;
extern MenuState g_state_0200F390;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern BufferCopier data_0836D4BC[];
extern u8 data_030039F8[];
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern u8 data_0851BA72[];
extern u8 data_0851BA7A[];

extern void *func_08096D7C(void);
extern void func_0809A260(void *object, u32 value);
extern void func_080A9548(void);
extern u8 func_080A9588(void);
extern u8 *func_080CBA84(u32 index);
extern u8 func_080C95A8(u16 selector);
extern void *func_080D2DE0(u16 id);
extern void *func_080C83CC(u8 category);
extern void func_08022A04(u8 flags);
extern void *func_08022840(u32 size);
extern void func_0801174C(void *window, u32 kind, u8 selection, void *first,
                          void *second, u32 a, u32 b, u32 c, u32 d, u32 e);
extern void func_08017FA8(void *control, const u8 *text, u32 x, u32 y);
extern u16 func_08011860(void);
extern u8 func_08023DBC(void);
extern void func_08023E88(void);
extern void func_08022854(void *allocation);
extern void func_0802317C(void);
extern void func_0802292C(u8 mask);

u32 func_08023AF4(void)
{
    switch (g_state_0200F390.mode) {
    case 0:
        func_0809A260(func_08096D7C(), 0);
        func_080A9548();
        g_state_0200F390.mode = 1;
        break;
    case 1:
        if (!func_080A9588())
            break;
        data_0836D4BC[0](data_030039F8, func_080CBA84(12) + 0x18, 2);
        {
            const ScriptEntry *entry = &g_table_08563A70[g_state_02000000.index];

            if (entry->flags & 8) {
                Request *request = &g_state_02000000.request;

                request->current = 0;
                request->slot = g_state_02000000.index;
                request->kind = 1;
                request->source = g_state_02000000.buffer;
            } else if (g_state_02000000.pending) {
                if ((u8)func_080C95A8(13) == 1) {
                    Request *request = &g_state_02000000.request;

                    request->id = g_state_02000000.pending;
                    request->kind = 4;
                    request->current = 0;
                    request->slot = 0;
                } else {
                    void *result = func_080D2DE0(g_state_02000000.pending);
                    Request *request = &g_state_02000000.request;

                    request->current = result;
                    request->kind = 5;
                    request->id = 0;
                    request->slot = 0;
                }
                if (g_state_02000000.index == 8) {
                    void *source = func_080C83CC(10);
                    Request *request = &g_state_02000000.request;

                    request->source = source;
                } else {
                    Request *request = &g_state_02000000.request;

                    request->source = g_state_02000000.buffer;
                }
            } else {
                Request *request = &g_state_02000000.request;

                request->current = 0;
                request->slot = g_state_02000000.index;
                request->kind = 1;
                request->source = g_state_02000000.buffer;
            }
        }
        g_state_020020D0.unknown_10 = 0;
        g_state_020020D0.unknown_12 = 4;
        func_08022A04(1);
        g_state_0200F390.mode = 2;
        break;
    case 2:
        {
            u8 *object = func_08022840(0x7B8);

            g_state_0200F390.object = object;
            g_callbacks_0836D4B8[0](object, 0x7B8);
            func_0801174C(object + 4, 9, g_state_020020D0.unknown_10,
                          data_030008B0, data_03000990, 2, 1, 0x18, 0x10,
                          0xE0);
            func_08017FA8(object + 0x798, data_0851BA72, 0xD8, 0xE);
            func_08017FA8(object + 0x7A8, data_0851BA7A, 0x18, 0xE);
        }
        g_state_0200F390.mode = 3;
        break;
    case 3:
        {
            u8 *object = g_state_0200F390.object;

            if (func_08011860()) {
                if (object[1] & 1) {
                    g_state_0200F390.mode = 5;
                } else {
                    if (g_state_020020D0.kind > 1)
                        object[0] = 1;
                    g_state_0200F390.mode = 4;
                }
            }
        }
        func_08023E88();
        break;
    case 4:
        if (func_08023DBC())
            g_state_0200F390.mode = 3;
        func_08023E88();
        break;
    case 5:
        g_state_020020D0.current = 0;
        g_state_020020D0.id = 0;
        g_state_020020D0.slot = 0;
        g_state_020020D0.kind = 0;
        g_state_020020D0.source = 0;
        func_08022854(g_state_0200F390.object);
        g_state_0200F390.object = 0;
        func_0802317C();
        func_0802292C(5);
        g_state_0200F390.phase = 0x80;
        func_0809A260(func_08096D7C(), 1);
        g_state_0200F390.active = 0;
        return 1;
    }
    return 0x15;
}
