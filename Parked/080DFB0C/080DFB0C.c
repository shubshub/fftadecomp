#include "ffta.h"

/* Target 0x080DFB0C, 416 bytes:
 * f0b557464e464546e0b48946151c0988012900d1bae0012902dc002905d0b5e08020400081420dd0b0e048464168087828704888e8804878a870888828818868e860a3e0e888002805d00138e8800004002800d09ae000218a466a7828788446af88624570d2eb68d100c81800888846b84269d81e1cac78881900883b1c984257d10026e86842461118700008188288002a40d089198878002800d0041c094b181c011c1140f0231b02181c0240002a01d0002c2fd0002c06d1081c61f0aafc29e00000ff0f0000002a21d080208001824212d0824204dc80204001824205d019e0c020800182420ed014e0002900d12021201c00f038f90de0002900d12021201c00f00bf906e0201c61f019fd02e0201c61f0a7fc701c0006060e012eb1d90120824668780130687029788c46af880ae0501c0006020e624505d2d100881900888846984296d9781ca880298902200840002804d05246002a01d00020a880687860450bd104200840002803d003204b4618800ae002204946088006e001200840002802d005484a461080002038bc9846a146aa46f0bc02bc084701010000
 */

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct {
    u8 count;
    u8 channel;
    u16 delay;
    u16 flags;
    u16 unknown_06;
    const SequenceEvent *events;
} SequenceParameters;

typedef struct {
    u16 phase;
    u16 unknown_02;
    SequenceParameters *parameters;
} SequenceDescriptor;

typedef struct {
    u8 count;
    u8 cursor;
    u8 channel;
    u8 unknown_03;
    u16 tick;
    u16 delay;
    u16 flags;
    u16 unknown_0a;
    const SequenceEvent *events;
} SequencePayload;

void func_08141520(u16 value);
void func_08141570(u32 mode, u32 value);
void func_080DFE74(u8 channel, u16 duration);
void func_080DFE28(u8 channel, u16 duration);
void func_0814164C(u16 mode);

u32 func_080DFB0C(void *task, void *descriptor_data, void *payload_data)
{
    SequenceDescriptor *descriptor = descriptor_data;
    SequencePayload *payload = payload_data;
    SequenceParameters *parameters;
    u8 scan_index;
    u8 slot;
    u8 channel;
    u8 processed;
    u16 command;
    u16 value;

    switch (descriptor->phase) {
    case 0:
        parameters = descriptor->parameters;
        payload->count = parameters->count;
        payload->delay = parameters->delay;
        payload->channel = parameters->channel;
        payload->flags = parameters->flags;
        payload->events = parameters->events;
        break;
    case 1:
        break;
    case 0x100:
        if (payload->delay != 0) {
            payload->delay--;
            if (payload->delay != 0)
                break;
        }
        processed = 0;
        for (scan_index = payload->cursor;
             scan_index < payload->count &&
             payload->events[scan_index].tick <= payload->tick;
             scan_index++) {
            channel = payload->channel;
            if (payload->events[scan_index].tick == payload->tick) {
                for (slot = 0; slot < 2; slot++) {
                    command = payload->events[scan_index].commands[slot];
                    if (command != 0) {
                        if (payload->events[scan_index].channels[slot] != 0)
                            channel = payload->events[scan_index].channels[slot];
                        value = command & 0x0fff;
                        command &= 0xf000;
                        if (command == 0 || channel != 0) {
                            if (channel == 0) {
                                func_08141520(value);
                            } else {
                                switch (command) {
                                case 0x1000:
                                    func_080DFE74(channel, value ? value : 0x20);
                                    break;
                                case 0x2000:
                                    func_080DFE28(channel, value ? value : 0x20);
                                    break;
                                case 0x3000:
                                    func_0814164C(channel);
                                    break;
                                case 0:
                                    func_08141570(channel, value);
                                    break;
                                }
                            }
                        }
                    }
                }
                processed = 1;
                payload->cursor++;
                break;
            }
        }
        payload->tick++;
        if ((payload->flags & 2) && processed)
            payload->tick = 0;
        if (payload->cursor == payload->count) {
            if (payload->flags & 4)
                descriptor->phase = 3;
            else
                descriptor->phase = 2;
        } else if (payload->flags & 1) {
            descriptor->phase = 0x101;
        }
        break;
    }
    return 0;
}
