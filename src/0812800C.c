#include "ffta.h"

/* Complete [0x0812800C, 0x0812803C), 48 bytes.
 * Target: 10b587b01b061b0e002484710190029168468282c38205486c216a460023f9f7affd07b010bc01bc004700000d7d1208 */
typedef struct {
    u8 unknown_00[6];
    u8 active;
} Object0812800C;

typedef struct {
    u32 unknown_00;
    Object0812800C *object;
    void *context;
    u32 unknown_0C[2];
    u16 first;
    u16 second;
    u32 unknown_18;
} Request0812800C;

extern int func_08127D0C(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *), u16,
    const Request0812800C *, void *);

void func_0812800C(Object0812800C *object, void *context, u16 first, u8 second)
{
    Request0812800C request;

    object->active = 0;
    request.object = object;
    request.context = context;
    request.first = first;
    request.second = second;
    func_08121B8C(func_08127D0C, 0x6C, &request, 0);
}
