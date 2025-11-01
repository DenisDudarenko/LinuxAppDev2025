#!/bin/sh
set -eu

prog="$1"
tmp="$(mktemp)"
trap 'rm -f "$tmp"' EXIT

echo "some text" > "$tmp"

if ! command -v sha1sum >/dev/null 2>&1; then
  echo "sha1sum not found" >&2
  exit 1
fi

reference="$(sha1sum "$tmp" | awk '{print $1}')"
result="$(echo "SHA1 $tmp" | "$prog" \
  | tr -d '\r\n' \
  | grep -oE '[0-9a-f]{40,}' \
  | tail -n 1 \
  | awk '{print substr($0, length($0)-39)}')"

if [ "$reference" != "$result" ]; then
  echo "SHA1 test FAILED" >&2
  echo "file: $tmp" >&2
  echo "reference: $reference" >&2
  echo "result:    $result" >&2
  exit 1
fi

echo "SHA1 test OK"
