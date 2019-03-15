#!/bin/sh
#/***************************************************************************
# * 
# * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
# * 
# **************************************************************************/

#/**
 # * @file query_title_match.sh
 # * @author zhangyunjiang@baidu.com
 # * @date 2015/12/01/ 13:15:20
 # * @version $Revision: 1.0 $ 
 # * @brief
 # *
 # **/

source ./conf_query_title_match.sh

###################################
# Brief:
#   Usage of query_title_match
# Arguments:
#   None
# Returns:
#   none
###################################
function Usage(){
    echo  -e "Usage: ${0} [-v] [-h]"
    echo "-----------------------------------------------------------------------------------"
    echo  -e "      -v          :   show version"
    echo  -e "      -h          :   show Usage"
    echo  -e "                  :   if it's null,start match query_title"
    echo "-----------------------------------------------------------------------------------"
}

###################################
# Brief:
#   Show the version of query_title_match
# Arguments:
#   None
# Returns:
#   none
###################################
function Version(){
    echo -e "${0}\nversion:  1.0\nauthor:   zhangyunjiang@baidu.com" 
}

###################################
# Brief:
#   get_options from command line.
# Arguments:
#   args
# Returns:
#   none
###################################
function get_options(){
    while getopts hv flag
    do
        case "${flag}" in
            h)  Usage
                exit 0
                ;;
            v)  Version
                exit 0
                ;;
            *)  echo "INPUT error options"
                Usage
                exit 0
                ;;
        esac
    done
}

###################################
# Brief:
#   init_env
# Arguments:
#   none
# Returns:
#   none
###################################
function init_env(){
    echo "init_env.."
    if [ -d ${TOOL_PATH} ];then
        rm -rf ${TOOL_PATH}
    fi
    mkdir -p ${URL_TITLE_PATH}
    if [ -d ${URL_TITLE_PATH} ];then
        rm -rf ${URL_TITLE_PATH}
    fi
    mkdir -p ${URL_TITLE_PATH}
}

###################################
# Brief:
#   init_env
# Arguments:
#   none
# Returns:
#   none
###################################
function init_env(){
    echo "init_env.."
    if [ -d ${TOOL_PATH} ];then
        rm -rf ${TOOL_PATH}
    fi
    mkdir -p ${TOOL_PATH}
    if [ -d ${UT_PATH} ];then
        rm -rf ${UT_PATH}
    fi
    mkdir -p ${UT_PATH}
    if [ -d ${QL_PATH} ];then
        rm -rf ${QL_PATH}
    fi
    mkdir -p ${QL_PATH}
}



function download_tool(){
    echo "download_tool"
    wget -q -P ${UT_PATH} ${URL_TITLE_PATH}
    ret=$? 
    [[ ${ret} -ne 0 ]] && echo "download url_titile Fail" && return -1
    wget -q -P ${TOOL_PATH} ${SEG_BASIC_PATH}
    ret=$?
    [[ ${ret} -ne 0 ]] && echo "download seg_basic Fail" && return -1
    wget -q -P  ${TOOL_PATH} ${PUNCWORDS_DICT_PATH}
    ret=$?
    [[ ${ret} -ne 0 ]] && echo "download puncwords_dict Fail" && return -1
    wget -q -P  ${TOOL_PATH} ${WORDDICT_PATH}
    ret=$?
    [[ ${ret} -ne 0 ]] && echo "download words_dict Fail" && return -1
        
    wget  -q -P  ${QL_PATH} ${QUERY_LIST_PATH}/${QUERY_LIST_NAME}
    ret=$?
    [[ ${ret} -ne 0 ]] && echo "download query_list Fail" && return -1
    wget  -q -P  ${QL_PATH} ${QUERY_LIST_PATH}/${QUERY_LIST_MD5}
    ret=$?
    [[ ${ret} -ne 0 ]] && echo "download query_list_md5 Fail" && return -1

}

function verify(){
    cd  ${QL_PATH}
    md5sum -c ${QUERY_LIST_MD5}
    ret=$?
    cd -
    [[ ${ret} -ne 0 ]] && return 1
    return 0
    #md5=`echo ${md5}|cut -d " " -f 1`
}

function preprocess_query_list(){
    local ret=0
    chmod +x ${TOOL_PATH}/seg_basic
    cd ${TOOL_PATH}
    iconv -f UTF-8 -t GBK ${QL_PATH}/${QUERY_LIST_NAME}> ${QL_PATH}/processed.txt 
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1
    cd -
    return 0
}

function do_mapreduce(){
    local ret=0
    #${HADOOP_FS_CMD} -rmr ${HDFS_INPUT_PATH}
    ${HADOOP_FS_CMD} -rmr ${HDFS_OUTPUT_PATH}
    #${HADOOP_FS_CMD} -mkdir ${HDFS_INPUT_PATH}
    #${HADOOP_FS_CMD} -put ${UT_PATH}/part-* ${HDFS_INPUT_PATH}
    #${HADOOP_FS_CMD} -mkdir ${HDFS_TOOL_PATH}
    #${HADOOP_FS_CMD} -put ${TOOL_PATH}/worddict.tar.gz ${HDFS_TOOL_PATH}
    
    echo ${HADOOP_CMD} 
    echo ${HDFS_TOOL_PATH}
    ${HADOOP_CMD} streaming -D mapred.job.name=click-adjust-new.schedule_all.zyj_filter \
        -D mapred.job.queue.name=rank-click \
        -D mapred.job.priority=NORMAL \
        -D mapred.job.map.capacity=200 \
        -D mapred.map.tasks=100 \
        -D mapred.job.reduce.capacity=100 \
        -D mapred.reduce.tasks=10 \
        -mapper "sh map_query_title_match.sh" \
        -reducer "sh reduce_query_title_match.sh" \
        -input ${HDFS_INPUT_PATH} \
        -output ${HDFS_OUTPUT_PATH} \
        -file ./map_query_title_match.sh \
        -file ./reduce_query_title_match.sh \
        -file ${QL_PATH}/processed.txt\
        -file ${TOOL_PATH}/seg_basic\
        -file ${TOOL_PATH}/puncwords_dict.txt\
        -cacheArchive ${HDFS_TOOL_PATH}/worddict.tar.gz#worddict
    # &>./hadoop.display_filter.log
    ret=$?
    return ${ret}
}
function postprocess_output(){
    #echo "postprocess_output"
    local ret=0
    ${HADOOP_CMD} fs -getmerge ${HDFS_OUTPUT_PATH} ${OUTPUT_DATA_PATH}/result
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1   
    cat  ${OUTPUT_DATA_PATH}/result| sort -T ./ -n -r -k 2 >ranksite_tmp
    ret=$?
    [[ ${ret} -ne 0 ]] && return 1  
    head -100 ranksite_tmp> ${OUTPUT_DATA_PATH}/top100site
    ret=$?
    rm -rf ${OUTPUT_DATA_PATH}/result ranksite_tmp
    return 0
}

function Main(){
    get_options "$@"
    init_env
    download_tool
    verify
    ret=$?
    [[ ${ret} -ne 0 ]]&&return -1
    echo "verify success"
    preprocess_query_list
    ret=$?
    [[ ${ret} -ne 0 ]]&&return -1
    echo "preprocess_query_list success"
    do_mapreduce
    ret=$?
    [[ ${ret} -ne 0 ]]&&return -1
    echo "do_mapreduce success" 
    postprocess_output
    ret=$?
    [[ ${ret} -ne 0 ]]&&return -1
    echo "postprocess_output success" 
}

Main "$@"

