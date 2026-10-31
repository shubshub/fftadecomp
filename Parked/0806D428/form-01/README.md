# 0806D428 form01: semantic layout defect

Accepted lease sol-D428, claim6537103008. Original default native attempt exited1 with plausible source, but emitted362B for the complete358B target. This first form embedded State0806FE14 at1A88 and then treated its size as1B when naming/sizing the following unknown region. The native compiler rounds the embedded object to4B, so downstream fields were emitted at incorrect offsets, including446F instead of446C and4473 instead of4470. Further alignment moved selection/records by4B.

Source, report and native result here are byte-identical originals. Full logs, complete compiled body, original current-machine/source/header/map/tool pins and exact layout diagnosis remain in state/matching-0806D428-author/. No original proof replay or diagnostic was performed.

Parent authorized one concrete layout correction under the same active lease, changing only the following unknown region from unknown_1A89[0x29E3] to unknown_1A8C[0x29E0]. This first failure remains immutable and is not match credit. The true owner is still [0806D428,0806D58E),358B; native's362B printed comparison window included4B beyond it and does not justify an index expansion.
