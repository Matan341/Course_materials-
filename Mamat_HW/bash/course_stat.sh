#!/bin/bash
chmod +x course_stat.sh

if (( $# != 1 )); then
    echo "Wrong number of arguments" >&2
    exit 1
fi
if [[ ! -f "$1.txt" ]]; then
    echo "Course not found" >&2
    exit 1
fi
DIR="$1_stats"
if [[ ! -d "$DIR" ]]; then
    mkdir $DIR
else
    rm -r $DIR
    mkdir $DIR
fi
awk '{ print $2 }' $1.txt > grades.txt
sed -i -e 's/grade//g' grades.txt
mv grades.txt $DIR
rm grades.txt-e
cp calc_statistics.c $DIR
cd $DIR
gcc -c -g -Wall calc_statistics.c
gcc -o prog.exe calc_statistics.o
./prog.exe > course_statistics.txt
rm calc_statistics.c calc_statistics.o prog.exe
cat course_statistics.txt
