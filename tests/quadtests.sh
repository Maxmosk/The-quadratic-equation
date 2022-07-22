#!/bin/sh
I=1
while IFS=% read -r source roots; do
        res=$(echo $source | $1)
        res=$(echo "$res" | tail -n +2)
        if [ x"$roots" != x"$res" ]; then
                echo TEST $I '('$source')' FAILED: expexted "$roots", got "$res"
        else
                echo TEST $I PASSED
        fi
        I=$((I+1))
done <<END
        1       2       1%-1.000
        1       4       3%-3.000 -1.000
        1       2       f%Incorrect input
        0       1       -1%1.000
        -1      -1      -1%No solutions
        0       0       1%No solutions
        0       0       0%All real numbers
        1       0       NAN%Error domain. One of the parameters is infinity or not a number
        INF     0       0%Error domain. One of the parameters is infinity or not a number
        9999999 999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 9999999%Error range. In the process of calculations, an infinitely large number was obtained
END

