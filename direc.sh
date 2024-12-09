#!/bin/bash

# Function to list the directory structure recursively
list_structure() {
  local dir="$1"
  local indent="$2"
  local depth="$3"
  local output_file="$4"

  # Stop recursion if the depth is greater than 10
  if [ "$depth" -gt 10 ]; then
    return
  fi

  # List and sort the files in the current directory, excluding dotfiles
  find "$dir" -maxdepth 1 -type f ! -name '.*' | sort | while IFS= read -r file; do
    echo "${indent}├── $(basename "$file")" >> "$output_file"
  done

  # List and sort the subdirectories, excluding dotfiles and node_modules
  find "$dir" -maxdepth 1 -type d ! -path "$dir" | sort | while IFS= read -r subdir; do
    if [[ "$(basename "$subdir")" != .* && "$(basename "$subdir")" != "node_modules" ]]; then
      echo "${indent}├── $(basename "$subdir")/" >> "$output_file"
      list_structure "$subdir" "${indent}│   " $((depth + 1)) "$output_file"
    fi
  done
}

# Determine the directory to list
if [ $# -eq 0 ]; then
  target_dir="."
else
  target_dir="$1"
fi

# Output file
output_file="README.md"

# Remove any existing .md files in the current directory
find . -maxdepth 1 -name '*.md' -type f -delete

# Create or clear the output file
: > "$output_file"

# Write the Markdown header and code block start
echo "# Directory Structure" >> "$output_file"
echo "" >> "$output_file"
echo '```' >> "$output_file"

# Start listing from the target directory with no initial indentation and a depth of 0
list_structure "$target_dir" "" 0 "$output_file"

# Write the code block end
echo '```' >> "$output_file"

echo "Directory structure has been saved to $output_file"