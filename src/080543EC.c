typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef void (*MenuCallback080543EC)(u8 index, u8 *state);
typedef void (*ClearBuffer080543EC)(void *destination, u32 size);

typedef struct {
    u16 value;
    u8 count;
    u8 current;
    u8 active_count;
    u8 state;
    u8 unknown_06[2];
    MenuCallback080543EC *callbacks;
    u8 *states;
} Runner080543EC;

typedef struct {
    u8 unknown_00[0x7A0];
} MenuContext080543EC;

typedef struct {
    u8 unknown_0000[0xCD4];
    MenuContext080543EC menu;
    u8 state;
    u8 unknown_1475[3];
    Runner080543EC runner;
    MenuCallback080543EC callbacks[1];
    u8 callback_states[1];
    u8 unknown_148D[0x1B13];
} MenuState080543EC;

extern MenuState080543EC *data_0200F428;
extern u8 g_state_0200F390;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern ClearBuffer080543EC const g_callbacks_0836D4B8[];

extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_08006A7C(Runner080543EC *runner,
                          MenuCallback080543EC *callbacks, u8 *states, u8 count);
extern void func_08006ADC(Runner080543EC *runner, u8 index,
                          MenuCallback080543EC callback);
extern void func_08054664(u8 index, u8 *state);
extern void func_08029E48(void *graphics, void *unused, const u16 *scratch,
                          s16 column, s16 row, u8 enabled);
extern void func_0802B53C(MenuContext080543EC *menu, u8 state);
extern void func_080069F4(Runner080543EC *runner, u8 count);
extern void func_0802AD54(MenuContext080543EC *menu);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

/* Complete [0x080543EC, 0x0805451C): 304 bytes, 102 instructions. */
void func_080543EC(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
        data_0200F428 = func_08022840(sizeof(*data_0200F428));
        g_callbacks_0836D4B8[0](data_0200F428, sizeof(*data_0200F428));
        func_08006A7C(&data_0200F428->runner, data_0200F428->callbacks,
                      data_0200F428->callback_states, 1);
        func_08006ADC(&data_0200F428->runner, 0, func_08054664);
        func_08029E48(data_030008B0, data_03000990, 0, 20, 17, 1);
        data_0200F428->state = 1;
        *state = 1;
        break;
    case 1:
        if (g_state_0200F390 == 0) {
            data_0200F428->state = 2;
            *state = 2;
            func_0802B53C(&data_0200F428->menu, 0);
        }
        break;
    case 2:
        func_080069F4(&data_0200F428->runner, 1);
        func_0802AD54(&data_0200F428->menu);
        *state = data_0200F428->state;
        break;
    case 0xFE:
        if (data_0200F428 != 0) {
            func_08022854(data_0200F428);
            data_0200F428 = 0;
        }
        func_08009AFC(0xA7);
        func_08009FD0();
        *state = 0xFF;
        break;
    case 0xFF:
        break;
    }
}
