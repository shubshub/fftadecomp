typedef unsigned char u8;
typedef unsigned short u16;

struct Context {
    u16 unknown_00;
    u16 position;
};

struct Object {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[19];
    u16 field_18;
    u16 field_1A;
};

extern struct Object *func_08125578(u8 identifier);
extern u8 func_080C8364(struct Object *object);
extern u8 func_080C8348(struct Object *object);

/* 0x0800A36C: 118 bytes, ending at 0x0800A3E2. */
void func_0800A36C(struct Context *context, const u8 *instruction)
{
    struct Object *object = func_08125578(instruction[1]);
    int passed;
    u8 threshold;

    if (object == 0 || object->active == 0)
        return;
    if (func_080C8364(object) || func_080C8348(object))
        return;

    threshold = instruction[2];
    passed = 0;
    if (threshold <= 9) {
        if (object->field_18 >= threshold)
            passed = 1;
    } else {
        if (object->field_18 >= object->field_1A * threshold / 100)
            passed = 1;
    }

    if (passed)
        context->position += instruction[3] | instruction[4] << 8;
}
