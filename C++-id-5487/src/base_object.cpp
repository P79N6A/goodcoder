/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file base_object.cpp
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:47:30
 * @brief ����build_in�Լ��û��������͵Ļ��࣬�ṩparse��output����
 *  
 **/

#include "base_object.h"

namespace good_coder {

BaseObject *BaseObject::parse(const std::string &str) {
    return NULL;
}

void BaseObject::output(bool is_array) {}

BaseObject *BaseObject::new_instance() {
    return NULL;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
