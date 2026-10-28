# 080A0854 — Parked

Target: 360 bytes / 180 reachable instructions.

The retained complete natural C compiles to 356 bytes under the fixed default native matcher. The final invocation exits 1 at the indexed-extent guard: compiled symbol is shorter than the indexed span, 356 < 360. Consequently the retained candidate has no native byte-comparison or source-plausibility verdict, and no exact-match credit is claimed.

The retained representation uses signed halfword coordinates, separate inline movement-duration and planar-distance calculations, an inline motion initializer, duration limiting, and the two height-bound modes. Compiler diagnostics show shared endpoint differences and a four-word local stack frame; the target recomputes those differences and uses five words. Initial step shifts, height-adjustment algebra, and register allocation also differ.

Bounded attempts included direct distance expressions with a local absolute-value helper or builtin abs, separate signed-halfword calculation helpers, and promoted or mixed-width helper parameters. The direct form reached a complete 370-byte plausible result with 50/185 instructions and 199/370 bytes identical; the signed-halfword helper form retained here is closest in extent. No forbidden compiler steering was used.

The final native output and the earlier differing report remain in private address scratch, outside the matching root. The earlier report describes the 370-byte attempt, not this retained 356-byte source.
