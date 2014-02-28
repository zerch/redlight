#!/bin/bash
set -e
#set -x

printf "\n--Pre-Cleaning\n"
make clean

printf "\n--Make ex19\n"
make ex19

printf "\n--Running ex19\n"
./ex19 a l s e w n l a a e e w w e w a a a a a  a a a a a a q d l e w n s 

printf "\n--Done testing\n"
printf "\n--Cleaning up\n"

make clean


