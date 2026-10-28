typedef unsigned char u8;
typedef unsigned short u16;

struct Context {
    u8 unknown_00[6];
    u16 tiles[80];
};

extern const u16 data_083AF62C[];

void func_0806F028(struct Context *context)
{
    const u16 *table = data_083AF62C;
    u16 index;

    for (index = 0; index < 80; index++)
        context->tiles[index] = table[index] + 0xC0;
}
