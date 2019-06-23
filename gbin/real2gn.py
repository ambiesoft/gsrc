import sys
import os.path


def isSamePath(a, b):
    return os.path.abspath(a) == os.path.abspath(b)


def findSourceRootDirectory():
    tryDir = '.'
    lastAbsPath = os.path.abspath(tryDir)
    while True:
        if os.path.isfile(os.path.join(tryDir, '.gn')):
            return tryDir

        tryDir = os.path.join('..', tryDir)
        if isSamePath(tryDir, lastAbsPath):
            exit('.gn not found in current and all its parent directories')
        lastAbsPath = os.path.abspath(tryDir)


def getRelativePath(sourceDir, path):
    '''
    Get relative path from sourceDir.
    if input = C:\\a\\b\\c\\d\\x.txt and sourceDir = C:\\a\\b,
    the result is c\\d\\x.txt
    '''
    return os.path.relpath(path, sourceDir)


def real2gn(inputPath):

    # find dir where .gn found
    sourceDir = findSourceRootDirectory()

    # get the relative path from .gn dir
    diffPath = getRelativePath(sourceDir,inputPath)
    
    # create output
    diffPath = diffPath.replace('\\', '/')
    gnPath = '//' + diffPath

    return gnPath

def main():
    if len(sys.argv) <= 1:
        exit('No input path')

    inputPath = sys.argv[1]
    print(real2gn(inputPath))
    
if __name__ == "__main__":
    main()
