import os, re, sys
root = sys.argv[1]
pat = re.compile(sys.argv[2])
skip = {".o", ".a", ".i", ".s", ".gch"}
hits = 0
for dirpath, dirnames, filenames in os.walk(root):
    for name in filenames:
        if os.path.splitext(name)[1] in skip:
            continue
        p = os.path.join(dirpath, name)
        try:
            with open(p, errors="replace") as fh:
                for i, line in enumerate(fh):
                    if pat.search(line):
                        print(f"{p}:{i+1}: {line.rstrip()}")
                        hits += 1
                        if hits > 200:
                            print("... truncated")
                            sys.exit(0)
        except OSError:
            pass
print(f"[{hits} hits]")
