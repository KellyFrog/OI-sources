#!/bin/bash

cppName=$1

RED='\e[1;31m' # 红
GREEN='\e[1;32m' # 绿
YELLOW='\e[1;33m' # 黄
BLUE='\e[1;34m' # 蓝
PINK='\e[1;35m' # 粉红
CLEAR='\e[0m' # 清除颜色

if [ -f $cppName.cpp ]; then

echo g++ -o $cppName.exe $cppName.cpp -std=c++17

if [ `g++ -o $cppName.exe $cppName.cpp -std=c++17` ]; then

exit 1

else

exeName=$cppName.exe
inputList=`ls *.in`

for inFile in $inputList
do

fileName=${inFile%%.in}
outFile=$fileName.out
ansFile=$fileName.ans
logFile=$fileName.log
diffFile=$fileName.diff

echo "=======Testing testcase $fileName.in/.ans======"
\time -o timelog -f "%Us,%Mkb" ./$exeName < $inFile > $outFile 2>$logFile

stat=`cat timelog`

diff -Z $outFile $ansFile > /dev/null

if [ -s $diffFile ]; then
echo -e ${RED}wrong answer${CLEAR}, $stat
echo -----$inFile-----
cat $inFile
echo -----stdout-----
cat $outFile
echo -----stderr-----
cat $logFile

echo -----diff-------
diff -Z $outFile $ansFile
else
echo -e ${GREEN}ok accepted${CLEAR}, $stat
fi # diff -Z $outFile $ansFile

done

fi #g++ -o $cppName.exe $cppName.cpp -std=c++17

else
echo File $cppName.cpp does not exsist!
fi # -f $cppName.cpp
