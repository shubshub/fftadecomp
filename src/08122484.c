#include "ffta.h"

/* 0x08122484..0x081224B8: 52 bytes. */
typedef struct {
    s16 unknown_00;
    s16 id;
} TaskInfo;

extern void *func_08121D0C(s32);
extern void *func_08005BFC(void *);

int func_08122484(u8 id)
{
    int i;

    for (i = 0; i < 16; ++i) {
        void *task = func_08121D0C(i);

        if (task != 0) {
            TaskInfo *info;

            if (id == 0xFF)
                return 1;
            info = func_08005BFC(task);
            if (info->id == id)
                return 1;
        }
    }
    return 0;
}
