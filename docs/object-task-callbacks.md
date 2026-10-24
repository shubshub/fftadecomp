# Object task callbacks

These recovered callbacks use the scheduler's three-pointer interface:
task, descriptor, and payload, with a zero `u32` result. The task argument is
unused in both bodies. Local type names describe observed layouts; they do
not recover the original public typedefs. Direct-call verification assumes
returning ABI-compliant callees, not transitive engine or object-lifetime proofs.

## 080DEBAC: cycling an object's signed-byte value

Constructor `080DF7A0` registers Thumb pointer `080DEBAD` through scheduler
`08005B6C` with a 16-byte payload. The complete function occupies
`[080DEBAC,080DEC84)`: 216 bytes and 105 reached instructions, without pools.

State zero captures the object, interval, direction, repeat count and initial
signed-byte value, and narrows delay-plus-one to `u16`. State `0x100` counts
down delay and interval, updates the value, dispatches an action, and counts
finite repeats. Signed repeat `-1` means indefinite repetition. Forward
stepping wraps exactly 3 to 0; reverse stepping wraps exactly 0 to 3. Values
outside that range are not normalized by general modulo-four arithmetic.

Payload action at `+0xC` is **not initialized** by this callback or the inspected
constructor. Its validity is an external precondition; no zero initialization
was invented. `080DBC88` returns a sign-extended object byte, but that does not
uniquely establish the original public return typedef. Thirteen native
sanitizer cases and sixteen ILP32 layout assertions support this recovery;
they do not prove allocator initialization or exhaustive gameplay behavior.

## 080DF080: flagged actions and completion waits

Constructor `080DF9E4` registers Thumb pointer `080DF081` through scheduler
`08005B6C` with an eight-byte payload. The complete function occupies
`[080DF080,080DF14C)`: 204 bytes and 95 reached instructions, without pools.

Only a nonzero-to-zero delay transition in state `0x100` triggers flag-2/4
actions. An initially zero or wrapped delay skips them. Completion falls
through into state-`0x101` logic without storing `0x101`; a newly assigned
delay of 16 can therefore become 15 in the same invocation. Flags are reloaded
after calls, preserving possible callee changes. Twenty-three native cases
check these state, countdown, flag and call-order behaviors with stubbed
helpers. Native pointer layouts are not ARM layout proof; complete target
byte equality supplies the separate target-code evidence.
