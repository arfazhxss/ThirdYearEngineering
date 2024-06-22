import os
import re

# THIS IS SCRIPT 2
def rename_file(old_name):
    # Split the filename and extension
    base_name, extension = os.path.splitext(old_name)
    
    # Make sure the file is a PDF and starts with 'Exercise'
    if extension.lower() == '.pdf' and base_name.startswith('Exercise'):
        # Use regex to find the parts of the filename
        match = re.match(r'Exercise(\d+)([A-Z])Answer', base_name)
        if match:
            num_part = match.group(1)
            letter_part = match.group(2)
            
            # Format the new name
            if len(num_part) == 4:
                new_name = f'Exercise {num_part[0]}-{num_part[1:]}{letter_part}'
            elif len(num_part) == 3:
                new_name = f'Exercise {num_part[0]}-{num_part[1:]}{letter_part}'
            elif len(num_part) == 2:
                new_name = f'Exercise {num_part[0]}-{num_part[1]}{letter_part}'
            elif len(num_part) == 1:
                new_name = f'Exercise {num_part}-{letter_part}'
            else:
                new_name = old_name
            
            # Add the extension back to the filename
            new_name += extension
            
            return new_name
    
    return old_name

def rename_files_recursively(directory):
    for root, dirs, files in os.walk(directory):
        for filename in files:
            old_path = os.path.join(root, filename)
            new_filename = rename_file(filename)
            new_path = os.path.join(root, new_filename)
            
            if old_path != new_path:
                print(f'Renaming: {old_path} -> {new_path}')
                os.rename(old_path, new_path)

# Get the directory of the current script
current_directory = os.path.dirname(os.path.abspath(__file__))

# Call the function to rename files
rename_files_recursively(current_directory)
