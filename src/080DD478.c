#include "ffta.h"

/* 0x080DD478 - 4 bytes. */
typedef struct {
    void *field_00;
} Struct080DD478;

void *func_080DD478(const Struct080DD478 *object)
{
    return object->field_00;
}
