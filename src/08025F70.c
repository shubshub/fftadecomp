#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} SceneObject08025F70;

extern void *func_08096D7C(void);
extern SceneObject08025F70 *func_08099560(void *scene, void *record);

/* 0x08025F70 - 28 bytes.
 * Target: 10b5041c70f002ff211c73f0f1fa006bc00b0121084010bc02bc0847
 */
u8 func_08025F70(void *record)
{
    SceneObject08025F70 *object = func_08099560(func_08096D7C(), record);

    return (object->flags >> 15) & 1;
}
