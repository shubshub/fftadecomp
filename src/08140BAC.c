#include "ffta.h"

/* Complete target [0x08140BAC, 0x08140EB8): 780 bytes, 323 instructions.
 * Target bytes:
 * f0b5474680b483b0061c09060f0ea020c00034182088012800d195e0012802dc002804d054e1022800d1a5e050e1002f
 * 01d000205be1fff771f93548354c36490368201c202201f02dfb3448344964180368201c8021ff2201f024fb31493248
 * 02698c231b01301cbff640ff2f4b00222f4f351c54351c24a419a4462d48801980462c1ca1181888087001320233ba42
 * f8d9254842691020009006200190202002906046291c0323bff6aaff9e22d200b11800200860204bf018a024e4000460
 * 802040000090019008680002000c02901820402178225023fff796fe174b00204021302207f04cf8154ab1180860154b
 * f118802008803419022222806088411c61800004c00b4044028001202080dfe0bcd43608603a0003408c9908c0d43608
 * 00feffff643f9908b00800035cf299085702000004050000f4040000c08b9908fc040000ee040000301c38300749084a
 * 8023bff6cbfe6088013860800004c00b044ab118091808882080b1e0805098080000010604050000ab239b00f5180024
 * 06e0081c10e078215022fff7bdfe0134012c0bda291c002208680028f1d001322431102af8db00200028ecd10d483418
 * 206800280bd007f037fc002804d0206807f0aefb00202060206800283ad10649741800202056002808d0012800d128e7
 * 30e00000fc040000fa040000002f08d09f22d200b118202008800f4bf118022008709f20c00031180a880023c85e1f28
 * 16dd094970180078012813d9802189000020302206f07efe044ab118086020780130207006e00000ec040000fc040000
 * 501c08802d4bf4180021605e00900022a05e01900233f51828680002000c02901820402178225023fff7cefd20880130
 * 00232080224c32192968106808182860002803da802149004018286029688020400281420ddd1b4c081928601a483118
 * 0878013008700006000e012806d913602b60154970180078012809d8104ab118086805380860ff2802dc802040000860
 * ab239b00f4180f252068002802d0201cfff7c8fd013d2434002df5da012003b008bc9846f0bc02bc08470000ee040000
 * f40400000000ffffec040000
 */

typedef struct TransferRecord08140BAC {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord08140BAC *next;
} TransferRecord08140BAC;

typedef struct ExtendedRequestNode08140BAC {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u8 unknown_16[2];
    struct ExtendedRequestNode08140BAC *next;
} ExtendedRequestNode08140BAC;

typedef struct {
    const u8 *image;
    s32 x;
    s32 y;
    s32 destination_x;
    s32 destination_y;
    s32 unknown_14;
    s32 lifetime;
    s32 speed;
    u16 scale;
    u16 frame;
} Particle08140BAC;

typedef struct {
    u16 current;
    u16 depth;
    u16 stack[34];
} Phases08140BAC;

typedef struct {
    TransferRecord08140BAC transfer;
    ExtendedRequestNode08140BAC request;
    TransferRecord08140BAC sprite_transfer;
    u8 tiles[0x258];
    Particle08140BAC particles[16];
    u8 stage;
    u8 unknown_4ed;
    s16 scale;
    s32 angle;
    s32 speed;
    s16 timer;
    s8 fade;
    u8 unknown_4fb;
    void *effect;
    Phases08140BAC phases;
} State08140BAC;

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u16 *destination;
} Display08140BAC;

typedef void (*BufferCopier08140BAC)(void *destination, const void *source,
                                     u32 size);
typedef void (*BufferFiller08140BAC)(void *destination, u32, u32);

extern const BufferCopier08140BAC data_0836D4BC[];
extern const BufferFiller08140BAC data_0836D4C0[];
/* One palette buffer: the ROM loads 0x03003A60 (row 16) at 0x08140BE8 and
 * reaches 0x03003860 (row 0) by adding -0x200 at 0x08140BFA. */
extern u16 data_03003860[][16];
extern Display08140BAC data_030008B0;
extern u8 data_06010000[];
extern const u16 data_08998C40[];
extern const u8 data_08993F64[];
extern const u16 data_0899F25C[];
extern const u16 data_08998BC0[];
extern const u8 data_08985080[];

extern void func_0813FEC8(void);
extern void func_08000A98(TransferRecord08140BAC *transfer, const void *source,
                          void *destination, u16 size);
extern void func_08000BAC(ExtendedRequestNode08140BAC *request,
                          const void *source, void *destination, u16, u16,
                          u16, u16);
/* The angle argument is narrowed to 16 bits at both calls (lsls #8; lsrs #16
 * at 0x08140C76 and 0x08140E06). */
