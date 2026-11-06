#!/usr/bin/env python3
"""Collect genuine Linux LeakSanitizer results for the broken and correct seat maps."""
from pathlib import Path
import json,os,platform,shlex,subprocess
R=Path(__file__).resolve().parents[1]
if platform.system()!='Linux':raise SystemExit('This leak-detector experiment requires a supported Linux runtime; macOS probe evidence is retained separately.')
out=R/'Task03/evidence/linux_leaks';out.mkdir(parents=True,exist_ok=True);(R/'build').mkdir(exist_ok=True)
records=[]
for source,expected in [('missing_delete.cpp',True),('main.cpp',False)]:
 binary=R/'build'/('linux_leaks_'+source.replace('.cpp',''))
 cmd=['g++','-std=c++17','-Wall','-Wextra','-Wpedantic','-O0','-g','-fsanitize=address','-fno-omit-frame-pointer','-Iinclude','Task03/'+source,'-o',str(binary)]
 c=subprocess.run(cmd,cwd=R,text=True,capture_output=True)
 (out/(source+'.compile.txt')).write_text('$ '+shlex.join(cmd)+'\n'+c.stdout+c.stderr+f'\nexit_code={c.returncode}\n')
 if c.returncode:raise SystemExit(c.stderr)
 env=dict(os.environ);env['ASAN_OPTIONS']='detect_leaks=1';env['LSAN_OPTIONS']='exitcode=23'
 run=subprocess.run([str(binary)],cwd=R,text=True,capture_output=True,env=env,timeout=90)
 (out/(source+'.stdout.txt')).write_text(run.stdout);(out/(source+'.stderr.txt')).write_text(run.stderr)
 ok=(run.returncode!=0 and 'LeakSanitizer' in run.stderr) if expected else run.returncode==0 and not run.stderr
 record={'source':source,'expected_leak':expected,'exit':run.returncode,'passed':ok,'compile':shlex.join(cmd)};records.append(record)
 print('BEGIN LINUX LEAK EXPERIMENT',source,flush=True);print(run.stdout,flush=True);print(run.stderr,flush=True);print(json.dumps(record),flush=True)
 if not ok:raise SystemExit('Unexpected leak-probe outcome: '+source)
(out/'manifest.json').write_text(json.dumps({'platform':platform.platform(),'compiler':subprocess.run(['g++','--version'],capture_output=True,text=True).stdout,'ASAN_OPTIONS':'detect_leaks=1','LSAN_OPTIONS':'exitcode=23','records':records},indent=2)+'\n')
print('LINUX LEAK EXPERIMENT PASSED: missing delete detected; corrected Event clean.',flush=True)
