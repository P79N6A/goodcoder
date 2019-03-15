#!/bin/sh
#/***************************************************************************
# * 
# * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
# * 
# **************************************************************************/

# 测试数据url-title文件位置
URL_TITLE_PATH="ftp://cp01-qa-junheng2-qa160.cp01.baidu.com/home/work/maj/cm-shell/test-data/url-title/part-*"
# querylist文件位置
QUERY_LIST_PATH="ftp://cp01-qa-junheng2-qa160.cp01.baidu.com/home/work/maj/cm-shell/test-data/query-set/"
QUERY_LIST_NAME="query_set_s1_25000.txt"
QUERY_LIST_MD5="query_set_s1_25000.txt.md5"

#切词工具的文件位置
SEG_BASIC_PATH="ftp://cq01-antispam-test01.cq01.baidu.com/home/work/shell_test/seg_basic"
PUNCWORDS_DICT_PATH="ftp://cq01-antispam-test01.cq01.baidu.com/home/work/shell_test/puncwords_dict.txt"
WORDDICT_PATH="ftp://cq01-antispam-test01.cq01.baidu.com/home/work/shell_test/worddict.tar.gz"


BASE_PATH=`pwd`
TOOL_PATH="${BASE_PATH}/tool/"
UT_PATH="${BASE_PATH}/urltitle/"
QL_PATH="${BASE_PATH}/querylist/"

# 输出数据文件位置
OUTPUT_DATA_PATH="${BASE_PATH}/output/"

HADOOP_HOME="/home/work/zyj/hadoop-v2-rank-click/hadoop"
HADOOP_FS_CMD="$HADOOP_HOME/bin/hadoop fs"
HADOOP_CMD="$HADOOP_HOME/bin/hadoop "
HDFS_INPUT_PATH="hdfs://szwg-rank-hdfs.dmop.baidu.com:54310/app/ps/rank/ubs/rank-click/rank_qa/zyj/input"
HDFS_TOOL_PATH="hdfs://szwg-rank-hdfs.dmop.baidu.com:54310/app/ps/rank/ubs/rank-click/rank_qa/zyj/tool"
HDFS_OUTPUT_PATH="hdfs://szwg-rank-hdfs.dmop.baidu.com:54310/app/ps/rank/ubs/rank-click/rank_qa/zyj/output"

