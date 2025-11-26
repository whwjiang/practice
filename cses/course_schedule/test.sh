#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR=$(cd -- "$(dirname -- "$0")" && pwd)
ROOT=$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel 2>/dev/null || realpath "$SCRIPT_DIR/../..")
exec "$ROOT/test.sh" "$@"

