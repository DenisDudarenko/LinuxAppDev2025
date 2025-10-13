set pagination off

set $var = 0

break range.c:9 if (++$var >= 28 && $var <= 35)
command 1
    printf "@@@ %d %d %d %d\n", n, m, s, i
    continue
end

run -100 100 3
quit
