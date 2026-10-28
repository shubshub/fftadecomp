typedef unsigned char u8;

struct PackedNibbles {
    u8 low : 4;
    u8 high : 4;
} __attribute__((packed));

/* Target: 080BDB9C..080BDBAC, 16 bytes. */
void func_080BDB9C(const struct PackedNibbles *packed, u8 *low, u8 *high)
{
    struct PackedNibbles value = *packed;

    *low = value.low;
    *high = value.high;
}
