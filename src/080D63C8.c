#include "ffta.h"

/* 0x080D63C8..0x080D6420: 88 bytes, 34 instructions. */
typedef void (*TaskCallback)(void *task);

typedef struct {
    s16 state;
} TaskRecord;

extern TaskCallback func_08005C00(void *task);
extern TaskRecord *func_08005BFC(void *task);
extern u16 func_08005BAC(void *task);
extern void func_080D5128(void *task);
extern void func_080D5594(void *task);
extern void func_080D5A60(void *task);

u32 func_080D63C8(void *task)
{
    TaskCallback callback = func_08005C00(task);

    if (callback == func_080D5128 || callback == func_080D5594) {
        TaskRecord *record = func_08005BFC(task);
        if (record->state == 1) {
            return 1;
        }
    } else if (callback == func_080D5A60) {
        if (func_08005BAC(task) == 0x102) {
            return 1;
        }
    }
    return 0;
}
