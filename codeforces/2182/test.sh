#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage: ./test.sh <problem> [-t name]

Options:
  -t name   Run only the specified test (e.g. 1 to use tests/a/1.in and tests/a/1.out)
  -h        Show this help
EOF
}

if [ "$#" -lt 1 ]; then
    usage
    exit 1
fi

problem="$1"
shift

test_name=""
while getopts ":t:h" opt; do
    case "$opt" in
        t) test_name="$OPTARG" ;;
        h) usage; exit 0 ;;
        \?) usage; exit 1 ;;
    esac
done
shift $((OPTIND - 1))

bin="./${problem}.bin"
tests_dir="tests/${problem}"

if [ ! -x "$bin" ]; then
    echo "Binary '${bin}' not found. Run 'make ${problem}' first."
    exit 1
fi

if [ -n "$test_name" ]; then
    inputs=("${tests_dir}/${test_name}.in")
else
    # shellcheck disable=SC2206
    inputs=(${tests_dir}/*.in)
fi

if [ ${#inputs[@]} -eq 0 ] || [ ! -e "${inputs[0]}" ]; then
    echo "No test inputs found in ${tests_dir}."
    exit 1
fi

for f in "${inputs[@]}"; do
    if [ ! -e "$f" ]; then
        echo "Test '${test_name}' not found."
        exit 1
    fi

    base=${f%.in}
    echo "Running ${base##*/}..."
    expected="${base}.out"
    actual="${base}.out.tmp"

    "$bin" < "$f" > "$actual"
    if diff -q "$expected" "$actual" > /dev/null; then
        echo "OK"
    else
        echo "Mismatch for ${base##*/}:"
        # Fold long lines so single-line outputs stay readable.
        diff -u <(fold -sw 80 "$expected") <(fold -sw 80 "$actual") || true
    fi
done
