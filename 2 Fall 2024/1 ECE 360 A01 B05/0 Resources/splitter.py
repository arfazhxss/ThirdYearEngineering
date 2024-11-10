import subprocess
import sys
import os

# Default PDF path
pdf_path = "/Users/arfaz/Desktop/ThirdYearEngineering/2 Fall 2024/1 ECE 360 A01 B05/0 Resources/Modern Control Engineering.pdf"

# Function to split PDF using Ghostscript
def split_pdf(start_page, end_page, output_path="output_split.pdf"):
    try:
        command = [
            "gs",
            "-sDEVICE=pdfwrite",
            "-dNOPAUSE",
            "-dBATCH",
            "-dSAFER",
            f"-dFirstPage={start_page}",
            f"-dLastPage={end_page}",
            f"-sOutputFile={output_path}",
            pdf_path
        ]
        subprocess.run(command, check=True)
        print(f"PDF split successfully: {output_path}")
    except subprocess.CalledProcessError as e:
        print("Error splitting PDF:", e)

if __name__ == "__main__":
    # Check if the correct number of arguments is provided
    if len(sys.argv) != 3:
        print("Usage: python3 split_pdf.py <start_page> <end_page>")
    else:
        start_page = sys.argv[1]
        end_page = sys.argv[2]
        
        # Default output path
        output_path = os.path.join(os.getcwd(), f"split_{start_page}_to_{end_page}.pdf")
        
        # Call the function to split PDF
        split_pdf(start_page, end_page, output_path)

