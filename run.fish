#!/bin/fish

echo "running on $argv[1]"
set fish_trace 1

set map (ls $argv[1]/*.map)

for solG in (ls $argv[1]/*.solG)
    set sol (string replace ".solG" ".sol" $solG)
    set cli (string replace ".solG" ".cli" $solG)

    time ./tourists $map $cli
    diff $sol $solG

    echo 

end

# for i in (seq (ls $argv[1]/*.solG | wc -l))
#     set num (printf "%02d" (math "$i+$argv[2]"))
#     ./tourists $argv[1]/Enunciado_mapa.map $argv[1]/Enunciado_$num.cli
#     diff $argv[1]/Enunciado_$num.sol $argv[1]/Enunciado_$num.solG
# end
