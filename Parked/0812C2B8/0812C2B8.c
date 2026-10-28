#include "ffta.h"

struct Completion0812C2B8 {
    u8 unknown_00[6];
    u8 done;
};

struct Command0812C2B8 {
    u16 state;
    u16 unknown_02;
    struct Completion0812C2B8 *owner;
};

struct Display0812C2B8 {
    u16 flags;
    u8 unknown_02[0x48];
    u32 blend : 8;
    u8 unknown_4B[5];
};

struct Runtime0812C2B8 {
    struct Completion0812C2B8 *owner;
    u8 counter;
    u8 message;
    u8 index;
    u8 unknown_07;
    void *resource;
    struct Display0812C2B8 saved_display;
};

struct GameState0812C2B8 {
    u8 unknown_0000[0x72];
    u16 index;
    u8 unknown_0074[0x211E];
    u16 scene;
};

extern struct Display0812C2B8 g_control_flags_03000940;
extern struct GameState0812C2B8 g_state_02000000;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern u8 data_02003CB0[];

extern void func_08121B78(void *resource);
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void *func_08121B64(u32 size);
extern void func_0801DB78(void);
extern void func_0801174C(void *resource, u32 first, u32 second,
                          void *tiles, void *palette, u32 width, u32 height,
                          u32 count, u32 mode, u32 value);
extern void func_0801339C(u32 mode);
extern u16 func_08011860(void);
extern void func_08145798(void);
extern void func_081452F4(void);
extern void func_080033C8(u32 mode);
extern u32 func_0813B480(u8 index, void *data);
extern void func_0812C170(void);
extern u32 func_0813B0D4(u8 index, void *data);
extern void func_081457FC(void);
extern void func_08141540(u32 sound);
extern void func_08013364(void);
extern void func_08011B30(u32 mode, u8 message);
extern void func_080231C0(void);

/* Complete [0x0812C2B8, 0x0812C4E4): 556 bytes, 229 instructions. */
u32 func_0812C2B8(void *context, struct Command0812C2B8 *command,
                  struct Runtime0812C2B8 *runtime)
{
    switch (command->state) {
    case 1:
        if (runtime->resource != 0) {
            func_08121B78(runtime->resource);
            runtime->resource = 0;
        }
        break;
    case 0: {
        struct Display0812C2B8 *display;

        runtime->owner = command->owner;
        runtime->counter = 0;
        display = &g_control_flags_03000940;
        func_081443FC(&runtime->saved_display, display, 0x50);
        runtime->resource = func_08121B64(0xA04);
        display->flags |= 0xC00;
        display->blend &= 0xE3;
        break;
    }
    case 0x100:
        func_0801DB78();
        if (g_state_02000000.scene == 0x93) {
            runtime->counter = 60;
            command->state = 0x106;
            break;
        }
        func_0801174C(runtime->resource, 1, 31, data_030008B0,
                      data_03000990, 2, 2, 24, 4, 0x3A0);
        func_0801339C(2);
        command->state = 0x101;
        break;
    case 0x101:
        if (func_08011860() == 0)
            break;
        runtime->index = g_state_02000000.index;
        if (runtime->index == 0) {
            runtime->message = 28;
            command->state = 0x103;
        } else {
            runtime->index--;
            command->state = 0x104;
        }
        break;
    case 0x104:
        func_08145798();
        func_081452F4();
        func_080033C8(2);
        if (!(u8)func_0813B480(runtime->index, data_02003CB0)) {
            if (runtime->counter > 1) {
                runtime->message = 28;
                command->state = 0x103;
            } else {
                runtime->counter++;
            }
        } else {
            func_0812C170();
            runtime->counter = 0;
            command->state = 0x105;
        }
        break;
    case 0x105:
        if (!(u8)func_0813B0D4(runtime->index, data_02003CB0)) {
            if (runtime->counter <= 1) {
                runtime->counter++;
            } else {
                runtime->message = 28;
                command->state = 0x103;
            }
        } else {
            runtime->message = 27;
            command->state = 0x103;
        }
        break;
    case 0x103:
        func_081457FC();
        func_08141540(0x70);
        func_08013364();
        func_08011B30(1, runtime->message);
        command->state = 0x102;
        break;
    case 0x102:
        if (func_08011860() != 0) {
            runtime->counter = 60;
            command->state = 0x106;
        }
        break;
    case 0x106:
        if (runtime->counter != 0)
            runtime->counter--;
        if (runtime->counter == 0)
            func_080231C0();
        break;
    case 0x107:
        if (runtime->resource != 0) {
            func_08121B78(runtime->resource);
            runtime->resource = 0;
        }
        runtime->owner->done = 1;
        command->state = 3;
        break;
    }
    return 0;
}
