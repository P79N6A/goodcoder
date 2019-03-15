#!/bin/bash

##! @TODO: test function is_file_existed 
##! @AUTHOR: xiafei  
##! @VERSION: 1.0 
##! @IN: $1 => existedfile.txt | notexistedfile.txt
##! @OUT: existedfile.txt => echo "existedfile.txt is existed!" return 0
##! @OUT: notexistedfile.txt =>echo "error: existedfile.txt is not existed!" and eixt 1

function test_func_is_file_existed()
{
    source ./lib/checker.sh
    is_file_existed existedfile.txt
    is_file_existed notexistedfile.txt
}


function test_download()
{
	 source ./checker.sh
	 download "ftp://cq01-ocean-824.epc.baidu.com/home/qacmc/good_coder/shell/mini_tester/mini_http_server/mini_http_server.tar.gz"
	 download "ftp://cq01-ocean-824.epc.baidu.com/home/qacmc/good_coder/shell/mini_tester/query_list/query_list.md5" 
	 download "ftp://cq01-ocean-824.epc.baidu.com/home/qacmc/good_coder/shell/mini_tester/query_list/query_list" 
}
