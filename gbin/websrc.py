from argparse import ArgumentParser
import os.path
import webbrowser

def main():
  '''main function'''
  
  parser = ArgumentParser(
    prog='websrc',
    description='open src in google src')
  
  parser.add_argument('main')
  
  args = parser.parse_args()
  
  print(args.main);
  
  # find srcRoot
  found = False
  originalAbsArg = os.path.abspath(args.main)
  srcRoot = os.path.abspath(args.main)
  while not found:
    srcRoot = os.path.abspath(os.path.join(srcRoot,os.pardir))
    dotfile = os.path.join(srcRoot, '.gn')
    if os.path.isfile(dotfile):
      break
  
  # https://chromium.googlesource.com/chromium/src.git/+/master/base/at_exit.cc
  relativePath = originalAbsArg[len(srcRoot)+1:]

  
  url = 'https://chromium.googlesource.com/chromium/src.git/+/master/' + relativePath.replace('\\', '/')
  print('url=' + url)
  webbrowser.open(url, new=1) 

  
  
if __name__ == "__main__":
  main()

  