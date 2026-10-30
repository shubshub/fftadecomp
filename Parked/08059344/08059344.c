#include "ffta.h"

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
    u8 unknown_00[0x1BC0];
    State08029864 field_1bc0;
} State08059344;

extern State08059344 *data_0200F428;
extern u8 g_state_02000000[];
extern u8 func_080CCB08(u8 index);
extern u32 func_080CCB28(u8 index);
extern void func_08029864(State08029864 *state, u8 a, u8 b, u8 c,
                          u8 d, u8 e, u8 f, u8 g, u8 h, u8 i);
extern void func_0802A370(u8, u8, u8, u8);

/* Target [0x08059344, 0x080593E0), 156 complete bytes:
 * f0b5474680b486b0041c2406240e09060f0e1206160e201c73f0d4fb051c2d062d0e
 * a846201c73f0ddfb0006000e0c490968de2252018b180a4a24010a4d511961180978
 * 009141460191002102910390a418064aa4182068002809d0012008e028f4000200000002
 * 7d2e0000782e00000220049000200590181c391c321c0823d0f74efa381c311c0a220a23
 * d0f7ceff06b008bc9846f0bc01bc0047
 */
void func_08059344(u8 index, u8 arg1, u8 arg2)
{
    u8 first = func_080CCB08(index);
    u8 second = (u8)func_080CCB28(index);

    /* The indexed records start at 0x2E78 and have a 16-byte stride. */
    func_08029864(&data_0200F428->field_1bc0, arg1, arg2, 8,
                   g_state_02000000[0x2E7D + index * 16], first, 0, second,
                   ((u32 *)(g_state_02000000 + 0x2E78))[index * 4] ? 1 : 2, 0);
    func_0802A370(arg1, arg2, 10, 10);
}
