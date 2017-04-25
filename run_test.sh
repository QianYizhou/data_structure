#TEST_BIN=$1
#TEST_BIN="./build/ut_foot_module -g math -v -c"
#TEST_BIN="./build/ut_foot_module -g bezier -v -c"
#TEST_BIN="./build/ut_foot_module -g matrix_api -v -c"
#TEST_BIN="./build/ut_foot_module -g user_mapping -v -c"
TEST_BIN="./build/ut_foot_module -g simu_plan -v -c"
if [[ "" != $1 ]]; then
    TEST_BIN=$1
fi
TEST_DIR=./build/
LCOV=lcov
GENHTML=genhtml
GENDESC=gendesc
GENPNG=genpng

echo "test_bin: "$TEST_BIN

echo
echo '*'
echo '* Test case : output index.html'
echo '*'
echo
rm -f $TEST_DIR/*.gcda
rm -f $TEST_DIR/*.gcno
rm -f *.info
$LCOV --zerocounters --directory $TEST_DIR
make clean all > /dev/null
#make all > /dev/null
./$TEST_BIN
$LCOV --capture --directory $TEST_DIR --output-file trace_noargs.info --test-name test_noargs > /dev/null
echo 'test_output DONE'

echo
echo '*'
echo '* Generating HTML output'
echo '*'
echo
$GENHTML trace_noargs.info \
    --output-directory output --title "Basic example" > /dev/null
echo
echo '*'
echo '* See '`pwd`/output/index.html
echo '*'
echo
