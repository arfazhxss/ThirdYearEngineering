import os
import re

def rename_files(directory):
    for root, _, files in os.walk(directory):
        for filename in files:
            new_filename = filename
            # Replace spaces with hyphens and adjust letter cases
            new_filename = re.sub(r'(\d) (\d{3}) ([A-Za-z])', r'\1-\2 \3', new_filename)
            new_filename = re.sub(r'(\d) (\d+\w) ([A-Za-z])', r'\1-\2\3', new_filename)
            new_filename = re.sub(r'(\d)\.(\d+)\.(\w)', lambda m: f"{m.group(1)}.{m.group(2)}{m.group(3).upper()}", new_filename)
            new_filename = new_filename.replace(" Answer", "")

            if new_filename != filename:
                old_path = os.path.join(root, filename)
                new_path = os.path.join(root, new_filename)
                os.rename(old_path, new_path)
                print(f'Renamed: {old_path} to {new_path}')

# Run the function in the current directory
rename_files('.')

