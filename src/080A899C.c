#include "ffta.h"

/* 0x080A899C..0x080A89D8: 60 bytes / 23 instructions. */
typedef struct {
    u8 unknown_00[12];
} ListEntry080A899C;

typedef struct {
    ListEntry080A899C entries[16];
    u8 unknown_c0;
    u8 count;
    u8 unknown_c2[0x4a];
} OutputList080A899C;

typedef struct GroupList080A899C GroupList080A899C;
typedef void (*BufferInitializer080A899C)(void *, u32);

extern OutputList080A899C data_0200F8C0;
extern BufferInitializer080A899C const g_callbacks_0836D4B8[];
extern void func_080A7A80(GroupList080A899C *, OutputList080A899C *);

OutputList080A899C *func_080A899C(GroupList080A899C *source)
{
    g_callbacks_0836D4B8[0](&data_0200F8C0, sizeof(data_0200F8C0));
    func_080A7A80(source, &data_0200F8C0);
    if (!data_0200F8C0.count)
        return 0;
    return &data_0200F8C0;
}
