/* FFTA (AFXE) - GBA memory map
 *
 * Reference layout for the matching build.  This ROM has no separate load
 * address in the usual sense: the GBA maps ROM linearly at 0x08000000 and the
 * header + code live at the start of it, so the "link" is really just the
 * ordered section list in asm/ffta.s.  The regions below are what the code
 * writes to at runtime.
 *
 * ROM contents found by tools/analyze.py:
 *   0x08000000 - 0x080000C0   cartridge header (logo, title, code, checksum)
 *   0x080000C0 - 0x080000F4   ARM crt0: stack/IRQ setup, mode switch
 *   0x08000254 - 0x08000295   Thumb init reached from crt0
 *   0x08000000 - 0x08150000   code region (Thumb-dominant, data interleaved)
 *   0x08150000 - 0x08A39820   assets: compressed data (entropy ~7.5) and
 *                             4bpp tile data (entropy ~3.5-4.5)
 *   0x08A39820 - 0x08FE1350   zero padding
 *   0x08FE1350 - 0x08FFFFFF   0xFF padding to the 16 MiB boundary
 */

MEMORY {
    rom   (rx)  : ORIGIN = 0x08000000, LENGTH = 16M
    ewram (rwx) : ORIGIN = 0x02000000, LENGTH = 256K
    iwram (rwx) : ORIGIN = 0x03000000, LENGTH = 32K
}

/* GBA I/O registers the game touches (from the crt0 literal pool). */
REGION_IO        : ORIGIN = 0x04000000, LENGTH = 0x400
REGION_PALETTE   : ORIGIN = 0x05000000, LENGTH = 0x400
REGION_VRAM      : ORIGIN = 0x06000000, LENGTH = 0x18000
REGION_OAM       : ORIGIN = 0x07000000, LENGTH = 0x400
REGION_SRAM      : ORIGIN = 0x0E000000, LENGTH = 0x20000
REGION_CART      : ORIGIN = 0x0A000000, LENGTH = 0x200

/* IWRAM scratch used by the startup code (stack tops seen at 0x03007E00). */
__sp_usr    = 0x03007FA0;
__sp_irq    = 0x03007EC0;
__irq_vector = 0x03007FFC;

ENTRY(_start)