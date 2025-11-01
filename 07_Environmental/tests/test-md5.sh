#!/bin/sh
set -eu

prog="$1"
tmp="$(mktemp)"
trap 'rm -f "$tmp"' EXIT

echo "hello world" > "$tmp"

if ! command -v md5sum >/dev/null 2>&1; then
  echo "md5sum not found" >&2
  exit 1
fi

reference="$(md5sum "$tmp" | awk '{print $1}')"
result="$(echo "MD5 $tmp" | "$prog" \
  | tr -d '\r\n' \
  | grep -oE '[0-9a-f]{32,}' \
  | tail -n 1 \
  | awk '{print substr($0, length($0)-31)}')"

if [ "$reference" != "$result" ]; then
  echo "MD5 test FAILED" >&2
  echo "file: $tmp" >&2
  echo "reference: $reference" >&2
  echo "result:    $result" >&2
  exit 1
fi

echo "MD5 test OK"
