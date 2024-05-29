#!/bin/bash

# MIT License

# Copyright (c) 2024 Arfaz Hussain <https://www.arfazhxss.ca/>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Usage
# bash pdfall.sh

dir=$(realpath $(dirname "$0"))
mkdir -p "$dir/IMGs"

viewjpeg=$(find /opt/homebrew/Cellar/ghostscript -name viewjpeg.ps 2>/dev/null)
printf "Current directory: {\e[33m${dir}\e[0m}\n"

shopt -s nullglob
for filepath in "$dir"/*.{jpg,jpeg,png,bmp,tiff}
do
    in=$(basename "$filepath")
    out="${in%.*}.pdf"
    dirmein="(${filepath// /\\ })"

    printf "Converting \e[31m${in}\e[0m into \e[34m${out}\e[0m\n"

    gs -q -dNOSAFER -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=${out} $viewjpeg -c "${dirmein}" viewJPEG showpage
    mv "$filepath" "$dir/IMGs/"
done