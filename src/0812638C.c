typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object12638C {
    u8 unknown_00[6];
    u8 active;
    u8 unknown_07;
    void *parent;
} Object12638C;

typedef struct Payload12638C {
    u32 unknown_00;
    Object12638C *object;
    void *value;
    u32 unknown_0C[4];
} Payload12638C;

extern int func_08125A5C(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Payload12638C *, void *);

void func_0812638C(Object12638C *object, void *value)
{
    Payload12638C payload;

    object->active = 0;
    payload.object = object;
    payload.value = value;
    func_08121B8C(func_08125A5C, 0xB4, &payload, object->parent);
}
