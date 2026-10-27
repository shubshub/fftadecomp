#include "ffta.h"

/* 0x0802B6A0..0x0802B6F0: 80 bytes. */
typedef struct {
    void *manager;
    void *allocation;
    void *first_task;
    void *second_task;
} TaskContext;

extern TaskContext *data_0200F440;
extern void func_08005A24(void *manager);
extern void func_080058A4(void *manager, void *task);
extern void func_08005C34(void *manager);
extern void func_08022854(void *allocation);

void func_0802B6A0(void)
{
    TaskContext **context = &data_0200F440;

    if (*context != 0) {
        void *allocation = (*context)->allocation;

        func_08005A24((*context)->manager);
        if ((*context)->first_task != 0)
            func_080058A4((*context)->manager, (*context)->first_task);
        if ((*context)->second_task != 0)
            func_080058A4((*context)->manager, (*context)->second_task);
        func_08005C34((*context)->manager);
        (*context)->manager = 0;
        func_08022854(allocation);
        *context = 0;
    }
}
