#!/bin/tcsh -f
#
# This is a sub-tcsh-script run from lab13data/tmux-lab13a.csh for node :12010

set prog = "./lab13a"

${prog} lab13data/lab13-12010.ini
echo "[ (6) type <Ctrl+d> to proceed to display log files ]"; cat
more lab13data/*.log
