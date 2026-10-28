/* Complete 0x0806B460..0x0806B4C4: 100 bytes, 37 instructions. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_0000[0x1A88];
    u8 context[0x29E4];
    u8 next;
} State0806B460;

typedef struct {
    u8 current;
} Command0806B460;

extern State0806B460 *data_0200F428;
extern u8 func_0806FE14(const u8 *context);
extern void func_08141540(u16 sound);

void func_0806B460(Command0806B460 *command)
{
    if (func_0806FE14(data_0200F428->context) == 4) {
        func_08141540(100);
        command->current = 60;
        data_0200F428->next = 23;
    } else if (func_0806FE14(data_0200F428->context) == 1) {
        func_08141540(104);
        command->current = 62;
        data_0200F428->next = 23;
    }
}
