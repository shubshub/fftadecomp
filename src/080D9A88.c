typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
    u8 fifth;
    u8 sixth;
    u8 unknown_6[2];
} ObjectEntry;

typedef struct {
    u8 unknown_0[4];
    void *object;
} ObjectState;

extern ObjectState *func_08005BFC(void *task);
extern void func_0800DB0C(void *object, u8 first, u8 second, u8 third,
                         u8 fourth, u8 fifth, u8 sixth);

/* 0x080D9A88: 82 bytes. Apply configuration records to the task's object. */
void func_080D9A88(void *task, const ObjectEntry *entries, u16 count)
{
    ObjectState *state = func_08005BFC(task);
    u16 i;

    for (i = 0; i < count; i++) {
        func_0800DB0C(state->object, entries[i].first, entries[i].second,
            entries[i].third, entries[i].fourth, entries[i].fifth,
            entries[i].sixth);
    }
}
