#include "ffta.h"

/* 0x08122404..0x08122452: 78 bytes. */
typedef struct {
    s16 unknown_00;
    s16 id;
} TaskInfo;

extern void *func_08005BFC(void *);
extern void *func_08121D0C(s32);
extern void func_08121D20(s32, void *);

int func_08122404(void *task)
{
    TaskInfo *info = func_08005BFC(task);
    int i;

    for (i = 0; i < 16; ++i) {
        void *entry = func_08121D0C(i);

        if (entry != 0) {
            if (info->id != 0xFF && info->id != 0x80) {
                TaskInfo *other = func_08005BFC(entry);
                if (info->id == other->id)
                    return 0;
            }
        } else {
            func_08121D20(i, task);
            return 1;
        }
    }
    return 0;
}
