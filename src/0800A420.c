typedef unsigned char u8;
typedef unsigned short u16;

struct Context {
    u16 unknown_00;
    u16 cursor;
};

struct Actor {
    u8 unknown_000[0x101];
    u8 value;
};

struct Entry {
    struct Actor *actor;
};

struct Root;

extern struct Root *func_08096D7C(void);
extern int func_08099CDC(struct Root *root, struct Entry **entries);
extern u8 func_080C8298(const struct Actor *actor);

/* Complete target span: 0x0800A420-0x0800A490, 112 bytes. */
void func_0800A420(struct Context *context, const u8 *instruction)
{
    struct Entry *entries[13];
    int total = 0;
    int count = func_08099CDC(func_08096D7C(), entries);
    int index;

    for (index = 0; index < count; index++) {
        struct Entry *entry = entries[index];

        if (func_080C8298(entry->actor) == 0)
            total += entry->actor->value;
    }
    if (instruction[1] == total)
        context->cursor += instruction[2] | (instruction[3] << 8);
}
