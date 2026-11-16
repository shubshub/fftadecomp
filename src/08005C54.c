#include "ffta.h"

/* Target: complete [0x08005C54, 0x08005E7A), 550 bytes, 272 instructions,
 * including the literal word at 0x08005D70 (data_0836D490).
 * f0b557464e464546e0b481b084460c1c65460c352179607900020843a1790904
 * 0143e079000608436968401800902178607800020843a17809040143e0780706
 * 0f430026a07af021014010293ad0102905dc00290ad0182060448246c7e02029
 * 00d18ce0182161448a46c0e018226244924663469b889e4200d3b8e0207a617a
 * 090263469a8901438a4200d3afe06046816889192888381800780870701c0004
 * 060c288801302880614689888e4200d39de0227a617a09020004000c11438842
 * e5d394e018226244924663469b889e4200d38ce0207a617a090263469a890143
 * 8a4200d383e0072081460c49884662469068801900210170a868c1084b461840
 * 79184044097802780a40002a08d0604681688919e07a0001087005e090d43608
 * 6146886880190270a8680130a860c1084a461040791840440978007808400028
 * 08d063469a689219e17a0f200840117808431070a8680130a860c3082b80701c
 * 0004060c60468088864240d2227a617a09021804000c11438842b8d337e01821
 * 61448a4662469288964230d2207a617a090263469a8901438a4228d2a9684a08
 * 01200140002903d0b8180078020903e0b81800780f220240604681688919e07a
 * 000102430a70a8680130a86043082b80701c0004060c614689888e4207d2227a
 * 617a09021804000c11438842d6d362469168b3085046009afaf746fe68688019
 * 68600023227a607a000229881043814200d30123181c01b038bc9846a146aa46
 * f0bc02bc0847
 */

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct __attribute__((packed)) {
    u32 source;
    u32 destination;
    u16 size;
} TransferDescriptor;

typedef struct __attribute__((packed)) TransferEntry {
    TransferDescriptor descriptor;
    u8 kind;
    u8 value;
} TransferEntry;

typedef struct TransferProgress {
    u16 consumed;
    u8 unknown_02[2];
    u32 offset;
    u32 cursor;
} TransferProgress;

typedef struct TransferPayload {
    u16 count;
    u16 current;
    u16 limit;
    u8 unknown_06[2];
    u8 *buffer;
    TransferProgress progress;
    TransferRecord request;
    TransferEntry entries[0];
} TransferPayload;

extern const u8 data_0836D490[];

void func_08000ADC(TransferRecord *entry, const void *source, void *destination, u16 words);

u8 func_08005C54(TransferPayload *state, const TransferEntry *entry)
{
    TransferProgress *progress = &state->progress;
    u8 *destination = (u8 *)entry->descriptor.destination + progress->offset;
    const u8 *source = (const u8 *)entry->descriptor.source;
    u16 produced = 0;

    switch (entry->kind & 0xF0) {
    case 0:
        while (produced < state->limit && progress->consumed < entry->descriptor.size) {
            state->buffer[produced] = source[progress->consumed];
            produced++;
            progress->consumed++;
        }
        break;
    case 0x10:
        while (produced < state->limit && progress->consumed < entry->descriptor.size) {
            u32 byte_index;
            u32 bit_index;

            state->buffer[produced] = 0;
            byte_index = progress->cursor >> 3;
            bit_index = progress->cursor & 7;
            if (source[byte_index] & data_0836D490[bit_index])
                state->buffer[produced] = entry->value << 4;
            else
                state->buffer[produced] = 0;
            progress->cursor++;
            byte_index = progress->cursor >> 3;
            bit_index = progress->cursor & 7;
            if (source[byte_index] & data_0836D490[bit_index])
                state->buffer[produced] |= entry->value & 0xF;
            progress->cursor++;
            progress->consumed = progress->cursor >> 3;
            produced++;
        }
        break;
    case 0x20:
        while (produced < state->limit && progress->consumed < entry->descriptor.size) {
            u32 byte_index = progress->cursor >> 1;
            u8 nibble;

            if (progress->cursor & 1)
                nibble = source[byte_index] >> 4;
            else
                nibble = source[byte_index] & 0xF;
            state->buffer[produced] = (entry->value << 4) | nibble;
            progress->cursor++;
            progress->consumed = progress->cursor >> 1;
            produced++;
        }
        break;
    }
    func_08000ADC(&state->request, state->buffer, destination, produced >> 2);
    progress->offset += produced;
    return progress->consumed >= entry->descriptor.size;
}
