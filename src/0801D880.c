/* 0801D880..0801D890: read the state byte at offset 0x228. */
typedef unsigned char u8;

typedef struct {
    u8 unknown_000[0x228];
    u8 value;
} State0801D880;

extern State0801D880 g_state_02007F40;

u8 func_0801D880(void)
{
    return g_state_02007F40.value;
}
