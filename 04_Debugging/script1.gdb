set pagination off

break range.c:9 if i % 5 == 0
command 1
    printf "@@@ %d %d %d %d\n", n, m, s, i
    continue
end

run 1 12
quit
