# 0806F994 selection window ability icons

The original spans 0806F994 through 0806FABB inclusive. It has 137 reachable Thumb instructions, one alignment halfword and two literal words. The normal compiler emits a 292-byte symbol for this C reconstruction. The original is 296 bytes.

## Original behavior

The selection handler at 0806F8DC calls the owner in state 1. Its constructor at 0806F7B8 configures the 13 by 18 window, clears the 234-entry tilemap and resets three animation counters. On a selection change the handler resets those counters again.

Item type 0x1B skips all ability processing. Other types call 080C8D14 with a 28-byte local group list. Reading all 376 item records between 0851D180 and 08520080 finds 10 special items. Of the other 366 items, 150 produce zero groups, 96 produce one, 82 produce two and 38 produce three. Group sizes run from one to three. The original source categories run from 2 to 43.

Each group animates with one byte. The low six bits count ticks within a frame and the high two bits select a source. At the start of a frame, 080CB9E0 decodes the category icon into the 256-byte local buffer. The original 0814186C wrapper requests 128 halfwords of synchronous BIOS CpuSet copy into the selected character tiles. The palette comes from 080CBA14. The tile run at 0802AB64 emits two four-tile rows. The timer advances on every processed group and resets when the high two bits reach its group size. The final 0806F5FC copies the complete window to the destination tilemap, including for a special item or an empty group list.

## Compiler difference

On item type 0x1B the original computes the embedded transfer-record address, saves it at stack offset 0x13C, then jumps to the final tilemap call. This source stores a group count of zero and takes the same output path through the loop header. On the other items the compiler places the group list, icon buffer, count, width and loop invariants at the original stack offsets. The graphics calls bind to the original symbols. The main loop lies four bytes before its original address.

After the timer store at 0806FA78, the original reloads the new byte and shifts it right six bits. The compiler narrows the incremented register value and obtains the same frame index. Both the caller and constructor show ordinary byte counters owned by the selection state.

## Native check

The complete original state-1 caller ran against both the original owner and the linked C candidate. The test installed the game's 03005E78 initializer from its ROM image and executed the original ability reader, archive decoder, palette reader and tile writers. The BIOS CpuSet hook copied the 256 bytes reached through the original SWI. On each run the input included a live 234-halfword source tilemap, a 32-tile destination stride, separate character tile storage and the same initialized item selection.

All 376 indexed items were tested at ticks 0, 63, 64, 127, 128 and 191, reduced modulo each group's complete animation period. All 2,256 comparisons agreed on the entire selection state, source tilemap, destination tilemap and character tiles. The official default verifier currently reports `unsupported stack-alias use or escape`. This candidate has no MATCH receipt.
