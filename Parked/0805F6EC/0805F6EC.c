#include "ffta.h"

/* 0x0805F6EC..0x0805F708: 28 bytes, 11 instructions.
 * 00b587b06a4604491180c0686946a6f783fa07b001bc004703010000 */

typedef struct Task05F6EC Task05F6EC;

typedef struct {
    u8 unknown_00[0xC];
    Task05F6EC *task;
} Owner05F6EC;

typedef struct Request05F6EC {
    u16 event;
    u16 unknown_02;
    void *object;
    u8 unknown_08[20];
} Request05F6EC;

extern u32 func_08005C04(void *task, void *descriptor);

void func_0805F6EC(Owner05F6EC *owner)
{
    Request05F6EC request;

    request.event = 0x103;
    func_08005C04(owner->task, &request);
}
