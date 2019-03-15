#!/bin/bash

##! @TODO: check if the file is existed 
##! @AUTHOR: xiafei  
##! @VERSION: 1.0 
##! @IN: $1 => filepath 
##! @OUT: 0 => success; 1 => failure 

function is_file_existed()
{	
	FILEPATH=$1
	if [ -f ${FILEPATH} ]
	then 
		echo " ${FILEPATH} is existed!"
		return 0
	else
		echo "error: ${FILEPATH} is not existed!" >&2
		exit 1
	fi
}


##! @TODO: to check if the argument number is enough
##! @AUTHOR: xiafei 
##! @VERSION: 1.0 
##! @IN: $1 => REAL_NUM ;$2 => NEED_NUM 
##! @OUT: 0 => success; 1 => failure 

function check_arg_nums()
{
	local REAL_NUM=$1
	local NEED_NUM=$2
	if [ ${REAL_NUM} -ne ${NEED_NUM} ]
	then
		echo "error: we need ${NEED_NUM} arguments,now only ${REAL_NUM} " >&2
		exit 1
	fi
}


##! @TODO: to check if download error
##! @AUTHOR: xiafei 
##! @VERSION: 1.0 
##! @IN: 
##! @OUT: 0 => success; 1 => failure 

function check_download()
{	
	check_arg_nums $# 1
	echo "error: download $1 failed. " >&2
	exit 1
}

##! @TODO: to check if the port is used
##! @AUTHOR: xiafei 
##! @VERSION: 1.0  
##! @IN:port
##! @OUT: the query result,if 0 not used,else used

function check_port()
{
	check_arg_nums $# 1
	local PORT=$1
	netstat -anp|awk '/^tcp/ {print $4;}'|grep ${PORT} >&2
	return $?
}


##! @TODO: to check if the file's md5
##! @AUTHOR: xiafei 
##! @VERSION: 1.0  
##! @IN:2 files
##! @OUT: 0 the file is newest,else  not 
function check_md5()
{
    a=`cat $1|md5sum|cut -d ' ' -f1` 
    b=`cat $2|cut -d ' ' -f1` 
    if [ $a == $b ];then 
        echo "The query_list is newest!"
    else
        exit 1
    fi
}









