

function download(){
    local URL=$1
    local MAX_DOWNLOAD_CNT=3
    local INDEX=0
    local DOWNLOADED_FLAG=0
    for((INDEX=0;INDEX<${MAX_DOWNLOAD_CNT};INDEX++))
    do
    {
        wget -q "${URL}"
        if [ $? -eq 0 ];then
            DOWNLOADED_FLAG=1
            INDEX=${MAX_DOWNLOAD_CNT}
        fi
    }
    done
    if [ ${DOWNLOADED_FLAG} -eq 1 ];then 
        echo "download ${URL} success!!!" >&2
        return 0
    else
        echo "download ${URL} failed!!!"  >&2
        return 1
    fi
}

function query_port(){
    local QUERY_PORT=$1
    netstat -anp | awk ' {print $4;}' | grep -w ${PORT}
    return $?
}

function config_port(){	
    local CONFIG_FILE=$1
    local LOCALIZED_PORT_TAG=0
    local NEW_PORT
    #以port开头，以:分隔，去除空格以取得数字
    PORT=`grep '^port' ${CONFIG_FILE}|awk -F ":" '{print $2;}'|tr -d ' '`
    #检查端口是否被占用i
    netstat -anp | awk ' {print $4;}' | grep -w ${PORT}|grep -P "ESTABLISHED|LISTEN"
    if [ $? -eq 1 ];then 
        echo "no need to localize the port,the port ${PORT} is avaliable!!!" >&2
        LOCALIZED_PORT_TAG=1
    else
        echo "Attention: the port ${PORT} is be used!!! " >&2
        while [ ${LOCALIZED_PORT_TAG} -ne 1 ]
        do
            read -s -p "please enter a port : " NEW_PORT   
            echo ${NEW_PORT}
            netstat -anp | awk ' {print $4;}' | grep -w ${NEW_PORT}|grep -P "ESTABLISHED|LISTEN"
            if [ $? -eq 0 ];then 
                 LOCALIZED_PORT_TAG=1
                 echo "localize the port ${NEW_PORT} success!!!" >&2
                 echo "port: ${NEW_PORT}" > ${CONFIG_FILE} >&2
            fi
        done
    fi 
    return $?     
}

#把data_path: ./data/dict.dat替换成./data/name_id_value_dict
function config_data_path(){
    local CONFIG_FILE=$1
    
    local DATA_PATH=`grep '^data_path' ${CONFIG_FILE}|awk -F ":" '{print $2;}'|tr -d ' '`
    local DATA_NAME=`basename ${DATA_PATH}`
    local LOCAL_DATA_NAME=""
    if [ -f DATA_PATH ];then 
        echo "no need to localize the data path."  >&2
    else
        cd `dirname ${DATA_PATH}`  >&2
        LOCAL_DATA_NAME=`ls`  #打印data下的data文件name_id_value_dict，默认data目录下只有一个文件
        cd ..
        pwd
        sed -i "s/${DATA_NAME}/${LOCAL_DATA_NAME}/g" ${CONFIG_FILE}
    fi
    return $?
}

#杀掉被测程序
function kill_mini_http_server(){
    local pid=`pgrep -f mini_http_server`
    if [ -n "${pid}" ]
    then
        kill -2 ${pid}
        if [ $? -ne 0 ]
        then
            echo "kill mini_http_server error" >&2
        fi
    fi
    return $?
}

#本地化port和data_path并启动被测程序
function localize_conf_and_start_server(){
    local MINI_HTTP_SERVER_PATH=$1
    cd  ${MINI_HTTP_SERVER_PATH}
    pwd
    config_port "./conf/server.conf" || error_check  "config port"
    config_data_path "./conf/server.conf" || error_check  "config data path"
    
    chmod u+x ./bin/mini_http_server
    nohup ./bin/mini_http_server & 
    error_check  "start mini_http_server"
    sleep 30
    cd ..    
    pwd
    return $?
}


function error_check(){ 
    if [ $? -ne 0 ];then
        echo "$1 error" >&2
        exit 1
    else
        echo "$1 success" >&2
    fi
}


#日志分析
function log_analyse() { 
    SERVER_LOG=$1
    RESULT_LOG=$2 
    #计算总花费时间
    local START_TIME=`head -3 ${SERVER_LOG} | tail -1 | awk '{print substr($3,0,8)}'` || error_check "got start time"
    START_TIME=`date +%s -d ${START_TIME}` || error_check "got start time as second" 
    local END_TIME=`tail -1 ${SERVER_LOG} | awk '{print substr($3,0,8)}'` || error_check "got end time"
    END_TIME=`date +%s -d ${END_TIME}`|| error_check "got end time as second"
    local TAKE_TIME=$((${END_TIME}-${START_TIME})) || error_check "calc take time as second"
    
    if [ ${TAKE_TIME} -lt 0 ];then
        echo "the time take is error!!!" >&2
        return 1
    fi

    #计算qps 每秒请求数
    echo "qps="$((`grep "NOTICE:" ${SERVER_LOG} | sed '1,2d' | sed '/^$/d' | wc -l` / ${TAKE_TIME} )) >> ${RESULT_LOG} || error_check "calculate qps"

    #计算value平均值，那些value字段为空的日志不参与统计
    echo "value_avg="`awk '{print $13}' ${SERVER_LOG} | sed '1,2d' | cut -d'=' -f2 | sed '/^$/d' | awk '{sum += $1};END { printf("%.3f", sum/NR)}'` >> ${RESULT_LOG} || error_check "calc value avg"
    
    #计算成功率，请求成功数在请求总数中的占比
    echo "succ_rate="`awk '{print $8}' ${SERVER_LOG} | sed '1,2d' | cut -d'=' -f2 | sed '/^$/d' | awk '{sum += $1};END {printf"%.3f",sum/NR}'` >> ${RESULT_LOG} || error_check "calc succ rate"
    
    #计算name总数（相同的name只计算一次）
    echo "name_num="`awk '{print $11}' ${SERVER_LOG} | sed '1,2d' | cut -d'=' -f2 | sed '/^$/d' | uniq | wc -l` >> ${RESULT_LOG} || error_check "calc name num"
}


