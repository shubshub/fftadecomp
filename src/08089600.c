typedef unsigned short u16;

void func_08089600(u16 *destination, u16 tile, u16 count, u16 flags)
{
    int column;

    for (column = 0; column < count; column++, destination++, tile += 2) {
        *destination = tile | flags;
        destination[count] = (tile + 1) | flags;
    }
}
