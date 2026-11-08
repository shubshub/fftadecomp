/* 0x080F1DEC: 52 target bytes, including the two table literals.
 * 00b587b0131c0006000e0191074a810089180a680649400040180188101c6a4613f7aefe
 * 07b002bc084700009ca53908bca53908
 */
#include "ffta.h"

typedef struct SchedulerDescriptor080F1DEC {
    u16 phase;
    u16 unknown_02;
    void *owner;
    u8 unknown_08[12];
    u16 unknown_14;
    u8 unknown_16[6];
} SchedulerDescriptor080F1DEC;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern TaskCallback const data_0839A59C[];
extern const u16 data_0839A5BC[];
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080F1DEC(u8 index, void *owner, void *parent)
{
    SchedulerDescriptor080F1DEC descriptor;

    descriptor.owner = owner;
    return func_08005B6C(data_0839A59C[index], data_0839A5BC[index],
                         &descriptor, parent);
}