extern void func_081409B4(s16 texture_x, s16 texture_y, s16 screen_x,
                          s16 screen_y, s16 scale_x, s16 scale_y, u16 angle);
extern void *func_08147D2C(u16 first, u16 count, u16 duration,
                           const u16 *colors);
extern void *func_08147AD0(u16 first, u16 count, u16 duration);
extern u32 func_081485D4(void *effect);
extern void *func_081484CC(void *effect);
extern void func_08140AB4(Particle08140BAC *particle, s16 x, s16 y);
extern void func_08140A20(Particle08140BAC *particle);

/* The text of push_phase in src/080B5278.c.  The ROM repeats this block in
 * func_08140310 (0x08140404) and func_08140EB8 (0x08141164). */
static inline void push_phase(Phases08140BAC *phases)
{
    phases->stack[phases->depth++] = phases->current;
}

/* Pops what push_phase pushed, the operation of pop_option in
 * src/080BD1EC.c.  The ROM repeats this block in func_08140310 (0x08140482)
 * and func_08140EB8 (0x0814123A). */
static inline void pop_phase(Phases08140BAC *phases)
{
    phases->current = phases->stack[--phases->depth];
}

/* The ROM compares the counter with the count itself, cmp r2, #0x10; blt at
 * 0x08140D4E; a literal bound of 16 compiles to cmp #0xF; ble. */
static inline Particle08140BAC *find_free_particle(Particle08140BAC *particle,
                                                   s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, particle++)
        if (particle->image == 0)
            return particle;
    return 0;
}

/* Called with a count of 1; the ROM keeps the loop: counter r4 = 0 at
 * 0x08140D2A, incremented at 0x08140D3A, cmp r4, #1; bge at 0x08140D3C (a
 * literal bound of 1 compiles to cmp #0; bgt) and the back branch bne at
 * 0x08140D56. */
static inline void spawn_particles(Particle08140BAC *particles, s32 count)
{
    Particle08140BAC *particle;
    s32 n;

    for (n = 0; n < count; n++) {
        particle = find_free_particle(particles, 16);
        if (particle == 0)
            break;
        func_08140AB4(particle, 0x78, 0x50);
    }
}

u32 func_08140BAC(State08140BAC *state, u8 skip)
{
    u32 i;
    const u16 *source;
    s32 n;
    Particle08140BAC *particle;

    switch (state->phases.current) {
    case 0:
        if (skip)
            return 0;
        func_0813FEC8();
        data_0836D4BC[0](data_03003860[16], data_08998C40, 0x20);
        data_0836D4C0[0](data_03003860[0], 0x80, 0xFF);
        func_08000A98(&state->transfer, data_08993F64, data_030008B0.tiles,
                      0x8C0);
        source = data_0899F25C;
        for (i = 0; i < 0x258; i++, source++)
            state->tiles[i] = *source;
        func_08000BAC(&state->request, state->tiles,
                      data_030008B0.destination, 3, 0x10, 6, 0x20);
        state->angle = 0;
        state->speed = 0x500;
        func_081409B4(0x18, 0x40, 0x78, 0x50, 0x100, 0x100,
                      state->angle >> 8);
        state->effect = func_08147D2C(0, 0x40, 0x30, data_08998BC0);
        state->scale = 0x80;
        state->phases.current = 2;
        push_phase(&state->phases);
        state->phases.current = 1;
        break;
    case 1:
        func_08000A98(&state->sprite_transfer, data_08985080, data_06010000,
                      0x80);
        pop_phase(&state->phases);
        break;
    case 2:
        spawn_particles(state->particles, 1);
        if (state->effect != 0 && func_081485D4(state->effect) != 0) {
            func_081484CC(state->effect);
            state->effect = 0;
        }
        if (state->effect == 0) {
            switch (state->fade) {
            case 0:
                if (skip) {
                    state->timer = 0x20;
                    state->stage = 2;
                }
                if (state->timer < 0x20) {
                    state->timer++;
                } else if (state->stage > 1) {
                    state->effect = func_08147AD0(0, 0x200, 0x30);
                    state->fade++;
                }
                break;
            case 1:
                return 0;
            }
        }
        func_081409B4(0x18, 0x40, 0x78, 0x50, state->scale, state->scale,
                      state->angle >> 8);
        state->scale++;
        state->angle += state->speed;
        if (state->angle < 0)
            state->angle += 0x100;
        if (state->angle > 0x10000) {
            state->angle -= 0x10000;
            state->stage++;
            if (state->stage > 1) {
                state->speed = 0;
                state->angle = 0;
            }
        }
        if (state->stage <= 1) {
            state->speed -= 5;
            if (state->speed < 0x100)
                state->speed = 0x100;
        }
        break;
    }

    particle = state->particles;
    for (n = 0; n < 16; n++, particle++)
        if (particle->image != 0)
            func_08140A20(particle);
    return 1;
}
