#include "control_flags.h"

// Target 0x0801CE6C, complete [0x0801CE6C, 0x0801CF10), 164 bytes.
typedef struct {
    u8 active;
    u8 mode;
    u8 unknown_02[6];
    u16 color;
    u8 unknown_0A[6];
    u8 *destination;
    u8 unknown_14[4];
    void *first_request;
    void *second_request;
} State0801CE6C;

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

extern State0801CE6C data_02008168;
extern RequestNode data_02007EB0[];
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08000B68(RequestNode *entry, u32 first, void *second, u16 count);
extern u16 func_080035A8(u8 layer);

void func_0801CE6C(void)
{
    State0801CE6C *state = &data_02008168;
    u32 fill = state->color | (state->color << 16);

    switch (state->mode) {
    case 0:
    {
        u32 word = fill;

        func_08141868(&word, state->destination, 0x01000800);
        func_08000B68(&data_02007EB0[0], fill, state->first_request, 0x200);
        state->mode = 1;
        break;
    }
    case 1:
    {
        u32 word = fill;

        func_08141868(&word, state->destination + 0x2000, 0x01000800);
        func_08000B68(&data_02007EB0[1], fill, state->second_request, 0x200);
        state->mode = 2;
        break;
    }
    case 2:
        g_control_flags_03000940.display |= func_080035A8(1);
        g_control_flags_03000940.display |= func_080035A8(0);
        state->mode = 3;
        break;
    }
}
