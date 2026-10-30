#include "ffta.h"

typedef struct {
    s16 state;
} TaskRecord;

extern u32 func_08005C00(const void *object);
extern void *func_08005BFC(void *task);
extern u16 func_08005BAC(const void *object);
extern void func_080D5128(void *task);
extern void func_080D5594(void *task);
extern void func_080D5A60(void *task);

/* Complete target: [0x080D6478, 0x080D64CC), 84 bytes.
 * 10b5041c2ff7c0fb011c0748814202d0064881420cd1201c2ff7b4fb0021405e02280fdd01200ee029510d0895550d080648814206d1201c2ff77cfb000404498842efd8002010bc02bc0847615a0d0800000301
 */
u32 func_080D6478(void *task)
{
    u32 callback = func_08005C00(task);

    if (callback == (u32)func_080D5128 || callback == (u32)func_080D5594) {
        TaskRecord *record = func_08005BFC(task);
        if (record->state > 2) {
            return 1;
        }
    } else if (callback == (u32)func_080D5A60) {
        if (func_08005BAC(task) > 0x103) {
            return 1;
        }
    }
    return 0;
}
