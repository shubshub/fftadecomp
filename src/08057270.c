/* Target: 40 bytes / 15 instructions, 0x08057270..0x08057298. */
typedef unsigned char u8;

typedef struct {
    u8 unknown_0000[0x2D38];
    u8 value_2D38;
} State;

extern State *data_0200F428;
extern void func_08141540(unsigned int delay);

void func_08057270(u8 *value)
{
    func_08141540(100);
    *value = 220;
    data_0200F428->value_2D38 = 120;
}
