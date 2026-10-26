typedef unsigned short u16;
typedef signed short s16;

extern u16 func_08141860(s16 x, s16 y);
extern const int data_083943BC[16];

int func_080A83EC(s16 start_x, s16 start_y, s16 end_x, s16 end_y)
{
    int dx = end_x - start_x;
    int dy = end_y - start_y;
    u16 angle = func_08141860(dx, dy);
    unsigned int sector = (((angle >> 8) + 8) & 0xFFu) >> 4;

    return data_083943BC[sector];
}
