/* 0x080F2E40: complete 56-byte caller, including both table literals.
 * 00b587b0131c0006000e6a4690820191074a810089180a680649400040180188101c6a46
 * 12f782fe07b002bc08470000e8a8390810a93908
 */
#include "ffta.h"

typedef struct SchedulerDescriptor080F2E40 {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[12];
    u16 kind;
    u8 unknown_16[6];
} SchedulerDescriptor080F2E40;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern TaskCallback const data_0839A8E8[];
extern const u16 data_0839A910[];

void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080F2E40(u8 kind, void *value, void *parent)
{
    SchedulerDescriptor080F2E40 descriptor;

    descriptor.kind = kind;
    descriptor.value = value;
    return func_08005B6C(data_0839A8E8[kind], data_0839A910[kind],
                         &descriptor, parent);
}
