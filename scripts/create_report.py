#!/usr/bin/env python3
from pathlib import Path
R=Path(__file__).resolve().parents[1]
parts=['# Assignment 3 CO3 Report','', '**Student:** S Vinoth Kumar  ','**Register number:** 192471006  ', '**Repository:** https://github.com/vinoththecool7-netizen/DSA01-192471006-Assignment3','',
'This report evaluates constructors, destructors, resource ownership and meaningful overloaded operators through Q1–Q7. The corrected designs use validated construction, explicit ownership, exception-safe copying and well-defined value semantics. It includes actual assistant-run experiments and clearly labelled expected failures.','',
'Each task folder contains the complete source and machine-readable manifests. The exact compiler was Apple clang 21.0.0 on arm64 macOS; normal flags are -std=c++17 -Wall -Wextra -Wpedantic -Iinclude -O0, with separate optimisation and sanitizer variants. The original supplied specification is preserved unchanged.','',
'## Contents','']
for task in sorted(R.glob('Task[0-9][0-9]')):parts.append('- '+(task/'REPORT.md').read_text().splitlines()[0].lstrip('# '))
for task in sorted(R.glob('Task[0-9][0-9]')):
 parts+=['','---','',(task/'REPORT.md').read_text()]
 prediction=task/'prediction.txt'
 if prediction.exists():parts+=['','## Recorded pre execution prediction','','```text',prediction.read_text().rstrip(),'```']
 parts+=['','## Actual ordinary execution evidence','']
 for log in sorted((task/'evidence/normal').glob('*.stdout.txt')):parts += ['**'+log.name+'**','','```text',log.read_text().rstrip(),'```','']
 if task.name=='Task01':
  for log in sorted((task/'evidence/normal').glob('*.compile.txt')):
   text=log.read_text()
   if 'warning:' in text or 'error:' in text:parts+=['**'+log.name+'**','','```text',text.rstrip(),'```','']
 for log in sorted((task/'evidence/sanitized').glob('*broken*.stderr.txt')):
  parts+=['','## Actual expected sanitizer rejection','','**'+log.name+'**','','```text',log.read_text().rstrip(),'```']
 if task.name=='Task03':
  for log in sorted((task/'evidence/leak_probe').glob('*.txt')):
   if log.read_text():parts+=['','**Local leak detector probe '+log.name+'**','','```text',log.read_text().rstrip(),'```']
ci=R/'CI_EVIDENCE.json'
if ci.exists():
 import json
 info=json.loads(ci.read_text());raw=(R/'Task03/evidence/linux_ci_job.log').read_text()
 lines=raw.splitlines();start=next(i for i,l in enumerate(lines) if 'BEGIN LINUX LEAK EXPERIMENT missing_delete.cpp' in l);end=next(i for i,l in enumerate(lines) if 'LINUX LEAK EXPERIMENT PASSED:' in l)
 parts+=['','## Actual Linux leak detector evidence','',info['url'],'','The following is the timestamped genuine Linux job output for the broken and corrected seat maps. The complete job log is retained in Task03/evidence/linux_ci_job.log.','','```text','\n'.join(lines[start:end+1]),'```']
parts+=['','---','',(R/'VALIDATION.md').read_text(),'',(R/'EVIDENCE.md').read_text()]
(R/'REPORT.md').write_text('\n'.join(parts)+'\n');print('Generated complete REPORT.md from analyses and actual logs.')
