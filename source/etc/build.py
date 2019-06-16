import sys
import pathlib
import subprocess


def findMakefile(buildspace, subpath):
    currentDirectory = buildspace.joinpath(subpath)
    while (currentDirectory > buildspace):
        if currentDirectory.exists():
            for current in currentDirectory.iterdir():
                if current.is_dir():
                    continue

                if (current.name == 'Makefile'):
                    return current

        currentDirectory = currentDirectory.parent
    raise ValueError('Makefile not found in: ' + str(buildspace))


def findTarget(directory, subpath):
    path = subpath.relative_to(directory)
    return str(path) + ".o"


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

makeFile = findMakefile(workspace.joinpath(
    'build'), relativeFile.relative_to('source').parent)

target = findTarget(makeFile.parent, workspace.joinpath(
    'build').joinpath(relativeFile.relative_to('source')))

exit(subprocess.run(args=['make', '-B', '--makefile=' +
                          str(makeFile), target]).returncode)
