# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_test.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 19:56:27 by paalexan          #+#    #+#              #
#    Updated: 2024/12/30 20:00:07 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST_PROGRAMS_DIR="tests"
TEST_CASES_DIR="tests/test_cases"
EXPECTED_DIR="tests/expected"

# Check if test programs directory exists
if [ ! -d "$TEST_PROGRAMS_DIR" ]; then
    echo "❌ Error: Test programs directory '$TEST_PROGRAMS_DIR' not found!"
    exit 1
fi

# Check if test cases directory exists
if [ ! -d "$TEST_CASES_DIR" ]; then
    echo "❌ Error: Test cases directory '$TEST_CASES_DIR' not found!"
    exit 1
fi

# Clean up previous expected outputs
echo "Cleaning up old expected outputs..."
rm -rf "$EXPECTED_DIR"
mkdir -p "$EXPECTED_DIR"

# Iterate over test cases
for test_case in "$TEST_CASES_DIR"/*; do
    test_case_name=$(basename "$test_case")
    echo "Testing file: $test_case_name"

    # Iterate over compiled test programs (skip directories and non-executables)
    for test_program in "$TEST_PROGRAMS_DIR"/test_*; do
        if [ ! -x "$test_program" ] || [ -d "$test_program" ]; then
            continue
        fi

        program_name=$(basename "$test_program")
        #echo "Running $program_name on $test_case_name"

        # Generate expected output
        output_file="$EXPECTED_DIR/${test_case_name}_${program_name}.out"
        "$test_program" "$test_case" > "$output_file"

        # Check execution success
        if [ $? -eq 0 ]; then
            echo "✅ $program_name $test_case_name passed!"
        else
            echo "❌ $program_name $test_case_name failed!"
        fi
    done
done

echo "Testing completed!"
