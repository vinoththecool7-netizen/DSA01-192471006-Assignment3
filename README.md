# Assignment 3 Constructors Destructors and Operator Overloading

Student: **S Vinoth Kumar**  
Register number: **192471006**  
Repository: https://github.com/vinoththecool7-netizen/DSA01-192471006-Assignment3

This submission contains Q1–Q7, each in Task01–Task07, with C++17 source, a task report, actual outputs, input fixtures where consumed, compiler diagnostics, sanitizer reports and measured timings. The full report is [REPORT.md](REPORT.md); the original attachment is [ASSIGNMENT_SPECIFICATION.txt](ASSIGNMENT_SPECIFICATION.txt). Read [VALIDATION.md](VALIDATION.md) and [EVIDENCE.md](EVIDENCE.md) for evidence limits.

## Compiler and exact commands

Local compiler: Apple clang 21.0.0 (clang-2100.4.1.1), arm64-apple-darwin27.2.0. On this Mac, the g++ command invokes Apple clang rather than GNU GCC. Full version output, source/header digests and exact commands are retained in every task's evidence manifests. The verified Linux run used GNU g++ 13.3.0 on Ubuntu 24.04.5; its compiler output and raw job log are retained.

From the repository root, with Python 3 and a C++17 compiler:

```sh
python3 scripts/validate.py
python3 scripts/validate.py --sanitize
python3 scripts/check_evidence.py
```

Run one question by adding --task Task01 (through Task07). CXX=clang++ can select another compiler. The validator builds each file with the exact base flags:

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -O0 Task01/book.cpp -o build/Task01_book
./build/Task01_book
```

Replace the source using the table below. All programs run without external stdin except Task04/io.cpp:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -O0 Task04/io.cpp -o build/Task04_io
./build/Task04_io < Task04/io.stdin.txt
```

Sanitizer flags are -g -fsanitize=address,undefined -fno-omit-frame-pointer. The runner explicitly sets ASAN_OPTIONS=detect_leaks=0:alloc_dealloc_mismatch=1 because local LeakSanitizer is unsupported. Separate Linux leak experiments use detect_leaks=1. Do not execute the intentionally broken examples without the sanitizer and expect meaningful defined results.

Task05/benchmark.cpp is measured at -O0 and -O2. Task06/text.cpp additionally runs at -fno-elide-constructors. Record timings from your own run; they are not stable expected outputs.

## Questions and programs

| Question | Files within task folder | Observed result |
|---|---|---|
| [Q1](Task01/REPORT.md) | book.cpp; no_default.fail.cpp.txt; explicit.fail.cpp.txt; implicit.ok.cpp.txt; reorder.warn.cpp.txt | Every constructor executes; negative copies rejected; missing default/explicit calls fail; reorder warning recorded. |
| [Q2](Task02/REPORT.md) | main.cpp; prescription.hpp; complete.cpp; vector.cpp; shallow_broken.cpp; without_copy_broken.cpp | Independent deep copies, self-assignment and pass-by-value/reference counts verified; both broken variants rejected by ASan; supplied output matched. |
| [Q3](Task03/REPORT.md) | main.cpp; seat_map.hpp; logger.cpp; missing_delete.cpp; delete_mismatch_broken.cpp | Seat booking/lifetimes/zero rows and requested memory sizes checked; Logger prediction matched; mismatch rejected; Linux LeakSanitizer detected the missing delete and verified corrected cleanup. |
| [Q4](Task04/REPORT.md) | main.cpp; money.hpp; complete.cpp; io.cpp; io.stdin.txt | Exact bill/carry, signed refunds, overflow and stream validation passed; million-addition drift measured; supplied output matched. |
| [Q5](Task05/REPORT.md) | main.cpp; playback.hpp; counter.cpp; benchmark.cpp | Counter prediction matched; rollover/checked const access passed; 10 million increments/accesses timed at both optimisation levels. |
| [Q6](Task06/REPORT.md) | text.cpp; text.hpp | Deep ownership/empty/long/self-assignment checks passed; copies and 100,000 independent concatenations measured with optimisation/elision variants. |
| [Q7](Task07/REPORT.md) | main.cpp; complex.hpp | Series 100-50j and parallel 50+50j matched hand calculations; zero division handled; 4,000 std::complex comparisons had no mismatches. |

The .cpp.txt sources are intentional compile diagnostics/conversion demonstrations. The validator compiles them with -x c++; expected failures do not mean the corrected programs failed. The broken ownership/deallocation .cpp files are separately executed only in sanitizer mode. The missing-delete fixture is deliberately incorrect and is not a clean-memory pass.

## Input and expected output evidence

Most task inputs are explicit constructor arguments, test-case data, deterministic generated operands or benchmark counts in source. No unconsumed input files are passed off as execution evidence. The actual consumed Task04 input and exact stdout fixture are supplied. Fixed supplied-program outputs are compared byte for byte, including Logger's trailing space and absent newline. Timing and sanitizer-address variation are preserved as actual observations.

The Q3/Q5 predictions were committed in the Q1 commit before first execution. They are assistant-authored predictions. The Q5 pasted Counter listing required restoration of line breaks around its // prefix comment; no intended behaviour was changed.

## Submission evidence and history

Each question has a progressively published commit with its source/report/results. The history reflects this real work session, without backdated commits or a fabricated week-long development story. UML/memory diagrams, alternatives, complexity analyses and raw measurements appear in the report and task folders. The student must review, individually execute and explain the work during verification.

The Linux workflow runs verification on relevant source changes; its actual status and captured leak evidence are recorded separately when available.

Verified Linux CI: https://github.com/vinoththecool7-netizen/DSA01-192471006-Assignment3/actions/runs/42157408603

That run passed ordinary and sanitizer experiments. Its leak detector reported 357 bytes in 13 allocations for the intentionally missing delete; the corrected Event run exited cleanly. See CI_EVIDENCE.json for the exact tested source commit.
