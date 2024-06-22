import os
import re

def rename_file(old_name):
    # Split the filename and extension
    base_name, extension = os.path.splitext(old_name)
    
    # Make sure the file is a PDF and starts with 'example' or 'exercise'
    if extension.lower() == '.pdf' and (base_name.startswith('example') or base_name.startswith('exercise')):
        
        # Perform the specific renaming based on the rules provided
        if base_name.startswith('example'):
            # Replace underscores with spaces and hyphens
            new_name = re.sub(r'_', ' ', base_name, count=1)
            new_name = re.sub(r'_', '-', new_name)
            new_name = new_name.capitalize()
        
        elif base_name.startswith('exercise'):
            # Split the parts of the filename
            parts = base_name.split('_')
            
            # Capitalize the first part and remove the underscores
            new_name = parts[0].capitalize()
            
            # Combine remaining parts, formatting as specified
            for part in parts[1:]:
                if part.isdigit() or part.isalpha():
                    new_name += part.capitalize()
                else:
                    new_name += '-' + part.capitalize()
        
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
