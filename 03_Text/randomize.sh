#!/bin/sh

timeout="0.2"

if [ -n "$1" ]; then
    timeout="$1"
fi

tput clear

{
    x=0
    y=0
    while IFS= read -r str; do
        printf '%s' "$str" | LC_ALL=en_US.UTF-8 grep -o . | \
        while IFS= read -r c; do
            printf '%d:%d:%s\n' "$x" "$y" "$c"
            x=$((x+1))
		done

        x=0
        y=$((y+1))
	done		             
} |
shuf |
{
    while IFS=':' read -r y x c; do
        tput cup $((x + 10)) $((y + 10))
        printf '%s' "$c"
        sleep $timeout
    done

    row=$(tput lines)
    col=$(tput cols)
    tput cup $((row-1)) $((col-1))
}