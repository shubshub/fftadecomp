#include "ffta.h"

/* Complete [0x08059344, 0x080593E0): 156 bytes, 66 instructions and four
 * literal words.
 * f0b5474680b486b0041c2406240e09060f0e1206
 * 160e201c73f0d4fb051c2d062d0ea846201c73f0
 * ddfb0006000e0c490968de2252018b180a4a2401
 * 0a4d511961180978009141460191002102910390
 * a418064aa4182068002809d0012008e028f40002
 * 000000027d2e0000782e00000220049000200590
 * 181c391c321c0823d0f74efa381c311c0a220a23
 * d0f7ceff06b008bc9846f0bc01bc0047
 */
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
    u8 unknown_00[0x1084];
    u8 value_1084;
    u8 value_1085;
    u8 value_1086;
    u8 value_1087;
    u8 value_1088;
    u8 value_1089;
    u8 value_108a;
    u8 value_108b;
} State08029864;

typedef struct {
    u8 unknown_0000[0x1BC0];
    State08029864 control;
} MenuContext;

extern MenuContext *data_0200F428;
extern GameState g_state_02000000;
extern u8 func_080CCB08(u8 index);
extern u32 func_080CCB28(u8 index);
extern void func_08029864(State08029864 *state, u8 a, u8 b, u8 c,
                          u8 d, u8 e, u8 f, u8 g, u8 h, u8 i);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);

void func_08059344(u8 index, u8 x, u8 y)
{
    u8 first = func_080CCB08(index);
    u8 second = func_080CCB28(index);

    func_08029864(&data_0200F428->control, x, y, 8,
                  g_state_02000000.templates[index].appearance, first, 0,
                  second, g_state_02000000.templates[index].name ? 1 : 2, 0);
    func_0802A370(x, y, 10, 10);
}
