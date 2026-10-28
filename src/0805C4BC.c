/* Target: 100 bytes / 30 instructions, 0x0805C4BC..0x0805C520. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *first;
    u8 *source;
    u16 count;
    u8 unknown_0A[2];
    u16 *data;
    u16 index;
    u16 field_12;
    u16 field_14;
    u8 field_16;
    u8 unknown_17;
    u16 field_18;
} AnimationState;

typedef struct {
    u8 unknown_0000[0x33E8];
    AnimationState animation;
} State;

extern State *data_0200F428;
extern u8 data_084229B8[];
extern u8 data_0841CE9C[];
extern u8 data_08422894[];
extern u8 data_0841CE4C[];
extern void func_0802B3A8(AnimationState *state, void *first, u8 *source,
                           u16 index, u8 value);

void func_0805C4BC(u8 selector, u8 value)
{
    if (selector <= 78) {
        func_0802B3A8(&data_0200F428->animation, data_084229B8,
                       data_0841CE9C, 0, value);
    } else {
        func_0802B3A8(&data_0200F428->animation, data_08422894,
                       data_0841CE4C, 0, value);
    }
}
