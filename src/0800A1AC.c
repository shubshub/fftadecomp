typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 unknown_00;
    u16 value;
} Context0800A1AC;

void func_0800A1AC(Context0800A1AC *context, const u8 *instruction)
{
    context->value += instruction[1] | (instruction[2] << 8);
}
