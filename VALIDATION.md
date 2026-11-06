# Validation summary

Student: S Vinoth Kumar; register number: 192471006.

Normal and address/undefined-behaviour runs are retained separately. Expected compiler/sanitizer failures are successful demonstrations of intentionally invalid programs, not clean-memory passes.

- Q1: source/header digests and expected outcomes verified in both modes.
- Q2: source/header digests and expected outcomes verified in both modes.
- Q3: source/header digests and expected outcomes verified in both modes.
- Q4: source/header digests and expected outcomes verified in both modes.
- Q5: source/header digests and expected outcomes verified in both modes.
- Q6: source/header digests and expected outcomes verified in both modes.
- Q7: source/header digests and expected outcomes verified in both modes.

## Counts

- normal runs: 20
- sanitized runs: 23
- expected compile rejections: 4
- expected sanitizer rejections: 3
- intentional leak runs: 2

## Important distinctions

- Three intentionally broken ownership/deallocation fixtures are rejected by ASan.
- The missing-delete fixture intentionally leaks in both local modes; ordinary local ASan does not detect leaks. Its zero exit code is not a claim of correctness.
- The local compiler/runtime both reject LeakSanitizer support; the actual probe diagnostics are retained.
- All corrected local program runs have zero process errors and no sanitizer stderr. Fixed expected outputs match exactly.
- Q3 and Q5 assistant predictions were committed before those programs were first executed.
- Timing measurements are single local observations; optimisation and common loop/call overhead are documented.

## Linux verification

- Actual successful GitHub Actions run: https://github.com/vinoththecool7-netizen/DSA01-192471006-Assignment3/actions/runs/42157408603
- Linux LeakSanitizer detected the missing delete and found no leaks in the corrected Event experiment. The raw job log is retained under Task03/evidence/linux_ci_job.log.

Output screenshots and personal student execution/prediction evidence remain incomplete; no fabricated images or personal claims are included.
