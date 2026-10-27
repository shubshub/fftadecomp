#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    void *allocation;
} ReleaseState;

extern void *data_02009168;
extern ReleaseState data_02009170;
extern void func_08007170(void *allocator, void *allocation);

/* 08011614..08011634: 32 bytes. */
void func_08011614(void)
{
    void *allocator = data_02009168;
    ReleaseState *state = &data_02009170;

    func_08007170(allocator, state->allocation);
    state->allocation = 0;
}
