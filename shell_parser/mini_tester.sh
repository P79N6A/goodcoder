#!/bin/bash 

#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
# Author: chenxiafei
# Date: 2015/12/28
# Brief:
#   The Test of Mini_http_server Test Framework
# Globals:
# Arguments:
# Returns:
#   succ:0
#   fail:1


#1.开关

set +x #set -o xtrace
set -e #set -o errexit
set -u #set -o nonuset
set -o pipefail


#2.source 文件

source ./tools.sh
source ./tester.conf


#3.常量

readonly VERSION=1.0.0 #版本号
readonly LOCAL_IP=`hostname -i`


#4.变量

CUR_PATH=${PWD}
TMP_PATH="tmp"
MINI_HTTP_SERVER_PATH=""
CONFIG_FILE=""
PORT=""

#5.函数

#Usage
function usage(){
    echo -e "简易测试框架\n" >&2
    echo -e "用法：sh $0 [参数]\n" >&2 #$0 为mini_tester.sh
    echo -e "-h\t\t打印帮助信息\n" >&2
    echo -e "-v\t\t打印版本信息\n" >&2
    echo -e "-c\t\t配置文件的路径，默认为tester.conf\n" >&2
    echo -e "例如：\n" >&2
    echo -e "sh $0 -c config.conf\n" >&2
}


while getopts c:hv OPT;do
    case $OPT in 
        h) 
            usage 
            exit 0 
            ;;
        v) 
            echo -e "minitester.sh version： ${VERSION}\n" >&2
            exit 0
            ;;
        c)
            CONFIG_FILE=${OPTARG}
            ;;
        \?)
            usage
            exit 1
            ;;
    esac
done


#读取配置

if [[ ! -f ${CONFIG_FILE} ]] || [[ ! -n "${CONFIG_FILE}" ]];then
    echo -e "The conf file is not existed!!!" >&2
else
    source ${CONFIG_FILE}
fi


#构建临时目录

rm -rf ${TMP_PATH} || error_check "clear up dir ${TMP_PATH}"
mkdir -p ${TMP_PATH} || error_check "make dir ${TMP_PATH}"


cd ${TMP_PATH} || error_check "enter ${TMP_PATH}"


#下载相关文件

download "${MUT_PATH}" || error_check "download mini_http_server.tar.gz"
download "${QUERY_LIST_PATH}*" ||error_check "download query list"


#解压mini_http_server.tar.gz

MINI_HTTP_SERVER=$(basename ${MUT_PATH})
tar -xzvf ${MINI_HTTP_SERVER} || error_check "unzip ${MINI_HTTP_SERVER}"
MINI_HTTP_SERVER_PATH=$(basename ${MUT_PATH} .tar.gz)
cd ${MINI_HTTP_SERVER_PATH}
MINI_HTTP_SERVER_PATH=`pwd`
cd -

#对query list进行MD5校验

md5sum --check ${QUERY_LIST_MD5} || error_check "query list md5 check"


#kill mini_server

kill_mini_http_server || error_check "kill mini http server"


#清除response 和 result目录并新建该目录

rm -rf ${RESPONSE_PATH} || error_check "clear up dir ${RESPONSE_PATH}"
mkdir -p ${RESPONSE_PATH} || error_check "make dir ${RESPONSE_PATH}"


#替换mini_server配置并启动

localize_conf_and_start_server "${MINI_HTTP_SERVER_PATH}"|| error_check "localize conf and start server"


#向被测程序发送请求词表

while read LINE
do
    LINE="http://${LOCAL_IP}:${PORT}${LINE}"
    curl ${LINE} >> ${RESPONSE_PATH}/response_result.log || error_check "curl query list"
    #sleep 2
done<${QUERY_LIST_NAME}


#kill mini_server

kill_mini_http_server || error_check "kill mini http server"


#分析日志
cd ..

log_analyse "${RESPONSE_PATH}/server.log" "${LOG_RESULT_PATH}/result.log"  || error_check "analyse log"
echo "done the mini_tester,bye."
