typedef unsigned char u8;

typedef struct {
    u8 unknown_0[0xB];
    u8 value;
} TaskState;

extern TaskState *func_08005BFC(void *task);

/* 0x080DADE8: 18 bytes. Set the task state's byte at offset 0xB. */
void func_080DADE8(void *task, u8 value)
{
    TaskState *state = func_08005BFC(task);

    state->value = value;
}
