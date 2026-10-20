typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 offset;
} ScriptContext;

u8 func_080C9540(u16 flag);

u32 func_08123ACC(ScriptContext *context, const u8 *script)
{
    if (func_080C9540(script[1] | (script[2] << 8))) {
        u32 displacement = script[3] | (script[4] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
