import sys
import pathlib
import subprocess


def findMakefile(workspace, relativeFile):
    buildspace = workspace.joinpath('build')
    currentDirectory = buildspace.joinpath(
        relativeFile.relative_to('source').parent)

    while (currentDirectory > buildspace):
        if currentDirectory.exists():
            for current in currentDirectory.iterdir():
                if current.is_dir():
                    continue

                if (current.name == 'Makefile'):
                    return current

        currentDirectory = currentDirectory.parent

    raise ValueError('Makefile not found in: ' + str(buildspace))


def findTarget(workspace, relativeFile, makeFile):
    makeFilePart = workspace.joinpath('build').joinpath(
        relativeFile.relative_to('source'))
    target = makeFilePart.relative_to(makeFile.parent)
    return str(target) + ".o"


if len(sys.argv) < 2:
    raise ValueError("Missing workspace root argument")
workspace = pathlib.Path(sys.argv[1])
if len(sys.argv) < 3:
    raise ValueError("Missing relative target file argument")
relativeFile = pathlib.Path(sys.argv[2])

if relativeFile.is_file() is False:
    raise ValueError('Target file not found: ' + str(relativeFile))

if relativeFile.suffix not in ['.cpp', '.c', '.cc', '.cxx']:
    raise ValueError('Target file is not a c++ file: ' + relativeFile.suffix)

makeFile = findMakefile(workspace, relativeFile)

target = findTarget(workspace, relativeFile, makeFile)

exit(subprocess.run(args=['make', '-B', '--makefile=' +
                          str(makeFile), target]).returncode)
