typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 unknown_0000[0x1089];
    u8 status;
} MenuControl;

typedef struct {
    void *first;
    u8 *source;
    u16 count;
    u8 unknown_0A[2];
    u16 *data;
    u16 index;
    u16 elapsed;
    u16 frame;
    u8 loop;
    u8 unknown_17;
    u16 finished;
} AnimationState;

typedef struct {
    u8 unknown_0000[0x1BB6];
    u8 selected;
    u8 unknown_1BB7[9];
    MenuControl control;
    u8 unknown_2C4C[0x33E8 - 0x2C4C];
    AnimationState animation;
} MenuContext;

typedef struct {
    u32 value;
    u8 unknown_04[12];
} SelectionEntry;

typedef struct {
    u8 unknown_0000[0x2E78];
    SelectionEntry entries[256];
} SelectionState;

extern MenuContext *data_0200F428;
extern SelectionState g_state_02000000;
extern void func_0802995C(MenuControl *control);
extern u8 func_08029D2C(const MenuControl *control);
extern void *func_0802B3D4(AnimationState *state);
extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);

/* Complete [0x0805C434, 0x0805C4BC): 136 bytes, including literal pools. */
void func_0805C434(u16 x, u16 y)
{
    func_0802995C(&data_0200F428->control);
    if (func_08029D2C(&data_0200F428->control) == 1) {
        u32 state_address = (u32)&g_state_02000000;
        SelectionEntry *entry = (SelectionEntry *)(state_address +
            data_0200F428->selected * sizeof(SelectionEntry) + 0x2E78);

        if (entry->value != 0)
            func_08001CF0(func_0802B3D4(&data_0200F428->animation),
                          (s16)x, (s16)y, 0, 0, 0, 0, 0, 800, 0, 0);
    }
}
