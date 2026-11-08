#include "ffta.h"

/* Target 0x080FDAB0..0x080FDB96, complete 230-byte request controller. */
typedef struct TaskRequest {
    u16 command;
    u16 unknown_02;
    void *subject;
    u32 argument_08;
    u32 argument_0C;
    u32 argument_10;
    s16 value;
    u16 flags;
    u32 unknown_18;
} TaskRequest;

typedef struct ControllerState {
    u16 unknown_00;
    u8 kind;
    u8 completion;
    void *unknown_04;
    void *animation;
    void *effect;
    void *subject;
    void *transition;
} ControllerState;

typedef u32 (*TaskCallback)(void *, TaskRequest *, void *);

extern const u8 g_object_0839D798[];
void *func_08005B6C(TaskCallback, u16, TaskRequest *, void *);
void func_080D38B4(void);
void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
void *func_080E051C(void *);
void *func_080E05DC(void *);
u32 func_080E5F50(void *, TaskRequest *, void *);
void *func_080FDE58(void *, u8, u8, u8 *, void *);
void *func_080FDEBC(void *);

u32 func_080FDAB0(void *task, TaskRequest *request, ControllerState *state)
{
    TaskRequest child;

    switch (request->command) {
    case 0: {
        void *subject;
        u8 mode;
        state->kind = request->flags;
        subject = request->subject;
        state->subject = subject;
        mode = 5;
        if (state->kind != 0)
            mode = 0;
        state->transition = func_080E03F8(subject, g_object_0839D798,
                                         mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->transition = func_080E05DC(state->transition);
        if (state->transition == 0) {
            state->animation = func_080FDE58(state->subject, 5, 0,
                                             &state->completion, task);
            if (state->animation != 0)
                request->command++;
            else
                request->command = 2;
        }
        break;
    case 0x101:
        if (state->completion != 0) {
            if (state->completion == 2) {
                request->command = 0x102;
            } else {
                child.value = 0x9E;
                child.flags = 1;
                child.subject = state->subject;
                state->effect = func_08005B6C(func_080E5F50, 0x40,
                                             &child, task);
                request->command++;
            }
        }
        break;
    case 0x102:
        state->animation = func_080FDEBC(state->animation);
        if (state->animation == 0) {
            state->effect = func_080E051C(state->effect);
            if (state->effect == 0)
                request->command = 2;
        }
        break;
    }
    return 0;
}
