#include "ffta.h"

typedef struct {
    const u8 *graphics;
    u16 x;
    u16 y;
    u8 unknown_08[8];
} Animation;

typedef struct {
    u8 unknown_0000[0x119D];
    u8 selection;
    u8 unknown_119E[4];
    u8 event;
    u8 unknown_11A3[0x2D9];
    Animation animations[2];
    u8 unknown_149C[0x18];
} MenuState;

typedef struct {
    u8 unknown_0000[0x219E];
    u16 pending;
} RootState;

typedef void (*ClearCallback)(void *destination, u32 size);

extern MenuState *data_0200F448;
extern RootState g_state_02000000;
extern u8 g_state_0200F390[];
extern u8 data_030008B0[];
extern const u8 data_0851BA72[];
extern const u8 data_0851BA7A[];
extern const ClearCallback g_callbacks_0836D4B8[];

void *func_08022840(u32 size);
void func_08022854(void *allocation);
void func_08029E48(void *graphics, u32 x, u32 y,
                   u32 width, u32 height, u32 value);
void func_08017FA8(Animation *animation, const u8 *graphics, u16 x, u16 y);
void func_08009AFC(u16 event);
void func_08009FD0(void);
void func_0805F588(MenuState *state);
u32 func_0805D534(void);
u32 func_0805D784(void);
u32 func_0805EAA8(void);
u32 func_0805EFEC(void);
u8 func_0805F2A8(void);
u32 func_0805F330(void);
void func_08011C60(MenuState *state);

/* Complete [0x0805CF5C, 0x0805D0E0): 388 bytes. */
void func_0805CF5C(void *context, u8 *phase)
{
    switch (*phase) {
    case 0:
        data_0200F448 = func_08022840(sizeof(MenuState));
        g_callbacks_0836D4B8[0](data_0200F448, sizeof(MenuState));
        g_state_02000000.pending = 0;
        data_0200F448->selection = 0x3E;
        func_08029E48(data_030008B0, 0, 0, 20, 17, 1);
        func_08017FA8(&data_0200F448->animations[0], data_0851BA72, 216, 14);
        func_08017FA8(&data_0200F448->animations[1], data_0851BA7A, 24, 14);
        *phase = 1;
        break;
    case 0xFF:
        if (data_0200F448 == 0)
            return;
        func_08022854(data_0200F448);
        data_0200F448 = 0;
        break;
    case 8:
        if (data_0200F448->event != 0)
            func_08009AFC(data_0200F448->event);
        func_08009FD0();
        *phase = 0xFF;
        break;
    case 1:
        if (g_state_0200F390[0] == 0) {
            func_0805F588(data_0200F448);
            *phase = 2;
        }
        break;
    case 2:
        *phase = func_0805D534();
        break;
    case 3:
        *phase = func_0805D784();
        break;
    case 4:
        *phase = func_0805EAA8();
        break;
    case 5:
        *phase = func_0805EFEC();
        break;
    case 6:
        if (func_0805F2A8())
            *phase = 8;
        break;
    case 7:
        *phase = func_0805F330();
        break;
    }
    if (*phase > 1 && data_0200F448 != 0)
        func_08011C60(data_0200F448);
}
