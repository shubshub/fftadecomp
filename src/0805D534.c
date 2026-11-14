#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1198];
    u8 result;
    u8 phase;
    u8 next_phase;
    u8 unknown_119B[2];
    u8 message;
} MenuState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern MenuState *data_0200F448;
extern InputState data_03000000;
extern u8 data_030008B0[];

extern void func_08022B24(void);
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 width, s16 height, u8 enabled);
extern void func_08061028(void *context, u8 entry);
extern u16 func_08011860(void);
extern s16 func_0805F4AC(void);
extern void func_0805F44C(u8 id);
extern u8 func_08060DD4(void);
extern s16 func_08060DC4(void);
extern void func_0805F4D8(u8 id, u8 mode);
extern void func_0805D23C(s16 mode);
extern void func_08013364(void);
extern void func_080610F8(u8 entry);

// Complete [0x0805D534, 0x0805D784): 592 bytes, 186 instructions.
u32 func_0805D534(void)
{
    switch (data_0200F448->phase) {
    case 0:
        func_08022B24();
        func_08029E48(data_030008B0, 0, 0, 20, 17, 1);
        func_08061028(data_0200F448, data_0200F448->message);
        data_0200F448->next_phase = 3;
        data_0200F448->phase = 1;
        break;
    case 1:
        if (func_08011860() != 0)
            data_0200F448->phase = data_0200F448->next_phase;
        break;
    case 2:
        if (func_0805F4AC() != 0)
            data_0200F448->phase = data_0200F448->next_phase;
        break;
    case 3:
        func_0805F44C(1);
        data_0200F448->next_phase = 4;
        data_0200F448->phase = 2;
        break;
    case 4:
        switch (func_08060DD4()) {
        case 1:
        case 2:
            func_0805F4D8(0, 1);
            func_0805D23C(3);
            break;
        case 3:
        case 4:
            func_0805F4D8(0, 1);
            func_0805D23C(func_08060DC4());
            break;
        }
        break;
    case 5:
        func_08013364();
        func_080610F8(data_0200F448->message);
        data_0200F448->next_phase = 8;
        data_0200F448->phase = 1;
        break;
    case 6:
        func_08013364();
        func_080610F8(data_0200F448->message);
        data_0200F448->next_phase = 7;
        data_0200F448->phase = 1;
        break;
    case 7:
        if (data_03000000.pressed & 1) {
            func_08013364();
            func_080610F8(0x3F);
            data_0200F448->next_phase = 3;
            data_0200F448->phase = 1;
        }
        break;
    case 8:
        data_0200F448->next_phase = 9;
        data_0200F448->phase = 1;
        break;
    case 9:
        data_0200F448->phase = 0;
        return data_0200F448->result;
    case 10:
        data_0200F448->phase = 0;
        return 6;
    case 11:
        func_0805D23C(1);
        break;
    case 12:
        func_0805D23C(2);
        break;
    }
    return 2;
}
