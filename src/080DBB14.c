#include "ffta.h"

typedef struct {
    void *unknown_00;
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
} Payload080DBB14A;

typedef struct {
    s16 unknown_00;
    s16 unknown_02;
    s16 unknown_04;
    u16 unknown_06;
} Payload080DBB14B;

typedef struct {
    u16 unknown_00;
    u16 unknown_2;
    const Payload080DBB14A *payload_a;
    const Payload080DBB14B *payload_b;
    u32 unknown_C[4];
} Task080DBB14;

typedef u32 (*TaskCallback)(void *, void *, void *);
extern u32 func_080DAE7C(void *task, void *control, void *state);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

/* Complete [0x080DBB14, 0x080DBB74): 96 bytes including literal pool.
 * 70b58bb00f9e0906090e12060790104c07ad686820400843120c0e4908401043
 * 0d4a1040686009981043ff390843099009a81b041343436001950290074814216a46
 * 331c2af708f80bb070bc02bc084700ffffffff00ffffffff00007dae0d08
 */
void *func_080DBB14(void *value, u8 arg1, u8 arg2, u16 arg3, void *parent)
{
    Task080DBB14 request;
    Payload080DBB14A payload_a;
    Payload080DBB14B payload_b;

    payload_a.unknown_00 = value;
    payload_a.unknown_04 = arg1;
    payload_a.unknown_05 = arg2;
    payload_a.unknown_06 = 0;
    payload_b.unknown_00 = -1;
    payload_b.unknown_02 = -1;
    payload_b.unknown_04 = -1;
    payload_b.unknown_06 = arg3;
    request.payload_a = &payload_a;
    request.payload_b = &payload_b;
    return func_08005B6C(func_080DAE7C, 0x14, &request, parent);
}
