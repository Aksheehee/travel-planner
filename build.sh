#!/usr/bin/env bash
set -euo pipefail

echo "== Building Travel Planner (GTK3) in MSYS2 MINGW64 =="
# Check pkg-config
if ! command -v pkg-config >/dev/null 2>&1; then
  echo "[ERROR] pkg-config not found."
  echo "Install: pacman -S mingw-w64-x86_64-pkg-config"
  exit 1
fi

# Check GTK3
if ! pkg-config --exists gtk+-3.0; then
  echo "[ERROR] gtk+-3.0 not found."
  echo "Install: pacman -S mingw-w64-x86_64-gtk3"
  exit 1
fi

echo "[INFO] pkg-config and GTK3 found."
CFLAGS="$(pkg-config --cflags gtk+-3.0)"
LIBS="$(pkg-config --libs gtk+-3.0)"

echo "[INFO] Compiling..."
gcc *.c -o travel_planner.exe $CFLAGS $LIBS

echo "[SUCCESS] Built travel_planner.exe"
