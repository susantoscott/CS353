#!/bin/tcsh -f
#
# If you have to run your programs on a shared server such as viterbi-scf1.usc.edu,
#     you must not use 12000 as your base port number and you must use a base port
#     number that was assigned to you at the beginning of the semester.  If you don't
#     know your base port number, please contact the instructor.
#
# This file should be in the "lab13data" subdirectory of the directory where you have your Lab 13 executables.  To run it do:
#
#         chmod 755 ./lab13data/change-ports.csh
#         ./lab13data/change-ports.csh BASEPORT
#
# Please note that this command can only be run against the ORIGINAL configuration files!
#     If you made a mistake the first time you ran it, you must wipe out the content of the
#     entire "lab13data" subdirectory by running the following command before running this command again:
#
#         tar xvf lab13data.tar.gz

set lab=lab13
set dir=${lab}data

set argc=0
foreach arg ( $argv )
   @ argc = $argc + 1
end
set num_args = $#argv

if ($num_args != 1) then
    echo "usage: ./${dir}/change-ports.csh BASEPORT"
    exit 1
endif

set baseport=$argv[1]

set rc = `echo ${baseport} | bc`
if ($rc == 0) then
    echo "usage: ./${dir}/change-ports.csh BASEPORT"
    echo "       BASEPORT must be a number"
    exit 1
endif

if (${baseport} < 10000 || ${baseport} > 64000) then
    echo "usage: ./${dir}/change-ports.csh BASEPORT"
    echo "       BASEPORT must be >= 10000 and <= 64000"
    exit 1
endif

set rc = `grep 12000 ${dir}/*.ini | wc -l`
if ($rc == 0) then
    echo "Looks like you have already run this program once before."
    echo "You must wipe out the content of the entire "\""${dir}"\"" subdirectory (by running the following command) before you can run this program again:"
    echo "       tar xvf ${dir}.tar.gz"
    exit 1
endif

foreach f (${dir}/${lab}*.ini ${dir}/${lab}*.csh ${dir}/${lab}*.txt ${dir}/tmux-*.txt)
    set port=${baseport}
    sed -i "1,$$s/12000/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12002/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12004/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12006/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12008/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12010/${port}/g" $f
    @ port = $port + 2
    sed -i "1,$$s/12012/${port}/g" $f
end

set port=${baseport}
mv ${dir}/${lab}-12000.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12000.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12000.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12002.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12002.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12002.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12004.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12004.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12004.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12006.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12006.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12006.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12008.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12008.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12008.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12010.ini ${dir}/${lab}-${port}.ini
mv ${dir}/${lab}a-12010.csh ${dir}/${lab}a-${port}.csh
mv ${dir}/${lab}b-12010.csh ${dir}/${lab}b-${port}.csh

@ port = $port + 2
mv ${dir}/${lab}-12012.ini ${dir}/${lab}-${port}.ini

echo "Done.  (Please be reminded that this program can only be run against the original configuration files.)"
