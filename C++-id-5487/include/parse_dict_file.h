/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file parse_dict_file.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 13:08:12
 * @brief 读取词表文件，并解析每一行
 **/

#ifndef GOODCODER_ZHANGYUNJIANG_PARSE_DICT_FILE_H
#define GOODCODER_ZHANGYUNJIANG_PARSE_DICT_FILE_H

#include <string>
#include <vector>
#include "user_object.h"

namespace good_coder {

class ParseDictFile {
public:
    /**
     * @brief 构造函数
     **/
    ParseDictFile() {}

    /**
     * @brief 设置具体列的类型为int
     * @param [in] is_array : bool  是否为数组类型   
     * @return int
     * @retval 成功返回0，失败返回-1
     **/
    int add_element_type_int(bool is_array);

    /**
     * @brief 设置具体列的类型为float
     * @param [in] is_array : bool  是否为数组类型   
     * @return int
     * @retval 成功返回0，失败返回-1
     **/
    int add_element_type_float(bool is_array);

    /**
     * @brief 设置具体列的类型为char *
     * @param [in] is_array : bool  是否为数组类型   
     * @return int
     * @retval 成功返回0，失败返回-1
     **/
    int add_element_type_char(bool is_array);

    /**
     * @brief 设置具体列的类型为用户自定义类型
     * @param [in] type_name   :  string    类名称
     * @param [in] obj      : BaseObject*   用户自定义类型实例
     * @param [in] is_array : bool  是否为数组类型   
     * @return int
     * @retval 成功返回0，失败返回-1
     **/
    int add_element_type_user_define(const std::string &type_name, 
            BaseObject *obj, 
            bool is_array);

    /**
     * @brief parse每一行数据
     * @param [in] str : const std::string& 数据字符串col1\tcol2\tcol3...\tcoln
     * @return int
     * @retval 成功返回0，失败返回-1
     **/
    int parse_line(const std::string &str);

    /**
     * @brief 输出每一行数据的parse结果
     **/
    void output_line();

    /**
     * @brief 返回数组vec
     * @return vector<BaseObject *>
     * @retval 返回_vec
     **/
    const std::vector<BaseObject *>& get_vector();
    ~ParseDictFile();
private:
    std::vector<BaseObject *> _vec;
};
}

#endif  //GOODCODER_ZHANGYUNJIANG_PARSE_DICT_FILE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
