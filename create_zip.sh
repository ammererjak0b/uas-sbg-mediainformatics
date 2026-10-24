#!/bin/bash
# usage: ./create_zip.sh <pathToLab>   e.g. ./create_zip.sh 01OpenCv
# zip lands in ./.submission/ (relative to where the script is called)
# task folders LBEL00, LBEL01, ... -> 00, 01, ... in the zip

studyProgram="ITS-B" # without year
# set in ~/.zshrc: STUD_LASTNAME, STUD_FIRSTNAME, STUD_MATRICULATION
lastName="$STUD_LASTNAME"
firstName="$STUD_FIRSTNAME"
matriculationNumber="$STUD_MATRICULATION"

if [ -z "$lastName" ] || [ -z "$firstName" ] || [ -z "$matriculationNumber" ]; then
    echo "ERROR: set STUD_LASTNAME, STUD_FIRSTNAME, STUD_MATRICULATION"
    exit 1
fi

zipName="${studyProgram}_${lastName}_${firstName}_${matriculationNumber}.zip"
outputDir="$PWD/.submission"

if [ $# -ne 1 ]; then
    echo "ERROR: usage: ./create_zip.sh <pathToLab>"
    exit 1
fi

labPath="${1%/}" # remove trailing slash
if [ ! -d "$labPath" ]; then
    echo "ERROR: $labPath is not a folder"
    exit 1
fi

tempDir=$(mktemp -d) # build folder, nothing touches the original
trap 'rm -rf "$tempDir"' EXIT # cleanup when script ends

shopt -s nullglob # no match -> empty list instead of literal pattern
for taskPath in "$labPath"/LB*[0-9][0-9]; do # only task folders like LBEL00
    folderName=$(basename "$taskPath")
    taskNumber="${folderName: -2}" # 00
    labName="${folderName#LB}" # ELxx
    labName="${labName%??}" # EL
    mkdir "$tempDir/$taskNumber"

    # only source files + Makefile, no .exe / .o / images
    find "$taskPath" -maxdepth 1 -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -o -name "Makefile" \) -exec cp {} "$tempDir/$taskNumber/" \;

    if [ ! -f "$tempDir/$taskNumber/Makefile" ]; then
        echo "ERROR: $folderName has no Makefile"
        exit 1
    fi

    # exe names must be <lab><num><task>.exe (e.g. EL00a.exe)
    sed -i "s/^LAB *=.*/LAB = $labName/; s/^NUM *=.*/NUM = $taskNumber/" "$tempDir/$taskNumber/Makefile"

    # build check on exactly what gets zipped
    if ! make -C "$tempDir/$taskNumber" -s; then
        echo "ERROR: $folderName does not build"
        exit 1
    fi
    for sourceFile in "$tempDir/$taskNumber"/*.cpp; do
        exeName="$tempDir/$taskNumber/${labName}${taskNumber}$(basename "${sourceFile%.cpp}").exe"
        if [ ! -f "$exeName" ]; then
            echo "ERROR: $(basename "$exeName") was not built"
            exit 1
        fi
    done
    make -C "$tempDir/$taskNumber" -s clean # exe out again
    rm -f "$tempDir/$taskNumber"/*.o
done

if [ -z "$(ls -A "$tempDir")" ]; then
    echo "ERROR: no task folders (LBEL00, ...) in $labPath"
    exit 1
fi

mkdir -p "$outputDir"
rm -f "$outputDir/$zipName" # else zip adds to the old archive
(cd "$tempDir" && zip -r -X -q "$outputDir/$zipName" .) # cd -> 00, 01 on top level

echo "CREATED: $outputDir/$zipName"
unzip -l "$outputDir/$zipName"
