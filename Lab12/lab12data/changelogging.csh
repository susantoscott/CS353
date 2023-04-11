#!/bin/tcsh -f
#
# This file should be in the "lab12data" subdirectory of the directory where you have your Lab 12 executables.  To run it do:
#
#     chmod 755 ./lab12data/changelogging.csh
#     ./lab12data/changelogging.csh {SAYHELLO|LSUPDATE|UCASTAPP} {0|1}

set argc=0
foreach arg ( $argv )
   @ argc = $argc + 1
end
set num_args = $#argv

if ($num_args != 2) then
    echo "usage: ./lab12data/changelogging.csh {SAYHELLO|LSUPDATE|UCASTAPP} {0|1}"
    exit 1
endif

set key=$argv[1]
set val=$argv[2]

if ($key != "SAYHELLO" && $key != "LSUPDATE" && $key != "UCASTAPP") then
    echo "usage: ./lab12data/changelogging.csh {SAYHELLO|LSUPDATE|UCASTAPP} {0|1}"
    exit 1
endif

if ($val != 0 && $val != 1) then
    echo "usage: ./lab12data/changelogging.csh {SAYHELLO|LSUPDATE|UCASTAPP} {0|1}"
    exit 1
endif

foreach f (lab12data/*.ini)
    sed -i "1,$$s/${key}=[01]/${key}=${val}/" $f
end
echo "All instances of ${key} in lab12data/*.ini has been set to ${val}."
