/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file main.cpp
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 10:34:41
 * @brief main entrance file 
 *  
 **/
#include <iostream>
#include <vector>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include "base_object.h"
#include "user_object.h"
#include "parse_dict_file.h"

using std::string;
using good_coder::ParseDictFile;
using good_coder::BaseObject;
using good_coder::IntObject;
using good_coder::FloatObject;
using good_coder::CharObject;
using good_coder::ArrayObject;
using good_coder::TestObject;

int main(int argc, char * argv[]) {
    string path = "./data/input.data";
    int ch = 0;
    if ((ch = getopt(argc, argv, "hi:")) != -1) {
        switch (ch) {
            case 'h':
                printf("使用说明:\n\t-h\t使用说明\n");
                printf("\t-i\t指定输入文件，默认input.txt\n");
                return 0;
            case 'i':
                path = optarg;
                break;
            default:
                fprintf(stderr, "指令错误，请用-h查看使用说明\n");
                exit(1);
        }
    }
    ParseDictFile parser;
    // 用户定义每一列类型
    if (parser.add_element_type_int(false) < 0) {
        fprintf(stderr, "ERROR: 指定类型错误!\n");
        exit(1);
    }
    if (parser.add_element_type_float(false) < 0) {
        fprintf(stderr, "ERROR: 指定类型错误!\n");
        exit(1);
    }
    if (parser.add_element_type_char(false) < 0) {
        fprintf(stderr, "ERROR: 指定类型错误!\n");
        exit(1);
    }
    if (parser.add_element_type_int(true) < 0) {
        fprintf(stderr, "ERROR: 指定类型错误!\n");
        exit(1);
    }
    if (parser.add_element_type_user_define("TestObject", new TestObject(), false) < 0) {
        fprintf(stderr, "ERROR: 指定类型错误!\n");
        exit(1);
    }
    
    // 读取词表文件
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: 读取输入文件失败!\n");
        fprintf(stderr, "请用-h指令查看命令说明\n");
        exit(1);
    }

    const int MAX_LINE_SIZE = 1024;
    char line[MAX_LINE_SIZE] = {'\0'};
    while (fgets(line, MAX_LINE_SIZE - 1, fp) != NULL) {
        // parse一行
        int ret = parser.parse_line(line);
        if (ret == -1) {
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
            continue;
        }
        parser.output_line();
    }
    printf("Parse over! byebye\n");
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
