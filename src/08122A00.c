typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 offset;
} ScriptContext;

typedef struct {
    void *object;
} ObjectEntry;

void *func_08096D7C(void);
int func_08099CDC(void *state, ObjectEntry **entries);
u8 func_080C8240(void *object);
u8 func_080C8260(void *object);
u8 func_080C8298(void *object);
u32 func_080C7EA4(void *object, u8 property);
u8 func_080CD92C(void *object);
u8 func_080CD95C(void *object);
u8 func_080CD9A4(void *object);
u8 func_080CD9BC(void *object);

u32 func_08122A00(ScriptContext *context, const u8 *script)
{
    ObjectEntry *entries[13];
    int count = func_08099CDC(func_08096D7C(), entries);
    int index;

    for (index = 0; index < count; index++) {
        ObjectEntry *entry = entries[index];
        u32 property;

        if (func_080C8240(entry->object) ||
            func_080C8260(entry->object) ||
            func_080C8298(entry->object))
            continue;
        property = func_080C7EA4(entry->object, 1);
        if (property == 0x5E || property == 10 || property == 9 ||
            property == 4 || property == 12)
            continue;
        if (func_080CD92C(entry->object) ||
            func_080CD95C(entry->object) ||
            func_080CD9A4(entry->object) ||
            func_080CD9BC(entry->object))
            continue;
        return 0x110;
    }
    context->offset += script[1] | (script[2] << 8);
    return 0x110;
}
