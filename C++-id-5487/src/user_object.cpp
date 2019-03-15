/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file user_object.cpp
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 16:32:12
 * @brief 继承基类，各种build_in类型和用户自定义类型
 *  
 **/

#include "user_object.h"
using std::string;
using std::vector;

namespace good_coder {

IntObject::IntObject() {
    _value = 0;
}

IntObject *IntObject::parse(const string &str) {
    if (str.empty()) {
        fprintf(stderr, "ERROR: Int类型parse失败，输入为空!\n");
        return NULL;
    }
    char *err = NULL;
    _value = strtol(str.c_str(), &err, 10);
    return (0 == strlen(err)) ? this : NULL;
}

void IntObject::output(bool for_array) {
    if (for_array) {
        printf("%d, ", _value);
    }
    else {
        printf("Type is int, value is %d\n", _value);
    }
}

int IntObject::get_value() {
    return _value;
}

IntObject *IntObject::new_instance() {
    return new IntObject();
}

FloatObject::FloatObject() {
    _value = 0.0;
}

FloatObject *FloatObject::parse(const string &str) {
    if (str.empty()) {
        fprintf(stderr, "ERROR: Float类型parse失败，输入为空!\n");
        return NULL;
    }
    char *err = NULL;
    _value = strtod(str.c_str(), &err);
    return (0 == strlen(err)) ? this : NULL;

}

void FloatObject::output(bool for_array) {
    if (for_array) {
        printf("%f, ", _value);
    }
    else {
        printf("Type is float, value is %f\n", _value);
    }
}

float FloatObject::get_value() {
    return _value;
}

FloatObject *FloatObject::new_instance() {
    return new FloatObject();
}

CharObject::CharObject() {
    _value = NULL;
}

CharObject *CharObject::parse(const std::string &str) {
    if (str.empty()) {
        fprintf(stderr, "ERROR: char*类型parse失败，输入为空!\n");
        return NULL;
    }
    _value = new char[str.size() + 1];
    if (_value == NULL) {
        fprintf(stderr, "ERROR: char*分配内存失败!\n");
        return NULL;
    }
    int res = snprintf(_value, str.size() + 1, "%s", str.c_str());
    return this;
}

void CharObject::output(bool for_array) {
    if (for_array) {
        printf("%s, ", _value);
    }
    else {
        printf("Type is char *, value is %s\n", _value);
    }
}

char *CharObject::get_value() {
    return _value;
}

CharObject *CharObject::new_instance() {
    return new CharObject();
}

CharObject::~CharObject() {
    delete[] _value;
    _value = NULL;
}

ArrayObject::ArrayObject(std::string type_name, BaseObject *obj) {
    _type_name = type_name;
    _obj = obj;
}

ArrayObject *ArrayObject::parse(const string &str) {
    if (str.empty()) {
        fprintf(stderr, "ERROR: 数组类型parse失败，输入为空!\n");
        return NULL;
    }
    // 先清空数组
    clear();
    // parse数组长度
    std::size_t pos = str.find(":");
    if (string::npos == pos) {
        fprintf(stderr, "ERROR: 数组类型长度parse失败，未找到:!\n");
        return NULL;
    }
    char *err = NULL;
    int array_len = strtol(str.substr(0, pos).c_str(), &err, 10);
    if (0 != strlen(err)) {
        fprintf(stderr, "ERROR: 数组类型parse长度失败，格式不符!\n");
        return NULL;
    }
    if (array_len <= 0) {
        fprintf(stderr, "ERROR: 数组类型parse长度失败，长度 <= 0!\n");
        return NULL;
    }
    // 根据长度和类型初始化数组
    init_array(array_len);
    // parse每一个元素
    pos = pos + 1;
    std::size_t index = str.find_first_of(",", pos);
    for (int i = 0; i < _vec.size() - 1; ++i) {
        if (string::npos == index) {
            fprintf(stderr, "ERROR: 数组类型parse失败，元素缺失!\n");
            return NULL;
        }
        string sub_str = str.substr(pos, index - pos);
        if (_vec[i]->parse(sub_str) == NULL) {
            fprintf(stderr, "ERROR: 数组类型parse失败，元素parse失败!\n");
            return NULL;
        }
        pos = index + 1;
        index = str.find_first_of(",", pos);
    }
    // 最后一个元素
    if (index - pos > 0) {
        string sub_str = str.substr(pos, index - pos);
        if (_vec[_vec.size() - 1]->parse(sub_str) == NULL) {
            fprintf(stderr, "ERROR: 数组类型parse失败，元素parse失败!\n");
            return NULL;
        }
    }
    return this;
}

void ArrayObject::output(bool for_array) {
    printf("Type is array<%s>, length is %d, value is ", _type_name.c_str(), _vec.size());
    for (int i = 0; i < _vec.size(); ++i) {
        _vec[i]->output(true);
    }
    printf("\n");
}

int ArrayObject::init_array(int array_len) {
    for (int i = 0; i < array_len; ++i) {
        _vec.push_back(_obj->new_instance());
    }
    return 0;
}

const vector<BaseObject *>& ArrayObject::get_value() {
    return _vec;
}

ArrayObject *ArrayObject::new_instance() {
    return new ArrayObject(_type_name, _obj);
}

void ArrayObject::clear() {
    for (int i = 0; i < _vec.size(); ++i) {
        if (_vec[i] != NULL) {
            delete _vec[i];
            _vec[i] = NULL;
        }
    }
    _vec.clear();
}

ArrayObject::~ArrayObject() {
    clear();
}

TestObject::TestObject() {
    _type = "";
    _value = 0;
}

TestObject *TestObject::parse(const string &str) {
    if (str.empty()) {
        fprintf(stderr, "ERROR: 自定义类型parse失败，输入为空!\n");
        return NULL;
    }
    // parse type
    std::size_t pos = str.find_first_of("_", 0);
    if (pos == string::npos) {
        fprintf(stderr, "ERROR: 自定义类型parse失败，缺少_!\n");
        return NULL;
    }
    _type = str.substr(0, pos);
    // parse value
    string sub_str = str.substr(pos + 1);
    if (sub_str.empty()) {
        fprintf(stderr, "ERROR: 自定义类型parse失败，缺失type!\n");
        return NULL;
    }
    char *err = NULL;
    _value = strtol(sub_str.c_str(), &err, 10);
    if (0 != strlen(err)) {
        fprintf(stderr, "ERROR: 自定义类型parse失败，value格式不符!\n");
        return NULL;
    }
    return this;
}

void TestObject::output(bool for_array) {
    printf("Type is TestObject, value is %s_%d\n", _type.c_str(), _value);
}

string TestObject::get_type() {
    return _type;
}

int TestObject::get_value() {
    return _value;
}

TestObject *TestObject::new_instance() {
    return new TestObject();
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
