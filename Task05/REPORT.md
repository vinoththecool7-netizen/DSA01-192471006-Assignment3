# Q5 Increment comparison and subscript operators

## Design and verification

Time holds nonnegative elapsed seconds and rejects overflow. Prefix operator++() increments and returns Time&. Postfix operator++(int) is distinguished by a dummy int, saves the original value, increments and returns the old value. Tests verify a=t++ gives a=5 then t=6; b=++t gives b=t=7. == and < compare seconds. Minute and hour rollovers print 0:01:00 and 1:00:00. A short playlist simulation advances the current time.

Playlist owns vector<string>. Mutable [] returns string& for editing, while const [] returns const string& for read-only access. The signed index is checked for negativity before conversion and for index>=size. Invalid access throws out_of_range: merely printing an error and returning an invalid reference would be unsafe. playlist[-1] and playlist[size] are tested.

## Prediction and copy semantics

The Q1 commit saved prediction.txt before Counter was run. The exact output is 5 7 7 and a newline. Postfix returns old 5 for a; prefix advances c from 6 to 7 for b. Postfix has an old-value result; prefix returns a reference, although constructing a new b from that reference still copy-initialises b. The pasted listing placed the postfix definition/closing brace inside a // prefix comment; the intended line breaks were restored without changing the program's logic. Prediction and actual output match; authorship is identified as assistant prediction evidence.

## Experiments and interpretation

benchmark.cpp performs 10,000,000 operations per loop at both -O0 and -O2. Prefix/postfix results are consumed and checked against n(n+1)/2 and n(n-1)/2, and both timers end at n. It separately measures 10,000,000 checked versus unchecked accesses with identical checksums. Exact flags and local nanosecond totals are retained.

A volatile result sink keeps results observable but adds common overhead. Inlining, copy elimination, index proofs and scheduling affect the measured costs. This run found postfix slower at -O0 but slightly faster at -O2. Therefore old-value semantics do not guarantee an actual slowdown for an eight-byte class. ++i remains a good default when the old value is unnecessary because it does not require that result and may avoid expensive copies in larger types. Sanitized timings are diagnostic runs, not ordinary throughput comparisons.

## Alternative and complexity

at(i) throwing out_of_range can use the same check. Unchecked [] removes the branch but gives undefined behaviour on invalid access. Successful access is O(1) in either case with O(1) auxiliary space; exceptions are failure-path behaviour, not the valid-access benchmark. Prefix and postfix are O(1) for fixed-size Time; a postfix deep copy of an n-element owning object could instead cost O(n). Run python3 scripts/validate.py --task Task05, optionally with --sanitize.
