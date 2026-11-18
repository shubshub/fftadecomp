#include "ffta.h"

typedef struct {
    void *object;
} Value0809ADDC;

extern void func_0812ED58(void *object);

/* Complete target: [0x0809ADDC, 0x0809ADEA), 14 bytes.
 * Target bytes: 00b5006893f0baff012002bc0847
 */
u32 func_0809ADDC(Value0809ADDC *value, void *argument)
{
    func_0812ED58(value->object);
    return 1;
}
