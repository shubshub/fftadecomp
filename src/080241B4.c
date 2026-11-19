#include "control_flags.h"

/* Complete [0x080241B4, 0x080245DC): 1064 bytes, 329 instructions,
   including the literal pools and the 35-entry jump table at 0x080241F8. */
typedef struct {
    u8 mode;
    u8 unknown_01[0x0D];
    u8 unknown_0E;
    u8 unknown_0F[0x18];
    u8 delay;
    u8 unknown_28[0x6C];
    u16 flags;
} State080241B4;

typedef struct {
    u8 unknown_00[8];
    void *entries;
} Owner080241B4;

typedef struct {
    u8 unknown_00[0x1F];
    s8 facing;
} SceneObject080241B4;

typedef struct {
    u8 unknown_00[7];
    u8 flags;
} InputState080241B4;

extern State080241B4 g_state_0200F390;
extern Table data_03002710;
extern InputState080241B4 data_03000000;
extern void *data_030027F4;
extern u8 data_0600E000[];
extern u8 data_06005000[];

extern u8 func_080C95A8(u16 index);
extern u8 func_080C9540(u16 flag);
extern void func_0801A100(u16 index, u8 value);
extern void func_0801A518(u8 index, u8 *state);
extern void func_0802321C(u8 index, u8 *flag);
extern u8 func_0801AE10(void);
extern void func_0801AE34(void);
extern u8 func_0801AE48(void);
extern void func_0801DB3C(void);
extern void func_0801DB78(void);
extern void func_0801E610(u8 *first, u8 *second);
extern u8 func_0801E648(void);
extern u8 func_0801E658(void);
extern u16 func_080035A8(u8 layer);
extern void func_08022C44(u8 timer);
extern u8 func_08022D48(u8 mode);
extern void func_08022CD4(u16 duration, u8 mode);
extern void func_08022E90(u16 duration, u8 mode);
extern u8 func_08022F00(u8 mode);
extern void func_08022E58(void);
extern u8 func_08022044(Owner080241B4 *owner);
extern void func_08022068(Owner080241B4 *object);
extern void *func_08096D7C(void);
extern Owner080241B4 *func_08099C30(void *object);
extern SceneObject080241B4 *func_08099560(void *context, void *record);
extern void func_0809836C(SceneObject080241B4 *object, u16 action, s8 value,
                          u16 option);
