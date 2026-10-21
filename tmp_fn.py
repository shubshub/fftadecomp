import json, sys
d = json.load(open("config/functions.json"))
pat = sys.argv[1] if len(sys.argv) > 1 else "08125578"
for x in d:
    if pat.lower() in x["rom"].lower():
        print(json.dumps(x))
