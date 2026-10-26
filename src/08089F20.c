typedef unsigned short u16;

void func_08089F20(u16 *destination, u16 tile, u16 stride,
                   u16 width, u16 height, u16 flags)
{
    int row;

    for (row = 0; row < height; row++) {
        int column;

        for (column = 0; column < width; column++, tile += 2) {
            u16 *bottom = destination + stride;

            destination[column] = tile | flags;
            bottom[column] = (tile + 1) | flags;
        }

        destination += stride * 2;
    }
}
