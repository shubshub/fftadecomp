#include "ffta.h"

typedef struct {
    u8 *state;
    u32 next_state;
    u32 selection;
} MenuChoice;

typedef struct {
    u8 unknown_0000[0x446C];
    u8 selection;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u16 song_id);

void func_08069548(void *argument)
{
    const MenuChoice *choice = argument;

    func_08141540(0x69);
    *choice->state = choice->next_state;
    data_0200F428->selection = choice->selection;
}
