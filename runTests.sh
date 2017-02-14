#!/bin/bash
#ficheiro que corre todos os testes automaticamente no pc
set -e
#TESTDIR="./randomTests"
TESTDIR="tests"
CURR=`pwd`

#compila
echo -ne "\e[34mCompiling... "
g++ -Wall -O3 -Ofast -std=c++11 ./artic.cpp && echo -e "\e[32mok" || exit 1

#corre os testes:
cd $TESTDIR

if [ -z "$1" ]; then
echo
echo -ne "\e[34m"
echo "Running tests... "
tput sgr0
for i in $( ls | grep ".in" );
        do
                TEST=${i%.in}
                echo -ne "\e[36m$TEST.in: "
                tput sgr0
                ./../a.out < "$TEST.in" > out
                diff "$TEST.out" out | colordiff && echo -e "\e[32mok" || exit 1
        done
fi;

#corre para obter informação de profiling
if [ -n "$1" ]; then
  echo
  echo -ne "\e[34m"
  echo "\$Generating Profiling Information... "
  tput sgr0
  for i in $( ls | grep ".in" );
          do
                  TEST=${i%.in}
                  echo -e "\e[36m$TEST.in: "
                  tput sgr0
                  echo -n "N: "
                  head -n 1 "$TEST.in" | cut -f 1 -d" "
                  echo -n "L: "
                  head -n 1 "$TEST.in" | cut -f 2 -d" "
                  cnt=$(perf stat -x, -e instructions:u ./../a.out < "$TEST.in" 2>&1 >/dev/null)
                  echo -n "I: "
                  echo $cnt | cut -d"," -f 1
          done
fi;
