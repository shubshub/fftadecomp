#include "ffta.h"

// 0x080ED3B8 - 302 bytes: 142 instructions plus the literal pool.
// Target: f0b557464e464546e0b483b0061cea21490070180068ecf7cdfa8246a3225200b1180b78
//         99464846043008702f4831180a789046404602300870a4235b00f1180888050ac0225200
//         80180880281c1af721fb041c281c1af71dfb2404e4140004001524186846211c0022a023
//         f3f7f0f8002548461af70efb00040014a909053108410004040c49464d31e80840180006
//         000e814640461af7fdfa000442460132290989180906090e884669464015098840180004
//         070c6846f3f7ecf82104091438040014091809040c0c6900b01d401802880023c05e0b1c
//         00280edd01202840002805d020040014801a04e0470100002004001480180004040c5046
//         191820040014b28880180880a62149007018006818180780681c0004050c9f2da9d903b0
//         38bc9846a146aa46f0bc01bc0047

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u8 unknown_00[4];
    s16 base;
    s16 offsets[160];
    u8 phase_a;
    u8 phase_b;
    u16 phase_c;
    u8 unknown_14A[2];
    u16 *samples;
    u8 unknown_150[0x84];
    void *scanline_task;
} Wave080ED3B8;

extern s32 func_08007A4C(u8 angle);
extern u16 *func_080D996C(void *task);
extern void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(InterpolationState *state);

void func_080ED3B8(Wave080ED3B8 *wave)
{
    InterpolationState interpolation;
    u16 *buffer;
    u8 phase_a;
    u8 phase_b;
    u8 angle;
    s16 start;
    s16 x;
    s16 sample;
    u16 i;

    buffer = func_080D996C(wave->scanline_task);
    phase_a = wave->phase_a;
    wave->phase_a = phase_a + 4;
    phase_b = wave->phase_b;
    wave->phase_b = phase_b + 2;
    angle = wave->phase_c >> 8;
    wave->phase_c += 0x180;
    start = ((s16)func_08007A4C(angle) >> 3) + ((s16)func_08007A4C(angle) >> 4);
    func_080E0608(&interpolation, start, 0, 160);

    for (i = 0; i < 160; i++) {
        x = (s16)func_08007A4C(phase_a) >> ((i >> 6) + 5);
        phase_a += (i >> 3) + 0x4D;
        sample = (s16)func_08007A4C(phase_b) >> 5;
        phase_b += (i >> 4) + 1;
        sample += interpolation.current;
        func_080E064C(&interpolation);
        x += sample;
        if (wave->offsets[i] > 0) {
            if (i & 1)
                x -= wave->offsets[i];
            else
                x += wave->offsets[i];
        }
        buffer[i] = x + wave->base;
        wave->samples[i] = sample;
    }
}
