#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 identifier : 10;
    u16 unknown_0A : 6;
} Unit;

typedef struct {
    u8 unknown_0000[0x1199];
    u8 state;
    u8 next;
    u8 resume;
    u8 unknown_119C;
    u8 selection;
    u8 unknown_119E[0xB];
    u8 count;
    u8 unknown_11AA[2];
    void *resources[169];
    Unit *current;
} MenuState;

typedef struct {
    void *resource;
    u8 unknown_04[12];
    u8 selection;
} ResourceSelection;

typedef struct {
    u16 held;
    u16 pressed;
} Input;

extern MenuState *data_0200F448;
extern ResourceSelection g_state_020020D0;
extern Input data_03000000;
extern u8 data_030008B0[];
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 width, s16 height, u8 enabled);
extern void func_0805F44C(u8 id);
extern void func_0805F540(void *const *entries, s32 count);
extern s16 func_0805F4AC(void);
extern u16 func_08011860(void);
extern void func_08061028(void *context, u8 entry);
extern void func_08061518(void *context, u8 index);
extern u8 func_0805DA10(u8 selection, u8 count, u8 mode);
extern u8 func_0805D4EC(void);
extern void func_0805DAA8(u8 option);
extern void func_0805D948(void);
extern s8 func_08013380(void);
extern void func_08013390(void *state);
extern void func_08013364(void);
extern void func_0805D13C(u16 value);
extern void func_080D0ED4(Unit *unit);
extern void func_08060DEC(u8 index, u8 value);

// Target [0x0805EFEC, 0x0805F2A6), 698 bytes including the jump table
// and literal pools.
u32 func_0805EFEC(void)
{
    s8 result;

    switch (data_0200F448->state) {
    case 0:
        func_0802A2C0(0, 0, 0, 0);
        data_0200F448->current = 0;
        func_08029E48(data_030008B0, 0, 0, 20, 17, 0);
        func_0805F44C(7);
        func_0805F540(data_0200F448->resources, data_0200F448->count);
        data_0200F448->next = 4;
        data_0200F448->state = 1;
        break;
    case 1:
        if (func_0805F4AC())
            data_0200F448->state = data_0200F448->next;
        break;
    case 2:
        if (func_08011860())
            data_0200F448->state = data_0200F448->next;
        func_0805D948();
        break;
    case 18:
        func_08061028(data_0200F448, data_0200F448->selection);
        data_0200F448->next = data_0200F448->resume;
        data_0200F448->state = 2;
        break;
    case 19:
        func_08061518(data_0200F448, g_state_020020D0.selection);
        data_0200F448->next = data_0200F448->resume;
        data_0200F448->state = 2;
        break;
    case 4:
        if (func_0805DA10(3, 4, 1))
            return func_0805D4EC();
        break;
    case 5:
        func_0805DAA8(1);
        func_0805D948();
        break;
    case 13:
        result = func_08013380();
        func_08013390(data_0200F448);
        if (result < 0) {
            data_0200F448->state = 5;
            break;
        }
        if (result > 0) {
            func_08013364();
            data_0200F448->next = 0;
            data_0200F448->state = 2;
        } else {
            func_08013364();
            data_0200F448->next = 14;
            data_0200F448->state = 2;
        }
        break;
    case 14:
        func_0805D13C(data_0200F448->current->identifier);
        func_080D0ED4(data_0200F448->current);
        data_0200F448->selection = 0x51;
        data_0200F448->resume = 0x11;
        data_0200F448->state = 0x12;
        break;
    case 17:
        if (data_03000000.pressed & 1) {
            data_0200F448->current = 0;
            func_08060DEC(7, 0);
            data_0200F448->state = 12;
            return 2;
        }
        break;
    }
    return 5;
}
