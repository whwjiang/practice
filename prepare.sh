#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source_group> <problem_name>" >&2
    echo "Example: $0 usaco teamwork" >&2
    exit 1
fi

group="$1"
name="$2"

src_dir="$group/!template"
dst_dir="$group/$name"

if [ ! -d "$src_dir" ]; then
    echo "Source template not found: $src_dir" >&2
    exit 1
fi

if [ -e "$dst_dir" ]; then
    echo "Destination already exists: $dst_dir" >&2
    exit 1
fi

cp -R "$src_dir" "$dst_dir"
echo "Created $dst_dir from $src_dir"

if [[ "$group" == "usaco" ]]; then
    target_main="$dst_dir/main.cpp"
    if [[ -f "$target_main" ]]; then
        sed -i "s/xxx/$name/g" "$target_main"
        echo "Updated template placeholders in $target_main"
    else
        echo "Warning: Expected file not found: $target_main" >&2
    fi
fi
