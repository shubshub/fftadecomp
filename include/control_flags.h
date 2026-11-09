#ifndef CONTROL_FLAGS_H
#define CONTROL_FLAGS_H

#include "ffta.h"

/* The IWRAM control block at 0x03000940 (fftadecomp-kit#90).
 *
 * The block is the game's RAM image of the LCD registers: 08000718 DMAs
 * 0x03000942 to 0x04000008 (BG0CNT) as 39 halfwords, so +0x02..+0x4F shadow
 * BG0CNT..BLDY one-to-one, and `display` at +0x00 is the DISPCNT copy.
 *
 * Every halfword store to +0x02..+0x39 and every byte store to +0x3A..+0x4E
 * in the ROM is preceded by a load of the same member; this happens on this
 * object only, in every module that writes it, and never on other RAM.  That
 * is one declaration of the register members as volatile, the usual GBA
 * spelling for state shared with an interrupt handler.  `display` has plain
 * stores and is not volatile.  The window, blend and mosaic registers are
 * written a byte at a time, so they are declared as their low and high
 * bytes.  Bytes the ROM never stores (MOSAIC's high byte, the unused
 * 0x0400004E and BLDY's high byte) stay ordinary.  It is declared once,
 * here; sources must not repeat it. */
extern struct {
    u16 display;
    volatile u16 bg0cnt : 16;
    volatile u16 bg1cnt : 16;
    volatile u16 bg2cnt : 16;
    volatile u16 bg3cnt : 16;
    volatile u16 bg0hofs : 16;
    volatile u16 bg0vofs : 16;
    volatile u16 bg1hofs : 16;
    volatile u16 bg1vofs : 16;
    volatile u16 bg2hofs : 16;
    volatile u16 bg2vofs : 16;
    volatile u16 bg3hofs : 16;
    volatile u16 bg3vofs : 16;
    volatile u16 bg2pa : 16;
    volatile u16 bg2pb : 16;
    volatile u16 bg2pc : 16;
    volatile u16 bg2pd : 16;
    volatile u16 bg2x_l : 16;
    volatile u16 bg2x_h : 16;
    volatile u16 bg2y_l : 16;
    volatile u16 bg2y_h : 16;
    volatile u16 bg3pa : 16;
    volatile u16 bg3pb : 16;
    volatile u16 bg3pc : 16;
    volatile u16 bg3pd : 16;
    volatile u16 bg3x_l : 16;
    volatile u16 bg3x_h : 16;
    volatile u16 bg3y_l : 16;
    volatile u16 bg3y_h : 16;
    volatile u8 win0h_lo : 8;
    volatile u8 win0h_hi : 8;
    volatile u8 win1h_lo : 8;
    volatile u8 win1h_hi : 8;
    volatile u8 win0v_lo : 8;
    volatile u8 win0v_hi : 8;
    volatile u8 win1v_lo : 8;
    volatile u8 win1v_hi : 8;
    volatile u8 winin_lo : 8;
    volatile u8 winin_hi : 8;
    volatile u8 winout_lo : 8;
    volatile u8 winout_hi : 8;
    volatile u8 mosaic_lo : 8;
    u8 mosaic_hi;
    u8 unknown_48[2];
    volatile u8 bldcnt_lo : 8;
    volatile u8 bldcnt_hi : 8;
    volatile u8 bldalpha_lo : 8;
    volatile u8 bldalpha_hi : 8;
    volatile u8 bldy_lo : 8;
    u8 bldy_hi;
} g_control_flags_03000940;

#endif
