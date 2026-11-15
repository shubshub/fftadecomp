#include "ffta.h"

/* Complete target: [0x080593E0, 0x08059452), 114 bytes, 45 instructions. */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06[2];
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

typedef struct {
    u8 unknown_0000[0x2E78];
    UnitTemplate templates[256];
} GameState;

typedef struct {
    u8 unknown_0000[0x1BC0];
    u8 control;
} MenuContext;

extern MenuContext *data_0200F428;
extern GameState g_state_02000000;
extern u8 func_080CCB08(u8 index);
extern u32 func_080CCB28(u8 index);
extern void func_08029C34(void *control, u8 value, u8 first, u8 second,
                          u8 fourth, u8 fifth, u8 sixth);

void func_080593E0(u8 index)
{
    u8 first = func_080CCB08(index);
    u8 fourth = func_080CCB28(index);

    func_08029C34(&data_0200F428->control,
                  g_state_02000000.templates[index].appearance, first, 0,
                  fourth, g_state_02000000.templates[index].name ? 1 : 2, 0);
}
