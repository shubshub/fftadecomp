typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unknown_00;
    u8 identifier;
    u16 value;
    u8 unknown_04[8];
} ScriptEntry;

typedef struct {
    u8 unknown_0000[0x3C24];
    u32 flags;
} ScriptState;

extern const ScriptEntry g_table_08563A70[];
extern ScriptState g_state_02000000;

void func_08009C04(u16 value, u16 mode);
void func_0802292C(u32 value);

u32 func_08123898(void *context, const u8 *script)
{
    u32 identifier = script[1] | (script[2] << 8);
    int index = 255;
    const ScriptEntry *entries = g_table_08563A70;
    u8 *selected = (u8 *)0x02003C2A;

    do {
        if (entries[index].identifier == identifier) {
            *selected = index;
            func_08009C04(entries[index].value, 0);
            break;
        }
        index--;
    } while (index > 0);
    if (identifier != 1)
        func_0802292C(13);
    g_state_02000000.flags |= 0x10;
    return 0x110;
}
