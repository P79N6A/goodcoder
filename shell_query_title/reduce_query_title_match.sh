#!/bin/bash
set -o pipefail

reduce_pid=$$
tmp_site_file="tmp_site_file_${reduce_pid}.txt"

[ -e ${tmp_site_file} ] && rm -rf ${tmp_site_file}
cat > ${tmp_site_file}
if [[ `wc -l ${tmp_site_file} | awk '{print $1}'` -eq 0 ]]
then
    exit 0
fi

awk '{a[$1]++} END {for(k in a) print k"\t"a[k]}' ${tmp_site_file}
ret=$?
rm -rf ${tmp_site_file}
[[ ${ret} -ne 0 ]] && exit 1

exit 0
