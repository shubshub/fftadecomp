#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    u8 finished;
    u8 unknown_09[0x16FB];
} TaskContext;

void *func_08022840(u32 byte_count);
void func_08022854(void *object);
void func_08005A24(void *manager);
void func_08005B18(void *manager);
void *func_08005C14(void *storage, u32 byte_count);
void func_08005C34(void *manager);

void func_08064EF8(u32 unused, u8 *phase)
{
    TaskContext **context_slot;

    switch (*phase) {
    case 0: {
        TaskContext *context = func_08022840(0x3800);

        context_slot = (TaskContext **)0x0200F454;
        *context_slot = context;
        ((void (*)(void *, u32))*(u32 *)0x0836D4B8)(context, sizeof(*context));
        (*context_slot)->allocation = context;
        (*context_slot)->manager = func_08005C14(context + 1, 0x20FC);
        *phase = 1;
        break;
    }
    case 0xFF:
        context_slot = (TaskContext **)0x0200F454;
        if (*context_slot != 0) {
            void *allocation = (*context_slot)->allocation;

            func_08005A24((*context_slot)->manager);
            func_08005B18((*context_slot)->manager);
            func_08005C34((*context_slot)->manager);
            func_08022854(allocation);
            *context_slot = 0;
            *phase = 2;
        }
        break;
    case 1:
        if ((*(TaskContext **)0x0200F454)->finished != 0)
            *phase = 0xFF;
        break;
    }
}
