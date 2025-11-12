#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage: ./test.sh [-t name]

Options:
  -t name   Run only the specified test (e.g. 1 to use tests/1.in and tests/1.out)
  -h        Show this help
EOF
}

test_name=""
while getopts ":t:h" opt; do
    case "$opt" in
        t) test_name="$OPTARG" ;;
        h) usage; exit 0 ;;
        \?) usage; exit 1 ;;
    esac
done
shift $((OPTIND - 1))

if [ ! -x main ]; then
    echo "Binary 'main' not found. Run 'make' first."
    exit 1
fi

if [ -n "$test_name" ]; then
    inputs=("tests/${test_name}.in")
else
    # shellcheck disable=SC2206
    inputs=(tests/*.in)
fi

if [ ${#inputs[@]} -eq 0 ] || [ ! -e "${inputs[0]}" ]; then
    echo "No test inputs found."
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

    ./main < "$f" > "$actual"
    if diff -q "$expected" "$actual" > /dev/null; then
        echo "OK"
    else
        echo "Mismatch for ${base##*/}:"
        # Fold long lines so single-line outputs stay readable.
        diff -u <(fold -sw 80 "$expected") <(fold -sw 80 "$actual") || true
    fi
done
