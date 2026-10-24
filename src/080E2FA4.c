#include "ffta.h"

/* Target 0x080E2FA4, 230 bytes:
70b584b0061c0d1c141c298880204000814215d0814204dc00290bd001290cd05ce00348814217d00130814248d055e001010000a868606050e0f0f769fc4de004480221321cf4f741fd60612888013043e00000f85e39086069f4f75dfd606100283bd16068a21c211cf8f7dbfe0021605e0222a15e03220092221c183201920d4a0292039600220123f3f733f860620a480096012104220023fcf7a5fee0626068009602210c220023f8f761fda0622888013011e00000105f3908585f3908606af3f765f86062002807d1a06af8f7f3fca062002801d102202880002004b070bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[6];
    void *object;
} Descriptor080E2FA4;

typedef struct {
    s16 x;
    s16 y;
    void *object;
    u8 unknown_08[12];
    void *setup_child;
    u8 unknown_18[12];
    void *coordinate_child;
    void *object_child;
    void *record_child;
} Work080E2FA4;

extern void func_080D38B4(void);
extern void *func_080D7A70(const void *records, u8 count, void *parent);
extern void *func_080D7ABC(void *task);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                         void *buffer, const void *records, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void *func_080DBB14(void *object, u8 first, u8 second, u16 value,
                         void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080E2FA4(void *task, void *descriptor_data, void *work_data)
{
    Descriptor080E2FA4 *descriptor = descriptor_data;
    Work080E2FA4 *work = work_data;

    switch (descriptor->phase) {
    case 0:
        work->object = descriptor->object;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->setup_child = func_080D7A70((const void *)0x08395EF8, 2, task);
        descriptor->phase++;
        break;
    case 0x101:
        work->setup_child = func_080D7ABC(work->setup_child);
        if (work->setup_child != 0)
            break;
        func_080DBDC8(work->object, &work->x, &work->y);
        work->coordinate_child = func_080D6098(work->x, work->y, 0, 1, 3,
                                             work->unknown_18,
                                             (const void *)0x08395F10, task);
        work->record_child = func_080DFD8C((const void *)0x08395F58, 1, 4, 0, task);
        work->object_child = func_080DBB14(work->object, 2, 12, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (work->coordinate_child != 0)
            break;
        work->object_child = func_080DBA5C(work->object_child);
        if (work->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
