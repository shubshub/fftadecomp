# 08000718

The complete indexed ROM target is 0x08000718..0x08000788, 112 bytes and
43 reachable Thumb instructions. The recovered behavior writes DMA0's source,
destination and control registers, reads the control register once, polls its
enable bit until clear, then copies the halfword at 0x03000940 to 0x03002BBC.
The source and destination addresses are 0x03000942 and 0x04000008; the DMA
control word is 0x80000027.

One complete natural C reconstruction was tested using the unchanged native
matcher and fixed agbcc -mthumb-interwork -O2. Native exit 1 was:

    compiled symbol is shorter than the indexed span: 76 < 112

The extent gate refused the candidate before byte comparison and plausibility
checking. No byte-identical or plausibility verdict is claimed.

The target establishes r7 as a frame pointer, reserves eight local bytes,
stores the source and DMA-register pointers in those locals, repeatedly reloads
them, and stores the same DMA-register address again before polling. The tested
natural reconstruction lets fixed O2 optimize those ordinary local pointers.
Its volatile qualifier applies only to the genuine DMA0 MMIO register block,
including the explicit hardware read and busy polling. It does not qualify RAM
or local pointer storage. No artificial volatile locals, optimization changes,
assembly, or other code-generation steering were attempted. Reproducing the
target's retained local-pointer traffic remains unresolved under the fixed
compiler settings; an original lower-optimization build is an inference, not
an experimentally established compiler configuration.

The unmatched active source and report were removed. The complete tested C is
preserved here; the root coordinator owns reservation release and integration.
