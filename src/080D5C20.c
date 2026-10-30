#include "ffta.h"

typedef struct {
    s16 state;
} TaskRecord080D5C20;

extern u32 func_08005C00(const void *object);
extern void *func_08005BFC(void *task);
extern u16 func_08005BAC(const void *object);
extern void func_08005BA8(void *object, u16 value);

/* Address comparisons only. These declarations follow the task dispatcher's
 * expected callback type; this function does not invoke the callbacks. */
extern u32 func_080D5128(void *task, void *descriptor, void *payload);
extern u32 func_080D5594(void *task, void *descriptor, void *payload);
extern u32 func_080D5A60(void *task, void *descriptor, void *payload);

static inline u8 task_ready_080D5C20(void *task)
{
    u32 callback = func_08005C00(task);

    if (callback == (u32)func_080D5128) {
        TaskRecord080D5C20 *record = func_08005BFC(task);
        if (record->state == 1)
            return 1;
    } else if (callback == (u32)func_080D5594) {
        TaskRecord080D5C20 *record = func_08005BFC(task);
        if (record->state == 1)
            return 1;
    } else if (callback == (u32)func_080D5A60) {
        if (func_08005BAC(task) == 0x102)
            return 1;
    }
    return 0;
}

/* Complete [0x080D5C20, 0x080D5CC0): 160 bytes.
 * f0b5051c2ff7ecff041c084fbc4202d0074eb4420ed1281c2ff7e0ff011c0022885e012830d10220088033e029510d0895550d08064884422cd1281c2ff7d0ffb84207d1281c2ff7c9ff0021405e08e0615a0d08b04208d1281c2ff7bfff0022805e01280dd101200ce0a04209d1281c2ff78cff000481214904884201d1012000e00020002801d1002004e00349281c2ff77aff0120f0bc02bc084703010000
 */
u32 func_080D5C20(void *task)
{
    u32 callback = func_08005C00(task);

    if (callback == (u32)func_080D5128 || callback == (u32)func_080D5594) {
        TaskRecord080D5C20 *record = func_08005BFC(task);
        if (record->state != 1)
            return 0;
        record->state = 2;
    } else if (callback == (u32)func_080D5A60) {
        if (!task_ready_080D5C20(task))
            return 0;
        func_08005BA8(task, 0x103);
    }
    return 1;
}
