import argparse
import os
import subprocess


def hasExtension(file, ext):
    filename, file_extension = os.path.splitext(file)
    return file_extension == ext


def main():
    parser = argparse.ArgumentParser(
        prog='startfile', description='Start Visual Studio solution')
    parser.add_argument('-t',
                        nargs=1,
                        help="The execution type. 'exe' or 'sln'")
    parser.add_argument('file',
                        nargs='?',
                        help="Part of string for solution name")
    # parser.add_argument('',
    #                     nargs='*',
    #                     help="Arguments to pass to the program")

    # args = parser.parse_args()
    args, passArgs = parser.parse_known_args()
    if not args.t:
        exit('-t must be set.')

    args.t = args.t[0]

    if args.t != 'exe' and args.t != 'sln':
        exit("-t must be one of 'exe' or 'sln'")
    if not args.file:
        exit('No string specified')
    if not os.getenv('CURRENT_DEBUGDIR'):
        exit('Env value CURRENT_DEBUGDIR is not set.')

    outdir = os.path.join('.', 'out', os.getenv('CURRENT_DEBUGDIR'))
    if not os.path.isdir(outdir):
        exit('{outdir} is not a directory')

    cands = []
    ext = '.sln' if args.t == 'sln' else '.exe'
    for file in os.listdir(outdir):
        if not os.path.isfile(os.path.join(outdir, file)):
            continue
        if not hasExtension(file, ext):
            continue
        if not file.startswith(args.file):
            continue
        # print(file)
        cands.append(file)

    if not cands:
        exit('not found')

    file_to_start = ''
    if len(cands) > 1:
        message = ''
        for i, x in enumerate(cands):
            message += '{}: {}\n'.format(i+1, x)
        message += 'Enter Number: '
        inpnum = int(input(message))
        file_to_start = os.path.join(outdir, cands[inpnum-1])
    else:
        file_to_start = os.path.join(outdir, cands[0])

    print("Starting '{}'...".format(file_to_start))

    # Run with passArgs if exe
    if args.t == 'exe':
        runArgs = [file_to_start]
        runArgs.extend(passArgs)
        subprocess.call(runArgs)
    else:
        if passArgs:
            print('Passed args will be ignored')
        os.startfile(file_to_start)


if __name__ == '__main__':
    main()
