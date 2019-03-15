#!/bin/bash

set -o pipefail
map_pid=$$

url_title_set="url_title_set_${map_pid}.txt"
url_title_processed="url_title_processed_${map_pid}.txt"

cat > ${url_title_set}
if [[ `wc -l ${url_title_set} | awk '{print $1}'` -eq 0 ]]
then
    exit 0
fi

function preprocess_url_title(){
    [[ $# -ne 2 ]]&& echo "Usage: preprocess_url_title <url_title_set> <url_title_processed>"&& return 1
    local ret=0
    chmod +x ./seg_basic
    local url_title_set=$1
    local url_title_processed=$2
    local tmp_url_file="./tmp_url_set.${map_pid}"
    local tmp_title_file="./tmp_title_set.${map_pid}"

    awk -F"\t" '{print $1}' ${url_title_set}|awk -F"http://" '{split($2,array,"/"); print array[1]}' >${tmp_url_file}
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1
    awk -F"\t" '{print $2}' ${url_title_set}|./seg_basic | awk -F"\t" '{print $NF}'|sed 's/,/ /g'>${tmp_title_file}
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1
    paste ${tmp_url_file} ${tmp_title_file} >${url_title_processed}
    rm -rf ${tmp_url_file} ${tmp_title_file}
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1
    
    cat processed.txt|./seg_basic | awk -F"\t" '{print $NF}'|sed 's/,/ /g' >new_processed.txt
    return 0   
}

preprocess_url_title ${url_title_set} ${url_title_processed}
ret=$?
[[ ${ret} -ne 0 ]] && exit 1
rm -rf ${url_title_set}

#url_title_processed="url_title_processed_14686.txt"
while read query
do
    if [[ ${query} == "" ]]
    then
        continue
    fi
    query_array=(${query[@]})
    len=${#query_array[@]}
    map_cmd=""
    for((i=0; i<${len};i++))
    do
        word=" ${query_array[i]} "
        map_cmd="${map_cmd} | grep \"${word}\""
    done
    map_cmd="cat ${url_title_processed} ${map_cmd}"
    #echo $map_cmd
    match_url=`eval "${map_cmd}"`
    ret=$?
    #echo ${query}
    if [[ ${ret} -eq 0 && ${match_url} != "" ]]
    then
        echo -n "${match_url}" |awk '{print $1}'
        ret=$?
        [[ ${ret} -ne 0 ]] && exit 1
    fi
done < new_processed.txt
rm -rf ${url_title_processed}
exit 0
