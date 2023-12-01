#!/bin/bash
one_thread_1k=`./genprimes 1000 1 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
two_thread_1k=`./genprimes 1000 2 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
five_thread_1k=`./genprimes 1000 5 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
ten_thread_1k=`./genprimes 1000 10 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`

one_thread_10k=`./genprimes 10000 1 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
two_thread_10k=`./genprimes 10000 2 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
five_thread_10k=`./genprimes 10000 5 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
ten_thread_10k=`./genprimes 10000 10 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`

# one_thread_100k=`./genprimes 100000 1 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# two_thread_100k=`./genprimes 100000 2 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# five_thread_100k=`./genprimes 100000 5 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# ten_thread_100k=`./genprimes 100000 10 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`


# one_thread_1mil=`./genprimes 1000000 1 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# two_thread_1mil=`./genprimes 1000000 2 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# five_thread_1mil=`./genprimes 1000000 5 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# ten_thread_1mil=`./genprimes 1000000 10 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`

# one_thread_10mil=`./genprimes 10000000 1 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# two_thread_10mil=`./genprimes 10000000 2 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# five_thread_10mil=`./genprimes 10000000 5 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`
# ten_thread_10mil=`./genprimes 10000000 10 | grep -Eo '[+-]?[0-9]+([.][0-9]+)?'`

printf "%6s %12s %12s %12s %12s %12s\n" " " "N" "N" "N" "N" "N" 
printf "%6s %12s %12s %12s %12s %12s\n" "threads" "1,000" "10,000" "100,000" "1,000,000" "10,000,000"
printf "%6s %12s %12s %12s %12s %12s\n" "1" $one_thread_1k $one_thread_10k $one_thread_100k $one_thread_1mil $one_thread_10mil
printf "%6s %12s %12s %12s %12s %12s\n" "2" $two_thread_1k $two_thread_10k $two_thread_100k $two_thread_1mil $two_thread_10mil
printf "%6s %12s %12s %12s %12s %12s\n" "5" $five_thread_1k $five_thread_10k $five_thread_100k $five_thread_1mil $five_thread_10mil
printf "%6s %12s %12s %12s %12s %12s\n" "10" $ten_thread_1k $ten_thread_10k $ten_thread_100k $ten_thread_1mil $ten_thread_10mil