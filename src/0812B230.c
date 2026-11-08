#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 done;
} Owner0812B230;

/* The actual scheduler copies all 28 bytes. Unknown fields are not initialized
 * by this owner; the callback consumes the owner and variant prefix fields. */
typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Owner0812B230 *owner;
    u8 unknown_08[12];
    u16 variant;
    u8 unknown_16[6];
} Request0812B230;

typedef struct State0812B230 State0812B230;
typedef s32 (*Callback0812B230)(void *, Request0812B230 *, State0812B230 *);

extern s32 func_0812A084(void *, Request0812B230 *, State0812B230 *);
/* Conditional ordinary ABI view from the full helper and callback entries.
 * The immutable scheduler definition instead uses a generic unsigned-word
 * callback; nominal cross-TU source compatibility is not asserted here. */
extern void *func_08121B8C(Callback0812B230, u16, Request0812B230 *, void *);

/* Complete [0x0812B230, 0x0812B258): 40 bytes including final literal. */
void func_0812B230(Owner0812B230 *owner)
{
    Request0812B230 request;

    owner->done = 0;
    request.owner = owner;
    request.variant = 0;
    func_08121B8C(func_0812A084, 0x334, &request, 0);
}
