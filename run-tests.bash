run_test() {
	diff -u "$1" <( ./natsort < "$2" ) && return
	echo "Test failed for input file '$2'"
	exit 1
}

run_test sorted-dates     test-dates
run_test sorted-fractions test-fractions
run_test sorted-words     test-words

echo "All tests passed"
exit 0
