import sys
import subprocess
import argparse
from os import path
import os

THISDIR = os.path.dirname(os.path.realpath(__file__))

def myexit(message=None, ret=1):
  '''Show message and quit'''
  if message:
    print(message)
  exit(ret)

# http://code.activestate.com/recipes/577058/
def query_yes_no(question, default="no"):
    """Ask a yes/no question via raw_input() and return their answer.
    
    "question" is a string that is presented to the user.
    "default" is the presumed answer if the user just hits <Enter>.
        It must be "yes" (the default), "no" or None (meaning
        an answer is required of the user).

    The "answer" returned is one of "yes" or "no".
    """
    valid = {"yes":"yes",   "y":"yes",  "ye":"yes",
             "no":"no",     "n":"no"}
    if default == None:
        prompt = " [y/n] "
    elif default == "yes":
        prompt = " [Y/n] "
    elif default == "no":
        prompt = " [y/N] "
    else:
        raise ValueError("invalid default answer: '%s'" % default)

    while 1:
        sys.stdout.write(question + prompt)
        choice = raw_input().lower()
        if default is not None and choice == '':
            return default
        elif choice in valid.keys():
            return valid[choice]
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' "\
                             "(or 'y' or 'n').\n")

  
def toOutDir(dir):
  if not dir:
    return None
  return path.join('out', dir)

def getLastPart(path, sep='/'):
  out = path.split(sep)[-1]
  return out

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
    outdir = toOutDir(os.getenv('CURRENT_DEBUGDIR'))
    if not outdir:
      outdir=path.join('out', 'debug')
  
  if not fullTarget:
    myexit('fullTarget is empty.')
  if fullTarget[0:2] != '//':
    myexit('target must be full target')
    
  # Name is after colon, if not colon after '/'
  targetName = fullTarget.split(':')[-1].split('/')[-1]
  
  slnFilename = targetName + '.sln'
  if path.exists(path.join(outdir, slnFilename)):
     if 'yes' != query_yes_no(slnFilename + ' already exists. Do you want to run "gn gen" again?'):
       myexit(ret=0)
     else:
       os.remove(path.join(outdir, slnFilename))
  

  # ninja
  ninjaarg = ['autoninja', '-C', outdir, fullTarget[2:]]
  if(args.j):
    ninjaarg.append('-j')
    ninjaarg.append(str(args.j))
#  else:
#    ninjaarg.append('-j')
#    ninjaarg.append('6')
    
  print(ninjaarg)
  ret = subprocess.call(['cmd', '/c'] + ninjaarg)
  if ret != 0:
    myexit(ret=ret)


  # gn gen
  tmpSlnFileName = targetName + '_gngennin'
  gngenarg = ['gn', 'gen', '--ide=vs2019', '--filters='+fullTarget, '--sln=' + tmpSlnFileName, outdir]
  print(gngenarg)
  subprocess.call(['cmd', '/c'] + gngenarg)
  slnTmpFull = path.join(outdir, tmpSlnFileName+'.sln')
  slnFull = path.join(outdir, slnFilename)
  os.rename(slnTmpFull, slnFull)
  

  # select startup project
  slnStartupProjectExe = os.path.join(THISDIR, "slnStartupProject\\bin\\slnStartupProject.exe")
  if not os.path.isfile(slnStartupProjectExe):
    myexit(r"""'{}' is not found. Run 'git submodule update -i'""".format(slnStartupProjectExe))

  slnStartupProjectArg = [
    slnStartupProjectExe,
    slnFull,
    targetName
  ]
  print(slnStartupProjectArg)
  subprocess.call(slnStartupProjectArg)

if __name__ == "__main__":
  main() 
