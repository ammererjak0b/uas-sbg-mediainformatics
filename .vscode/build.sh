#!/usr/bin/env bash
# walks up from the focused file's folder to the nearest Makefile and builds there
# no Makefile: compile the focused .cpp alone to <name>.exe (matches launch.json)
dir="$1"
file="$2"
while [ "$dir" != "/" ] && [ ! -f "$dir/Makefile" ]; do
    dir=$(dirname "$dir")
done

if [ -f "$dir/Makefile" ]; then
    CFLAGS="-g -Wall -Wextra" CXXFLAGS="-g -Wall -Wextra" make -C "$dir" # C + C++ makefiles, env is appended by +=
elif [[ "$file" == *.cpp ]]; then
    g++ -g -Wall -Wextra "$file" -o "${file%.cpp}.exe" # -g = debug symbols
else
    echo "no Makefile found and focused file is not a .cpp"
    exit 1
fi
