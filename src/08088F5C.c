typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 enabled : 1;
    u8 unknown_flags : 7;
    u8 unknown_001[0x10C];
    u8 first_entry;
    u8 second_entry;
    u8 third_entry;
} DisplayEntries;

typedef struct {
    u8 unknown_000[0x569];
    u8 first_enabled;
    u8 second_enabled;
    u8 third_enabled;
} DisplayContext;

typedef struct {
    u32 unknown_00;
    u8 *surface;
} RenderState;

extern DisplayContext *data_03002818;
extern RenderState data_03000E30;
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);

/* Complete [0x08088F5C, 0x08088FEC): 144 bytes, including literal pools. */
void func_08088F5C(DisplayEntries *entries)
{
    entries->enabled = 0;
    if (data_03002818->first_enabled)
        func_0804C788(data_03000E30.surface, entries->first_entry, 0xF0, 0xF0);
    if (data_03002818->second_enabled)
        func_0804C788(data_03000E30.surface, entries->second_entry, 0xF0, 0xF0);
    if (data_03002818->third_enabled)
        func_0804C788(data_03000E30.surface, entries->third_entry, 0xF0, 0xF0);
}
