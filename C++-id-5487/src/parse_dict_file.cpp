/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file parse_dict_file.cpp
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 18:01:12
 * @brief 读取词表文件，并解析每一行
 *  
 **/

#include "parse_dict_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using std::vector;
using std::string;
using std::ifstream;

namespace good_coder {

int ParseDictFile::add_element_type_int(bool is_array) {
    try {
        if (is_array) {
            _vec.push_back(new ArrayObject("int", dynamic_cast<BaseObject *>(new IntObject())));
        } else {
            _vec.push_back(new IntObject());
        }
    }
    catch (std::bad_alloc& e) {
        fprintf(stderr, "ERROR:分配内存失败，type_int! %s", e.what());
        return -1;
    }
    return _vec[_vec.size() - 1] == NULL ? -1 : 0;
}

int ParseDictFile::add_element_type_float(bool is_array) {
    try {
        if (is_array) {
            _vec.push_back(new ArrayObject("float", dynamic_cast<BaseObject *>(new FloatObject())));
        } else {
            _vec.push_back(new FloatObject());
        }
    }
    catch (std::bad_alloc& e) {
        fprintf(stderr, "ERROR:分配内存失败，type_float! %s", e.what());
        return -1;
    }
    return _vec[_vec.size() - 1] == NULL ? -1 : 0;
}

int ParseDictFile::add_element_type_char(bool is_array) {
    try {
        if (is_array) {
            _vec.push_back(new ArrayObject("char*", dynamic_cast<BaseObject *>(new CharObject())));
        } else {
            _vec.push_back(new CharObject());
        }
    }
    catch (std::bad_alloc& e) {
        fprintf(stderr, "ERROR:分配内存失败，type_char! %s", e.what());
        return -1;
    }
    return _vec[_vec.size() - 1] == NULL ? -1 : 0;
}

int ParseDictFile::add_element_type_user_define(const string &type_name, 
        BaseObject *obj, 
        bool is_array) {
    try {
        if (is_array) {
            _vec.push_back(new ArrayObject(type_name, dynamic_cast<BaseObject *>(obj)));
        } else {
            _vec.push_back(dynamic_cast<BaseObject *>(obj));
        }
    }
    catch (std::bad_alloc& e) {
        fprintf(stderr, "ERROR:分配内存失败，type_user! %s", e.what());
        return -1;
    }
    return _vec[_vec.size() - 1] == NULL ? -1 : 0;
}

int ParseDictFile::parse_line(const string &str) {
    std::size_t pos = 0;
    std::size_t index = str.find_first_of("\t", pos);
    // parse每一个元素
    for (int i = 0; i < int(_vec.size()) - 1; ++i) {
        if (index == string::npos) {
            fprintf(stderr, "ERROR: parse此行失败，缺少元素!\n");
            return -1;
        }
        string sub_str = str.substr(pos, index - pos);
        if (_vec[i] == NULL || _vec[i]->parse(sub_str) == NULL) {
            fprintf(stderr, "ERROR: parse此行第 %d 列元素失败! \
                    读取下一行!\n", (i + 1));
            return -1;
        }
        pos = index + 1;
        index = str.find_first_of("\t", pos);
    }
    //最后一个元素
    string sub_str = "";
    if (int(index-pos)>0) { 
        sub_str = str.substr(pos, index - pos);
    } else {   
        sub_str = str.substr(pos);
    }
    sub_str.erase(sub_str.find_last_not_of(" \n\r") + 1);
    if (_vec[_vec.size() - 1] == NULL || _vec[_vec.size() - 1]->parse(sub_str) == NULL) {
        fprintf(stderr, "ERROR: parse此行第 %d 列元素失败! \
               读取下一行!\n", _vec.size());
        return -1;
    }
    return 0;

}

void ParseDictFile::output_line() {
    for (int i = 0; i < int(_vec.size()); ++i) {
        printf("column is %d\n", i);
        _vec[i]->output(false);
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
}

const vector<BaseObject *>& ParseDictFile::get_vector() {
    return _vec;
}

ParseDictFile::~ParseDictFile() {
    for (int i = 0; i < int(_vec.size()); ++i) {
        if (_vec[i] != NULL) {
            delete _vec[i];
            _vec[i] = NULL;
        }
    }
    _vec.clear();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
