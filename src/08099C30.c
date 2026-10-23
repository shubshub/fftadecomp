#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *field_08;
} Object08099C30;

void *func_08099C30(const Object08099C30 *object)
{
    return object->field_08;
}
