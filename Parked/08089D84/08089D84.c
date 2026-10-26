typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct TileBuffer {
    u8 unknown_00[0x18];
    u16 *tiles;
    u8 unknown_1C[0xC];
    u8 width;
};

struct Point {
    s8 x;
    s8 y;
};

struct Rectangle {
    s8 x;
    s8 y;
    s8 width;
    s8 height;
};

static inline void copy_row(u16 *source, u16 *destination, s8 width)
{
    int column;

    for (column = 0; column < width; column++)
        destination[column] = source[column];
}

void func_08089D84(struct TileBuffer *source, struct TileBuffer *destination,
                   struct Point origin, struct Rectangle rectangle)
{
    int row;

    for (row = 0; row < rectangle.height; row++) {
        u16 *source_row = source->tiles + origin.x
            + (origin.y + row) * source->width;
        u16 *destination_row = destination->tiles + rectangle.x
            + (rectangle.y + row) * destination->width;

        copy_row(source_row, destination_row, rectangle.width);
    }
}
