/* 0x08021DE0 - 4 bytes
 * Target: 0088 7047
 */
#include "ffta.h"

typedef struct {
    u16 flags;
} Struct08021DE0;

u16 func_08021DE0(const Struct08021DE0 *object)
{
    return object->flags;
}
