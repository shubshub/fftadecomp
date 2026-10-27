#include "ffta.h"

typedef struct SceneObject SceneObject;

typedef struct {
    s16 selector;
    u16 duration;
    SceneObject *object;
    void *argument;
} TaskParameters;

typedef struct {
    u16 phase;
    u16 unknown_02;
    TaskParameters *parameters;
} TaskCommand;

typedef struct {
    u8 unknown_00[6];
    u16 duration;
    u8 unknown_08[2];
} OperationScript;

typedef struct {
    u16 unknown_00;
    s16 selector;
    SceneObject *object;
    void *argument;
    void *operation;
    OperationScript script;
} TaskRuntime;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);
extern BufferCopier const data_0836D4BC[];
extern const u8 data_08395618[10];
extern void *func_080D3E9C(const void *script, void *context);
extern void *func_080D3F08(void *operation);
extern void func_080DD7B0(SceneObject *object, u8 value, u8 include_second);
extern void func_080DD808(u8 selector, u8 value, u8 include_second,
                          SceneObject *skip, void *argument);
extern void func_080DBEB4(SceneObject *object, u8 value);
extern void func_080DBED4(u8 selector, u8 value, SceneObject *skip,
                          void *argument);

/* 0x080DEF90..0x080DF080: 240 bytes; run a timed object visibility task. */
u32 func_080DEF90(void *context, TaskCommand *command, TaskRuntime *runtime)
{
    switch (command->phase) {
    case 0: {
        TaskParameters *parameters = command->parameters;

        runtime->selector = parameters->selector;
        runtime->object = parameters->object;
        runtime->argument = parameters->argument;
        data_0836D4BC[0](&runtime->script, data_08395618,
                         sizeof(data_08395618));
        runtime->script.duration = parameters->duration;
        break;
    }
    case 1:
        break;
    case 0x100:
        runtime->operation = func_080D3E9C(&runtime->script, context);
        if (runtime->selector == -1)
            func_080DD7B0(runtime->object, 1, 1);
        else
            func_080DD808(runtime->selector, 1, 1, runtime->object,
                          runtime->argument);
        command->phase++;
        break;
    case 0x101:
        runtime->operation = func_080D3F08(runtime->operation);
        if (runtime->operation != 0)
            break;
        if (runtime->selector == -1) {
            func_080DBEB4(runtime->object, 0);
            func_080DD7B0(runtime->object, 0, 1);
        } else {
            func_080DBED4(runtime->selector, 0, runtime->object,
                          runtime->argument);
            func_080DD808(runtime->selector, 0, 1, runtime->object,
                          runtime->argument);
        }
        command->phase = 2;
        break;
    }
    return 0;
}
