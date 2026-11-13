/* Target bytes: f0b584460c1c12061b060026150e1b0e01271de0002c07d02570637010784006400ea070e670043c90784006410e0f2928d001315079c6090e488900091800200856b0402d1a01200856b0401b1a013719040913280400140918c800401a61460a18917880200840002805d10120404209e000003c5d9a085178402008400028c8d0013f381cf0bc02bc0847 */
typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;

struct Cell08148A0C {
    u8 value : 7;
    u8 unknown_0_7 : 1;
    u8 unknown_1;
    u8 direction : 7;
    u8 valid : 1;
    u8 unknown_3;
    u8 unknown_4;
    u8 unknown_5;
    u8 unknown_6;
} __attribute__((packed));

struct Path08148A0C {
    u8 x;
    u8 y;
    u8 value;
    u8 wide;
};

struct Delta08148A0C {
    s8 x;
    s8 y;
    s8 unknown_2;
    s8 unknown_3;
};

extern const struct Delta08148A0C data_089A5D3C[];

int func_08148A0C(struct Cell08148A0C *grid, struct Path08148A0C *output,
                  u8 start_x, u8 start_y)
{
    int wide = 0;
    int x = start_x;
    int y = start_y;
    int count = 1;
    for (;;) {
        struct Cell08148A0C *cell = &grid[(s16)y * 16 + (s16)x];
        int direction;
        if (!cell->valid)
            return -1;
        if (cell->unknown_1 & 0x40) {
            count--;
            break;
        }
        if (output) {
            output->x = x;
            output->y = y;
            output->value = cell->value;
            output->wide = wide;
            output--;
        }
        direction = cell->direction;
        if (direction == 15)
            break;
        direction++;
        wide = cell->unknown_5 >> 7;
        x -= data_089A5D3C[direction].x << wide;
        y -= data_089A5D3C[direction].y << wide;
        count++;
    }
    return count;
}
