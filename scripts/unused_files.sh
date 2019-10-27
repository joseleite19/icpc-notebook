all_files=$(find code -type f)
used_files=$(grep -Fio "$all_files" notebook.tex)
echo "$all_files" | grep -Fv "$used_files"

