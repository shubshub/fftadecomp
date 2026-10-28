typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    u8 unknown_0[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080D9F60(s16 x, s16 y, u16 value, void *context, u8 option);

/* 0x080DAC40: 64 bytes. Draw through the task's object context. */
void func_080DAC40(void *task, u16 x, u16 y, u16 value)
{
    DrawingState *state = func_08005BFC(task);
    void *context = func_0800C614(state->object);

    func_080D9F60((s16)x, (s16)y, value, context, 0);
}
