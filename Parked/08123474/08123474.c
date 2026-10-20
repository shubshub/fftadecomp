typedef unsigned char u8;
typedef unsigned int u32;

void func_08124974(u8 start_x, u8 start_y, u8 end_x, u8 end_y, u8 value);

/* 0x08123474 - target extent is 64 bytes; this candidate is not byte-identical. */
u32 func_08123474(void *context, const u8 *script)
{
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    int start = script[1];
    int end = script[2];

    if (start == end)
        return 0x110;

    start_x = start & 0xF;
    start_y = (start & 0xF0) >> 4;
    end_x = end & 0xF;
    end_y = (end & 0xF0) >> 4;

    if (start_x == end_x || start_y == end_y)
        func_08124974(start_x, start_y, end_x, end_y, script[3]);
    return 0x110;
}
