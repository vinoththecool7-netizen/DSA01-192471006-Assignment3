#!/usr/bin/env python3
"""Real compilation/execution evidence, including isolated expected failures."""
import argparse,datetime,hashlib,json,os,platform,shlex,subprocess
from pathlib import Path
P=argparse.ArgumentParser();P.add_argument('--task');P.add_argument('--sanitize',action='store_true');a=P.parse_args()
R=Path(__file__).resolve().parents[1];cxx=os.environ.get('CXX','g++');flags=['-std=c++17','-Wall','-Wextra','-Wpedantic','-Iinclude']
if a.sanitize:flags+=['-g','-fsanitize=address,undefined','-fno-omit-frame-pointer']
(R/'build').mkdir(exist_ok=True)
tasks=[R/a.task] if a.task else sorted(R.glob('Task[0-9][0-9]'))
failures=[]
for task in tasks:
 out=task/'evidence'/('sanitized' if a.sanitize else 'normal');out.mkdir(parents=True,exist_ok=True);records=[]
 sources=sorted(task.glob('*.cpp'))+sorted(task.glob('*.cpp.txt'))
 for src in sources:
  broken='broken' in src.stem
  if broken and not a.sanitize:continue # Deliberate UB is executed only with diagnostics enabled.
  variants=['-O0','-O2'] if src.name=='benchmark.cpp' else ['-O0']
  if src.name=='text.cpp':variants+=['-O2','-fno-elide-constructors']
  for opt in variants:
   suffix=opt.replace('-','');name=src.name.replace('.cpp.txt','').replace('.cpp','')+'_'+suffix
   binary=R/'build'/f'{task.name}_{name}_{"san" if a.sanitize else "normal"}'
   cmd=[cxx,*flags,opt]
   if src.suffix=='.txt':cmd+=['-x','c++']
   cmd+=[str(src.relative_to(R)),'-o',str(binary.relative_to(R))]
   compiled=subprocess.run(cmd,cwd=R,capture_output=True,text=True)
   (out/f'{name}.compile.txt').write_text('$ '+shlex.join(cmd)+'\n'+compiled.stdout+compiled.stderr+f'\nexit_code={compiled.returncode}\n')
   expected_failure='.fail.' in src.name
   record={'source':str(src.relative_to(R)),'sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'compile':shlex.join(cmd),'compile_exit':compiled.returncode,'expected_compile_failure':expected_failure}
   if expected_failure:
    if compiled.returncode==0:failures.append(str(src)+' unexpectedly compiled')
    records.append(record);continue
   if compiled.returncode:failures.append(str(src)+' compile failed');records.append(record);continue
   data=src.with_suffix('.stdin.txt');stdin=data.read_text() if data.exists() else ''
   env=dict(os.environ)
   if a.sanitize:env['ASAN_OPTIONS']='detect_leaks=0:alloc_dealloc_mismatch=1'
   run=subprocess.run([str(binary)],cwd=task,input=stdin,capture_output=True,text=True,env=env,timeout=120)
   (out/f'{name}.stdout.txt').write_text(run.stdout);(out/f'{name}.stderr.txt').write_text(run.stderr)
   expected=src.with_suffix('.expected.txt');match=run.stdout==expected.read_text() if expected.exists() else None
   ok=(run.returncode!=0 and 'AddressSanitizer' in run.stderr) if broken else run.returncode==0 and not run.stderr and match is not False
   record.update(run=str(binary.relative_to(R)),stdin=str(data.relative_to(R)) if data.exists() else '(embedded or no input)',run_exit=run.returncode,expected_sanitizer_failure=broken,matches_expected=match,passed=ok)
   records.append(record)
   if not ok:failures.append(f'{task.name}/{name} exit={run.returncode} expected={match}')
   print(task.name,name,'PASS' if ok else 'FAIL', 'expected sanitizer rejection' if broken else '')
 manifest={'generated_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'platform':platform.platform(),'compiler':subprocess.run([cxx,'--version'],capture_output=True,text=True).stdout,'asan_options':'detect_leaks=0:alloc_dealloc_mismatch=1' if a.sanitize else None,'header_sha256':{str(p.relative_to(R)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted((R/'include').glob('*.hpp'))+sorted(task.glob('*.hpp'))},'programs':records}
 (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
if failures:raise SystemExit('\n'.join(failures))
