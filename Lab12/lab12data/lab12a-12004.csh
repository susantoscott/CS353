#!/bin/tcsh -f
#
# This is a sub-tcsh-script run from lab12data/tmux-lab12a.csh for node :12004

set prog = "./lab12a"
while (! -x ${prog})
    echo "Waiting for ${prog} to get compiled..."
    sleep 1
end

${prog} lab12data/lab12-12004.ini
