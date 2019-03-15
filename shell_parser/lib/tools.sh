source ./lib/checker.sh

##! @TODO: use wget to download file
##! @AUTHOR: xiafei  
##! @VERSION: 1.0 
##! @IN: $1 => url
##! @OUT: 0 => success; 1 => failure 

function download()
{	
	check_arg_nums $# 1 #here the argument's number must be 1 
	local URL=$1
	wget -q ${URL} 
	return $?
}


function config_port()
{
	check_arg_nums $# 1
	local CONFIG_FILE=$1
	#以port开头，以:分隔，去除空格以取得数字
        CMD1=cat ${CONFIG_FILE}|grep '^port'|awk -F ":" '{print $2;}'|tr -d ' '
        PORT=${CMD1}
        CONFIG_SUCCESS=0
	NEW_PORT
	while [ ${CONFIG_SUCCESS} -ne 1 ]
	do
	        echo "Please enter the port you want to use,and Attention the default is ${PORT}:" >&2
		read ${NEW_PORT}
		#如果${NEW_PORT}为空，就说明用户没有输入，那就用默认的端口
		if [ -z ${NEW_PORT} ]
	        then
	    	    NEW_PORT=${PORT}
                fi
	        #检查端口是否被占用
	        check_port ${NEW_PORT}
	        #如果执行后返回的结果是0，则说明该端口已被占用
		if [ $? -eq 0 ]
	        then
	            echo "Attention: the port ${NEW_PORT} is be used!!! " >&2
	        else
	    	    #将（新）端口写入配置文件中,配置文件中port：和端口有一个空格
	            echo "port: ${NEW_PORT}" > ${CONFIG_FILE}
	            CONFIG_SUCCESS=1
	        fi
	done
	return $?	 		
}
