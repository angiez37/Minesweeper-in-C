#!/bin/bash
#
# Test Script adopoted from script provided Sam Scott @ McMaster University 2024
#

declare -i tc=0
declare -i fails=0

############################################
# Run a single test. Runs a given command 
# to check the return value, stdout, and stderr
#
# GLOBALS: tc, fails
# PARAMS: $1 = command
#         $2 = input file name
#         $3 = expected std output file name
#         $4 = expected std error file name
#
# Assumes return value should be 0 if the
# std error file is empty. Otherwise it 
# should be 1.
#
# OUTPUTS: An pass/fail report showing the
# difference between expected and actual
# output on a failure (diff command)
############################################
test() {
    tc=tc+1

    local COMMAND=$1
    local INP=$2
    local EX_OUT=$3
    local EX_ERR=$4 

    EX_RET=1
    if [[ $(cat $EX_ERR) = "" ]]; then
        EX_RET=0
    fi
    $COMMAND < $INP > test_out.txt 2> test_err.txt
    RET=$?
    if [[ $RET != $EX_RET ]]; then
        echo "TC $tc Failed"
        echo "Returned $RET"
        echo "-----------"
        fails=$fails+1
        return
    fi
    DIFF=$(diff test_out.txt $EX_OUT)
    if [[ $DIFF != '' ]]; then
        echo "TC $tc Failed Standard Output"
        echo "$DIFF"
        echo "-----------"
        fails=$fails+1
        return
    fi
    DIFF=$(diff test_err.txt $EX_ERR)
    if [[ $DIFF != '' ]]; then
        echo "TC $tc Failed Standard Error"
        echo "$DIFF"
        echo "-----------"
        fails=$fails+1
        return
    fi

    echo "TC $tc Passed"
}

test './score_test' 'tests/logic_test_input1.txt' 'tests/score_test_output1.txt' 'tests/score_test_empty.txt'
test './score_test' 'tests/logic_test_input2.txt' 'tests/score_test_output2.txt' 'tests/score_test_empty.txt'

# clean up
rm test_err.txt test_out.txt

# return code
exit $fails