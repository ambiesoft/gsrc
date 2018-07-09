from sys import argv
import subprocess
import argparse
from os import path


def myexit(message):
  '''Show message and quit'''
  print(message)
  exit(1)

def main():
  '''
  run gn gen for creating visual studio's sln.
  after creating it, start build with ninja.
  '''
  parser = argparse.ArgumentParser(description='gn gen and ninja')
  parser.add_argument('-j', help="ninja's -j, the number of processes", type=int)
  parser.add_argument("target")
  parser.add_argument("outdir", nargs='?')
  
  args = parser.parse_args()
  
  fullTarget = args.target
  outdir = args.outdir
  if not outdir:
    outdir=path.join('out', 'debug')
  
  if not fullTarget:
    myexit('fullTarget is empty.')
  if fullTarget[0:2] != '//':
    myexit('targe must be full target')
    
  # Name is after colon
  targetName = fullTarget.split(':')[-1]
  if not targetName:
    # if no colon, target name is same as folder name
    targetName = fullTarget.split('/')[-1]
    
  gngenarg = ['gn', 'gen', '--ide=vs2017', '--filters='+fullTarget, '--sln='+targetName, outdir]
  print(gngenarg)
  subprocess.call(['cmd', '/c'] + gngenarg)
  
  
  ninjaarg = ['ninja', '-C', outdir, fullTarget[2:]]
  if(args.j):
    ninjaarg.append('-j')
    ninjaarg.append(args.j)
  print(ninjaarg)
  subprocess.call(['cmd', '/c'] + ninjaarg)  
  
if __name__ == "__main__":
  main() 
