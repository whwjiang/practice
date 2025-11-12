#!/usr/bin/env bash
set -euo pipefail

if [ ! -x main ]; then
    echo "Binary 'main' not found. Run 'make' first."
    exit 1
fi

for f in tests/*.in; do
    base=${f%.in}
    echo "Running ${base##*/}..."
    ./main < "$f" > "${base}.out.tmp"
    if diff -q "${base}.out" "${base}.out.tmp" > /dev/null; then
        echo "OK"
    else
        echo "Mismatch for ${base##*/}:"
        diff -u "${base}.out" "${base}.out.tmp" || true
    fi
done
