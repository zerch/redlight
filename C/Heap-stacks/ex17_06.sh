#!/bin/bash
set -e

printf "I>Pre-Cleaning\n"
make clean

function test_ex17 {
    printf "\n--Compiling ex17\n"
    make ex17_05
    printf "\n--Creating Databse\n"
    ./ex17_05 data.dat c 512 100
    printf "\n--Setting a few rows\n"
    ./ex17_05 data.dat s 1 alin pav@email.com engineer 771234
    ./ex17_05 data.dat s 5 george pos@email.com medic 555234
    ./ex17_05 data.dat s 99 chris les@email.com journalist 771234
    ./ex17_05 data.dat s 66 john leb@email.com engineer 612314
    printf "\n--Listing database\n"
    ./ex17_05 data.dat l
    printf "\n--Getting entry at id 5\n"
    ./ex17_05 data.dat g 5
    printf "\n--Deleting entry at id 1\n"
    ./ex17_05 data.dat d 1
    printf "\n--Listing database\n"
    ./ex17_05 data.dat l
    printf "\n--Search for 'chris'\n"
    ./ex17_05 data.dat f chris
    printf "\n--Search for engineers\n"
    ./ex17_05 data.dat p engineer
    printf "\n--Search by number 555234\n"
    ./ex17_05 data.dat n 555234
    printf "\n--Test Complete.\n"
    printf "\n--Cleaning up.\n"
    make clean
    dats=`ls | grep -e ".dat"`
    ( test -n "$dats" && ( printf "\n--Cleaning databases\n"; rm -vf $dats ) )
    return 0
}

test_ex17
