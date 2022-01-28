#!/bin/sh
I=1
while IFS=% read -r source roots; do
        res=$(echo $source | ./quad)
        res=$(echo "$res" | tail -n +2)
        if [ x"$roots" != x"$res" ]; then
                echo TEST $I '('$source')' FAILED: expexted "$roots", got "$res"
        else
                echo TEST $I PASSED
        fi
        I=$((I+1))
done <<END
        1 2 1%-1.000
        1 4 3%-3.000 -1.000
        1 2 f%Incorrect input
END