extern void func_080245DC(u8 reset);
extern void func_08024670(u8 reset);
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 func_080241B4(void)
{
    if (func_080C95A8(13) == 1 && (g_state_0200F390.flags & 0x400))
        return 2;

    switch (g_state_0200F390.mode) {
    case 0:
        /* Idle.  The table at 0x080241F8 starts at mode 0 (entries 0-7 go
           to 0x080245CE) and 0x080241DE compares the unbiased mode with
           #0x22. */
        break;
    case 8:
        return 0xFE;
    case 0xA:
        func_0801A100(func_080C95A8(7), 0);
        func_08006ADC(&data_03002710, 3, (u32)func_0801A518);
        g_state_0200F390.mode = 0xB;
        break;
    case 0xB:
        if (func_0801AE10()) {
            u8 first;
            u8 second;

            func_0801DB3C();
            func_0801E610(&first, &second);
            if (func_0801E648())
                g_control_flags_03000940.display |= func_080035A8(first);
            if (func_0801E658())
                g_control_flags_03000940.display |= func_080035A8(second);
            g_control_flags_03000940.display |= 0x1C40;
            func_08022C44(6);
            data_03000000.flags |= 1;
            g_state_0200F390.mode = 0xE;
        }
        break;
    case 0xC:
        func_0801AE34();
        g_state_0200F390.mode = 0xD;
        break;
    case 0xD:
        if (func_0801AE48()) {
            func_0801DB78();
            if (g_state_0200F390.unknown_0E)
                g_state_0200F390.mode = 8;
            else
                g_state_0200F390.mode = 0xE;
        }
        break;
    case 0xF:
        if (func_08022D48(15))
            g_state_0200F390.mode = 0;
        break;
    case 0x10:
        if (func_08022D48(16))
            g_state_0200F390.mode = 0xC;
        break;
    case 0x11:
        g_state_0200F390.unknown_0E = 1;
        func_08022CD4(16, 16);
        g_state_0200F390.mode = 0x10;
        break;
    case 0x12:
        g_state_0200F390.unknown_0E = 1;
        g_state_0200F390.mode = 0xC;
        break;
    case 0x13:
        if (func_08022D48(16))
            g_state_0200F390.mode = 0x14;
        break;
    case 0x14:
        g_state_0200F390.delay = 8;
        func_080245DC(1);
        g_state_0200F390.mode = 0x16;
        break;
    case 0x16:
        if (g_state_0200F390.delay != 0) {
            g_state_0200F390.delay--;
            if (g_state_0200F390.delay != 0)
                break;
        }
        g_state_0200F390.mode = 0x15;
        break;
    case 0x15:
        func_08006ADC(&data_03002710, 8, (u32)func_0802321C);
        g_state_0200F390.mode = 0x17;
        break;
    case 0x17:
        if (data_03002710.flags[8] == 0xFF)
            g_state_0200F390.mode = 0x18;
        break;
    case 0x18:
        func_08024670(1);
        g_state_0200F390.mode = 0x1A;
        break;
    case 0x1A:
        {
            u16 zero;
            u16 zero2;

            zero = 0;
            func_0814186C(&zero, data_0600E000, 0x01000800);
            zero2 = 0;
            func_0814186C(&zero2, data_06005000, 0x01000800);
        }
        func_08022068(func_08099C30(func_08096D7C()));
        g_state_0200F390.mode = 0x19;
        break;
    case 0x19:
        if (func_08022044(func_08099C30(func_08096D7C()))) {
            func_0801DB3C();
            func_08022E58();
            if (data_030027F4 != 0) {
                SceneObject080241B4 *object =
                    func_08099560(func_08096D7C(), data_030027F4);

                if (object != 0)
                    func_0809836C(object, 10, object->facing, 0);
                data_030027F4 = 0;
            }
            func_08022CD4(8, 15);
            g_state_0200F390.mode = 0xF;
        }
        break;
    case 0x1B:
        if (func_08022F00(16))
            g_state_0200F390.mode = 0x1C;
        break;
    case 0x1C:
        func_080245DC(0);
        g_state_0200F390.mode = 0x1D;
        break;
    case 0x1D:
        func_08006ADC(&data_03002710, 8, (u32)func_0802321C);
        g_state_0200F390.mode = 0x1E;
        break;
    case 0x1E:
        if (func_080C9540(0x4A)) {
            if (data_03002710.flags[8] == 0xFD)
                g_state_0200F390.mode = 0x1F;
        } else {
            if (data_03002710.flags[8] == 0xFF)
                g_state_0200F390.mode = 0x1F;
        }
        break;
    case 0x1F:
        func_08024670(0);
        g_state_0200F390.mode = 0x22;
        break;
    case 0x22:
        {
            u16 zero;
            u16 zero2;

            zero = 0;
            func_0814186C(&zero, data_0600E000, 0x01000800);
            zero2 = 0;
            func_0814186C(&zero2, data_06005000, 0x01000800);
        }
        func_08022068(func_08099C30(func_08096D7C()));
        g_state_0200F390.mode = 0x20;
        break;
    case 0x20:
        if (func_08022044(func_08099C30(func_08096D7C()))) {
            func_08022E90(8, 15);
            g_state_0200F390.mode = 0x21;
        }
        break;
    case 0x21:
        if (func_08022F00(15))
            g_state_0200F390.mode = 0;
        break;
    }
    return 2;
}
