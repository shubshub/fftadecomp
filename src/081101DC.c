#include "control_flags.h"
/* Target bytes: f0b581b0061c0f1c151c3c88012c7ad0012c02dc002c05d075e080204000844254d070e02548311cc3f74afe2860782050210022331ccaf7bffda860204a111c423108783f200870131c433319781870111c443108781f200870093908780c70013908780c70053108780c700139ff200870013908780c70101c3c3001780470111c413108780c70013908780120404208701188c023db01181c0843108009480096012104220023cff782fde8600648311cc4f739fa686025e000007cd9940840090003f82e3a08c8a994082868c3f72dfe2860002816d16868c4f75dfa6860002810d1a868caf7bffda86000280ad107490a8807481040002208804a3108780a7002203880002001b0f0bc02bc084740090003ff9f0000 */
typedef struct { u16 phase; } Command;
typedef struct { void *script; void *effect; void *window; void *sequence; } Payload;
extern const u8 data_0894D97C[];
extern const u8 data_083A2EF8[];
extern const u8 data_0894A9C8[];
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DAD94(int, int, int, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DAE44(void *);
u32 func_081101DC(void *task, Command *command, Payload *payload)
{
    switch (command->phase) {
    case 0:
        payload->script = func_080D3E9C(data_0894D97C, task);
        payload->window = func_080DAD94(120, 80, 0, task);
        g_control_flags_03000940.winin_lo = 63;
        g_control_flags_03000940.winin_hi = 63;
        g_control_flags_03000940.winout_lo = 31;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 255;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 255;
        g_control_flags_03000940.display |= 0x6000;
        payload->sequence = func_080DFD8C(data_083A2EF8, 1, 4, 0, task);
        payload->effect = func_080D4704(data_0894A9C8, task);
        break;
    case 1:
        break;
    case 0x100:
        payload->script = func_080D3F08(payload->script);
        if (payload->script) break;
        payload->effect = func_080D4774(payload->effect);
        if (payload->effect) break;
        payload->window = func_080DAE44(payload->window);
        if (payload->window) break;
        g_control_flags_03000940.display &= 0x9fff;
        g_control_flags_03000940.bldcnt_lo = 0;
        command->phase = 2;
        break;
    }
    return 0;
}
