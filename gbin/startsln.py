
import argparse
import os

DEBUGDIR = 'out/debug'


def hasExtension(file, ext):
    filename, file_extension = os.path.splitext(file)
    return file_extension == ext


def main():
    parser = argparse.ArgumentParser(
        prog='startsln', description='Start Visual Studio solution')
    parser.add_argument('sln',
                        nargs='?',
                        help="Part of string for solution name")

    args = parser.parse_args()

    print(args)
    if not args.sln:
        exit('No string specified')

    debugdir = os.path.join('.', DEBUGDIR)
    if not os.path.exists(debugdir):
        exit('{debugdir} does not exist.')

    slncands = []
    for file in os.listdir(debugdir):
        if not os.path.isfile(os.path.join(debugdir, file)):
            continue
        if not hasExtension(file, '.sln'):
            continue
        if not file.startswith(args.sln):
            continue
        print(file)
        slncands.append(file)

    if not slncands:
        exit('not found')

    sln_to_start = os.path.join(debugdir, slncands[0])
    print("Starting solution '{}'...".format(sln_to_start))
    os.startfile(sln_to_start)


if __name__ == '__main__':
    main()
