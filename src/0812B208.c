/* 0x0812B208, 40 bytes. Start the object task with its request flag. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 busy;
} Object0812B208;

typedef struct {
    u16 state;
    u16 unknown_02;
    Object0812B208 *object;
    u8 unknown_08[12];
    u16 flag;
    u8 unknown_16[6];
} TaskRequest0812B208;

typedef u32 (*TaskCallback0812B208)(void *task, void *request, void *payload);

extern u32 func_0812A084(void *task, void *request, void *payload);
extern void *func_08121B8C(TaskCallback0812B208 callback, u16 payload_size,
                          void *request, void *parent);

void func_0812B208(Object0812B208 *object)
{
    TaskRequest0812B208 request;

    object->busy = 0;
    request.object = object;
    request.flag = 1;
    func_08121B8C(func_0812A084, 0x334, &request, 0);
}
