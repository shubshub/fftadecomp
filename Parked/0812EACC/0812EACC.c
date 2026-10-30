#include "ffta.h"

/* Complete target: [0x0812EACC, 0x0812EB4C), 128 bytes.
 * f0b557464e464546e0b483b00b9c0c9dac461204120cf6263618b04635780095
 * f7263618b14635780195f6267618b24635780f1cf7373e780296464633704b46
 * 1c706646544626700dab1b783b70fff793ff0004000c6c462678444626706946
 * 0a7949460a7053461d706c46247a3c7003b038bc9846a146aa46f0bc02bc0847
 */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 unknown_F8[5];
    u8 movement;
} Unit0812EACC;

extern u16 func_0812EA44(const Unit0812EACC *source,
                         const Unit0812EACC *target, u16 identifier);

u16 func_0812EACC(Unit0812EACC *source, Unit0812EACC *target,
                  u16 identifier, u8 source_x, u8 source_y,
                  u8 target_x, u8 target_y)
{
    u8 original_source_x = source->x;
    u8 original_source_y = source->y;
    u8 original_target_x = target->x;
    u8 original_target_y = target->y;
    u16 result;

    source->x = source_x;
    source->y = source_y;
    target->x = target_x;
    target->y = target_y;
    result = func_0812EA44(source, target, identifier);
    source->x = original_source_x;
    source->y = original_source_y;
    target->x = original_target_x;
    target->y = original_target_y;
    return result;
}
