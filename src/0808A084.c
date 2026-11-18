#include "ffta.h"

typedef struct {
    u8 unknown_000[0x987];
    u8 selected_unit;
} MenuState;

extern MenuState *data_03002818;

/* Complete target [0x0808A084, 0x0808A098), 20 bytes. */
u8 func_0808A084(void)
{
    return data_03002818->selected_unit;
}
