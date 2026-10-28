#include "ffta.h"

typedef struct {
    u8 *destination;
    u32 value;
    u32 state_value;
} Update0805463C;

typedef struct {
    u8 unknown_0000[0x2D38];
    u8 value_2D38;
} State0805463C;

extern State0805463C *data_0200F428;
extern void func_08141540(u32 sound);

/* 0805463C..08054664: 40 bytes, 14 reachable instructions. */
void func_0805463C(const Update0805463C *update)
{
    *update->destination = update->value;
    data_0200F428->value_2D38 = update->state_value;
    func_08141540(0x69);
}
