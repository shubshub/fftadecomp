typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    const void *data;
    u16 length;
    u16 unknown_6;
} QueueEntry;

typedef struct {
    u8 unknown_0[0x26];
    u8 count;
    u8 unknown_27;
    QueueEntry entries[4];
} QueueState;

extern QueueState *func_08005BFC(void *task);

/* 0x080D659C: 56 bytes. Append an entry while the task queue has room. */
void func_080D659C(void *task, const void *data, u16 length)
{
    QueueState *state = func_08005BFC(task);

    if (state->count < 4) {
        state->entries[state->count].data = data;
        state->entries[state->count].length = length;
        state->count++;
    }
}
