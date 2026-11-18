# 0800CFC8 — mode 1 affine scanline constructor

The reconstructed C produces the original 200 bytes at `[0800CFC8, 0800D090)` with the standard Thumb agbcc recipe. SHA-256 for both images is `10526b37b1922937dbb24d101581a4809d6c43b3f0783bd290dc03a025d41dfc`. The toolkit CFG closes at 92 reachable instructions. The return is at 0800D084, followed by two zero alignment bytes and two literal words.

The constructor registers callback 0800D3BC via 0800C3CC with a 0x2B8-byte payload and 16-byte rows. It gets the payload from 0800C614, sets the mode to 1, writes the two fixed-point origins and the signed center/offset sums in both parameter sets, initializes both scales to 0x100, and stores the radius at +0x34. It invokes 0800C9E4 with the payload and 1, then returns the task pointer from registration. The original constructor test in `tests/test_bg_affine_rows.py` exercises BG2 and BG3 through the alternate banks, hardware transfer and release.

## Stack index

At 0800CFFE–0800D006 the constructor copies the two words at 08149820 to its eight local stack bytes. Those words are the BG2 and BG3 affine register blocks, 04000020 and 04000030. The load at 0800D014 passes `targets[(u8)target - 2]` to registration. A native execution of the original prefix for each of the 256 low-byte values reached 0800D01A. Only 2 and 3 loaded within the local array. Values 0 and 1 read at SP−8 and SP−4, 4 reads saved R8 at SP+8, and 10 reads saved LR at SP+32. Initializing only valid targets for the native frame test establishes the two supported effects, but gives no caller guarantee.

An aligned full-ROM scan found no immediate Thumb BL, B, conditional B or ARM B/BL to 0800CFC8, and no literal copy of the even or odd function address at any byte alignment. The table address itself appears at 0800CFBC, 0800D088, 0800D160 and 0800D234 in the four constructors. An unseen caller could use a computed address.

## Verification

In a scratch checkout, place the C at `src/0800CFC8.c` and name `data_08149820` at 08149820 in the data-symbol map. The standard link with the three callees and callback at their original addresses reproduces the complete symbol. On toolkit `47cd658f`, `plausible.py --strict` passes. Default `match.py --no-write` refuses the variable stack-address materialization. With `--owner-runtime-profile named-data-buffer-stack-index-v2` it requires a reviewed bound of 5 at 0800D014 for the unsigned byte offset `(((entry_R0 << 24) >> 22) - 8)`. The original permits offsets outside that bound. There is no verified caller premise or match report.
