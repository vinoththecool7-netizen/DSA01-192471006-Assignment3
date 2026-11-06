#!/usr/bin/env python3
from pathlib import Path
import hashlib,json
R=Path(__file__).resolve().parents[1]
counts={'normal_runs':0,'sanitized_runs':0,'expected_compile_rejections':0,'expected_sanitizer_rejections':0,'intentional_leak_runs':0}
lines=['# Validation summary','','Student: S Vinoth Kumar; register number: 192471006.','',
'Normal and address/undefined-behaviour runs are retained separately. Expected compiler/sanitizer failures are successful demonstrations of intentionally invalid programs, not clean-memory passes.','']
for task in sorted(R.glob('Task[0-9][0-9]')):
 for mode in ['normal','sanitized']:
  directory=task/'evidence'/mode;data=json.loads((directory/'manifest.json').read_text())
  for file,digest in data['header_sha256'].items():assert hashlib.sha256((R/file).read_bytes()).hexdigest()==digest,file
  for record in data['programs']:
   source=R/record['source'];assert hashlib.sha256(source.read_bytes()).hexdigest()==record['sha256'],source
   if record['expected_compile_failure']:
    assert record['compile_exit']!=0;counts['expected_compile_rejections']+=1;continue
   assert record['compile_exit']==0 and record['passed'],record
   counts['normal_runs' if mode=='normal' else 'sanitized_runs']+=1
   if record['expected_sanitizer_failure']:counts['expected_sanitizer_rejections']+=1
   if source.name=='missing_delete.cpp':counts['intentional_leak_runs']+=1
 lines.append(f'- Q{int(task.name[-2:])}: source/header digests and expected outcomes verified in both modes.')
lines+=['','## Counts','']+[f'- {k.replace("_"," ")}: {v}' for k,v in counts.items()]
lines+=['','## Important distinctions','','- Three intentionally broken ownership/deallocation fixtures are rejected by ASan.',
'- The missing-delete fixture intentionally leaks in both local modes; ordinary local ASan does not detect leaks. Its zero exit code is not a claim of correctness.',
'- The local compiler/runtime both reject LeakSanitizer support; the actual probe diagnostics are retained.',
'- All corrected local program runs have zero process errors and no sanitizer stderr. Fixed expected outputs match exactly.',
'- Q3 and Q5 assistant predictions were committed before those programs were first executed.',
'- Timing measurements are single local observations; optimisation and common loop/call overhead are documented.']
ci=R/'CI_EVIDENCE.json'
if ci.exists():
 info=json.loads(ci.read_text());log=(R/'Task03/evidence/linux_ci_job.log').read_text()
 assert info['conclusion']=='success' and 'LINUX LEAK EXPERIMENT PASSED' in log and 'LeakSanitizer' in log
 lines+=['','## Linux verification','',f'- Actual successful GitHub Actions run: {info["url"]}',
 '- Linux LeakSanitizer detected the missing delete and found no leaks in the corrected Event experiment. The raw job log is retained under Task03/evidence/linux_ci_job.log.']
else:lines+=['','Linux CI evidence is not yet attached; do not infer a leak-detector finding from the local runs.']
lines+=['','Output screenshots and personal student execution/prediction evidence remain incomplete; no fabricated images or personal claims are included.']
(R/'VALIDATION.md').write_text('\n'.join(lines)+'\n');print('\n'.join(lines))
