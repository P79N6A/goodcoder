/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file base_object.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 11:31:48
 * @brief 所有build_in以及用户定义类型的基类，提供parse和output功能
 **/

#ifndef GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H 
#define GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H

#include <string>

namespace good_coder{

class BaseObject {
public:
    BaseObject() {}
    
    /**
     * @brief parse函数，将string输入parse成具体类型
     * @param [in] str : string& 用于parse的字符串
     * @return BaseObject *
     * @retval 返回this，失败返回NULL
     **/
    virtual BaseObject *parse(const std::string &str) = 0;

    /**
     * @brief output函数，将具体类型转换成string输出
     * @param [in] for_array : bool 判断是否用于在数组类型内输出
     **/
    virtual void output(bool for_array) = 0;
    
    /**
     * @brief 生成一个新的实例
     * @return BaseObject *
     * @retval 返回BaseObject实例
     **/
    virtual BaseObject *new_instance() = 0;
    virtual ~BaseObject() {}
};

}

#endif // GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
