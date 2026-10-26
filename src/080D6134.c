typedef unsigned char u8;
typedef unsigned int u32;

extern u32 func_08005BB0(const void *task);
extern void func_08005B58(void *task);

static inline u8 task_finished(const void *task)
{
    if (func_08005BB0(task))
        return 1;
    return 0;
}

/* 0x080D6134: 40 bytes. Destroy a finished task and clear its handle. */
void *func_080D6134(void *task)
{
    void *result;

    if (!task_finished(task)) {
        result = task;
    } else {
        func_08005B58(task);
        result = 0;
    }
    return result;
}
