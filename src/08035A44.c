/* Target: 36 bytes / 14 instructions, 0x08035A44..0x08035A68.
 * Return the selected record's byte at offset 1, scaled by eight. */
typedef unsigned char u8;
typedef unsigned int u32;

struct Record20 {
    u8 unknown_00;
    u8 value_01;
    u8 unknown_02[18];
};

struct ModuleState {
    u8 unknown_000[0x67C];
    struct Record20 *records;
};

extern struct ModuleState *g_state_03002810;

u32 func_08035A44(u8 index)
{
    return g_state_03002810->records[index].value_01 << 3;
}
