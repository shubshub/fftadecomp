#include "ffta.h"

typedef struct Control080812E8 Control080812E8;

struct Control080812E8 {
    void (*callback)(void *context, Control080812E8 *control);
    void *owner;
    u16 x;
    u8 unknown_0A[6];
    u8 flags;
    u8 unknown_11;
    u8 phase;
};

extern const s8 data_08393C72[];
extern const s8 data_08393D02[];

/* Complete target: [0x080812E8, 0x0808136C), 132 bytes.
 * The callback advances either an additive or an absolute horizontal motion
 * table when animation is enabled, then dispatches the active record.
 */
void func_080812E8(void *context, Control080812E8 *control, s32 enabled)
{
    if (!control->callback)
        return;

    if (enabled && (control->flags & 2)) {
        if (!(control->flags & 0x80)) {
            control->x += data_08393C72[control->phase++];
            control->phase %= 48u;
        } else {
            control->x = data_08393D02[control->phase++];
            control->phase %= 40u;
        }
    }
    if (control->flags & 1)
        control->callback(context, control);
}
