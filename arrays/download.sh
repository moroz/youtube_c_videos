#!/usr/bin/env bash

# exit on errors
set -exuo pipefail

VERSION=3490000
YEAR=2025
URL="https://sqlite.com/$YEAR/sqlite-amalgamation-$VERSION.zip"

DIGEST="138b6922eb274c953c9d8f3249c39706ad3e40f3eef5d81bbeb73509b41f52c9"

filename="$(basename $URL)"
basename="${filename%.*}"
echo $filename

download_release() {
  mkdir -p tmp
  if [[ -f tmp/sqlite.zip ]]; then
    echo "tmp/sqlite.zip exists, skipping download..."
    return
  fi
  curl -o tmp/sqlite.zip "$URL"
}

verify_checksum() {
  echo "Verifying checksum for the downloaded file..."
  got="$(openssl dgst -sha3-256 -r tmp/sqlite.zip | awk '{print $1}')"
  if [[ "$got" != "$DIGEST" ]]; then
    echo "Checksum of downloaded file does not match the hardcoded SHA3-256 digest, please delete tmp/sqlite.zip and retry!"
    exit 1
  fi
}

unzip_release() {
  echo "Unpacking release to $(pwd)..."
  unzip -o -d tmp/ tmp/sqlite.zip
  cp tmp/${basename}/sqlite3.{c,h} .
  rm -rf tmp/
}

if [[ -f sqlite3.h ]] && [[ -f sqlite3.c ]]; then
  exit 0
fi

download_release
verify_checksum
unzip_release
