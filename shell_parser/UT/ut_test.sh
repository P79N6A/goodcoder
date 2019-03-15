
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

source ./tester.conf
source ./tools.sh

echo `date`
function test_download(){
    echo "===============test_download start===============" > ut_result.log
    #测试正确的url
    download "${MUT_PATH}"
    #测试错误的url
    download "http:/www.baidu.com/a.txt" 
    rm -rf  mini_http_server*
    echo "===============test_download end===============" >> ut_result.log
}

function test_kill_mini_http_server(){
    echo "===============test_kill_mini_http_server start===============" >> ut_result.log
    #before
    download "${MUT_PATH}"
    MINI_HTTP_SERVER=$(basename "${MUT_PATH}")
    tar -xzvf "${MINI_HTTP_SERVER}" || error_check "unzip ${MINI_HTTP_SERVER}"
    MINI_HTTP_SERVER_PATH=$(basename "${MUT_PATH}" .tar.gz)
    #cd  "${MINI_HTTP_SERVER_PATH}"
    pwd
    localize_conf_and_start_server "${MINI_HTTP_SERVER_PATH}"
    #cd -
    #test
    local pid=`pgrep -f mini_http_server`
    if [ -n "${pid}" ];then
        echo  "===============test_kill_mini_http_server failed===============" >> ut_result.log
    else
        echo  "===============test_kill_mini_http_server success===============" >> ut_result.log
    fi
    rm -rf mini_http_server*  
    echo "===============test_kill_mini_http_server end===============" >> ut_result.log
}


function test_localize_conf_and_start_server(){
    echo "===============test_localize_conf_and_start_server start===============" >> ut_result.log
    #before
    download "${MUT_PATH}"
    MINI_HTTP_SERVER=$(basename ${MUT_PATH})
    tar -xzvf ${MINI_HTTP_SERVER} || error_check "unzip ${MINI_HTTP_SERVER}"
    MINI_HTTP_SERVER_PATH=$(basename ${MUT_PATH} .tar.gz)

    #test
    localize_conf_and_start_server "${MINI_HTTP_SERVER_PATH}"
    if [ $? -eq 0 ];then
        echo  "===============test_localize_conf_and_start_server success===============" >> ut_result.log
    else
        echo  "===============test_localize_conf_and_start_server failed===============" >> ut_result.log
    fi
    rm -rf mini_http_server*  
    echo "===============test_localize_conf_and_start_server end===============" >> ut_result.log
}


function test_log_analyse() { 
    
    echo  "===============test_log_analyse start===============" >> ut_result.log
    echo  "===============test_log_analyse with take time right===============" >> ut_result.log
    log_analyse "./server.log" "./ut_result_rightdata.log"
    if [ $? -ne 0 ];then
        echo  "===============test_log_analyse failed===============" >> ut_result.log
    else
        diff "./ut_right_log_analyse_result.log" "./ut_result_rightdata.log"
        if [ $? -eq 0 ];then
            echo  "===============test_log_analyse success===============" >> ut_result.log
        else
            echo  "===============test_log_analyse failed===============" >> ut_result.log
        fi
    fi
    echo  "===============test_log_analyse with take time error===============" >> ut_result.log
    log_analyse "./server_taketime_error.log" "./ut_result_errordata.log"
    if [ $? -ne 1 ];then
        echo  "===============test_log_analyse success===============" >> ut_result.log
    else
        echo  "===============test_log_analyse failed===============" >> ut_result.log
    fi
    echo  "===============test_log_analyse end===============" >> ut_result.log
        
} 
echo  "=============== unit test start===============" > ut_result.log
test_download
test_kill_mini_http_server
test_localize_conf_and_start_server
test_log_analyse
echo  "===============unit test end===============" >> ut_result.log
