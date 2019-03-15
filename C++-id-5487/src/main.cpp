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
                printf("ʹ��˵��:\n\t-h\tʹ��˵��\n");
                printf("\t-i\tָ�������ļ���Ĭ��input.txt\n");
                return 0;
            case 'i':
                path = optarg;
                break;
            default:
                fprintf(stderr, "ָ���������-h�鿴ʹ��˵��\n");
                exit(1);
        }
    }
    ParseDictFile parser;
    // �û�����ÿһ������
    if (parser.add_element_type_int(false) < 0) {
        fprintf(stderr, "ERROR: ָ�����ʹ���!\n");
        exit(1);
    }
    if (parser.add_element_type_float(false) < 0) {
        fprintf(stderr, "ERROR: ָ�����ʹ���!\n");
        exit(1);
    }
    if (parser.add_element_type_char(false) < 0) {
        fprintf(stderr, "ERROR: ָ�����ʹ���!\n");
        exit(1);
    }
    if (parser.add_element_type_int(true) < 0) {
        fprintf(stderr, "ERROR: ָ�����ʹ���!\n");
        exit(1);
    }
    if (parser.add_element_type_user_define("TestObject", new TestObject(), false) < 0) {
        fprintf(stderr, "ERROR: ָ�����ʹ���!\n");
        exit(1);
    }
    
    // ��ȡ�ʱ��ļ�
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: ��ȡ�����ļ�ʧ��!\n");
        fprintf(stderr, "����-hָ��鿴����˵��\n");
        exit(1);
    }

    const int MAX_LINE_SIZE = 1024;
    char line[MAX_LINE_SIZE] = {'\0'};
    while (fgets(line, MAX_LINE_SIZE - 1, fp) != NULL) {
        // parseһ��
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
