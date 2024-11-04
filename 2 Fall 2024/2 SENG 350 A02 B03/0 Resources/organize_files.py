import os
import re

def clean_filename(filename):
    # Replace '%20' with spaces and hyphens with spaces
    cleaned_name = filename.replace('%20', ' ').replace('-', ' ')
    
    # Add a hyphen after the module number (e.g., "M1 " -> "M1 - ")
    cleaned_name = re.sub(r'^(M\d+)\s', r'\1 - ', cleaned_name)
    
    # Replace multiple spaces with a single space
    cleaned_name = re.sub(r'\s+', ' ', cleaned_name).strip()
    
    return cleaned_name

def rename_files_in_directory(directory):
    for filename in os.listdir(directory):
        # Check if it's a file (skip directories)
        old_path = os.path.join(directory, filename)
        if os.path.isfile(old_path):
            # Generate new filename
            new_filename = clean_filename(filename)
            new_path = os.path.join(directory, new_filename)

            # Rename the file if the name has changed
            if old_path != new_path:
                os.rename(old_path, new_path)
                print(f'Renamed: "{filename}" -> "{new_filename}"')

# Define the target directory
directory = '.'  # current directory

# Run the renaming function
rename_files_in_directory(directory)

