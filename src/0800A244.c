/* 0x0800A244: 170 bytes, ending at 0x0800A2EE. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 unknown_00;
    u16 offset;
} ScriptContext;

void *func_08125578(u8 selector);
u8 func_080C8348(const void *object);
u8 func_080C8364(const void *object);
u8 func_080C8240(const void *object);
u8 func_080C82B8(const void *object);
u8 func_080C8280(const void *object);
u8 func_080CD92C(const void *object);
u8 func_080CD95C(const void *object);
u8 func_080CD9A4(const void *object);
u8 func_080CD9BC(const void *object);

void func_0800A244(ScriptContext *context, const u8 *instruction)
{
    void *object = func_08125578(instruction[1]);

    if (object == 0 || func_080C8348(object) || func_080C8364(object))
        return;

    if (instruction[1] == 0x80) {
        if (func_080C8240(object) && func_080C82B8(object)) {
            if (func_080C8280(object) || func_080CD92C(object))
                return;
        }
    } else if (func_080C8280(object) || func_080CD92C(object) ||
               func_080CD95C(object) || func_080CD9A4(object) ||
               func_080CD9BC(object)) {
        return;
    }

    context->offset += instruction[2] | (instruction[3] << 8);
}
