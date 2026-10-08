#!/usr/bin/env bash
set -euo pipefail

if [[ $# != 3 ]]; then
    echo "usage: $0 BINARY INPUT EXPECTED" >&2
    exit 2
fi

binary="$1"
input="$2"
expected="$3"

actual="${TEST_TMPDIR}/actual.out"
"$binary" < "$input" > "$actual"

diff -ub "$expected" "$actual"
