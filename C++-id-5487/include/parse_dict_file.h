/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file parse_dict_file.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 13:08:12
 * @brief ��ȡ�ʱ��ļ���������ÿһ��
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
     * @brief ���캯��
     **/
    ParseDictFile() {}

    /**
     * @brief ���þ����е�����Ϊint
     * @param [in] is_array : bool  �Ƿ�Ϊ��������   
     * @return int
     * @retval �ɹ�����0��ʧ�ܷ���-1
     **/
    int add_element_type_int(bool is_array);

    /**
     * @brief ���þ����е�����Ϊfloat
     * @param [in] is_array : bool  �Ƿ�Ϊ��������   
     * @return int
     * @retval �ɹ�����0��ʧ�ܷ���-1
     **/
    int add_element_type_float(bool is_array);

    /**
     * @brief ���þ����е�����Ϊchar *
     * @param [in] is_array : bool  �Ƿ�Ϊ��������   
     * @return int
     * @retval �ɹ�����0��ʧ�ܷ���-1
     **/
    int add_element_type_char(bool is_array);

    /**
     * @brief ���þ����е�����Ϊ�û��Զ�������
     * @param [in] type_name   :  string    ������
     * @param [in] obj      : BaseObject*   �û��Զ�������ʵ��
     * @param [in] is_array : bool  �Ƿ�Ϊ��������   
     * @return int
     * @retval �ɹ�����0��ʧ�ܷ���-1
     **/
    int add_element_type_user_define(const std::string &type_name, 
            BaseObject *obj, 
            bool is_array);

    /**
     * @brief parseÿһ������
     * @param [in] str : const std::string& �����ַ���col1\tcol2\tcol3...\tcoln
     * @return int
     * @retval �ɹ�����0��ʧ�ܷ���-1
     **/
    int parse_line(const std::string &str);

    /**
     * @brief ���ÿһ�����ݵ�parse���
     **/
    void output_line();

    /**
     * @brief ��������vec
     * @return vector<BaseObject *>
     * @retval ����_vec
     **/
    const std::vector<BaseObject *>& get_vector();
    ~ParseDictFile();
private:
    std::vector<BaseObject *> _vec;
};
}

#endif  //GOODCODER_ZHANGYUNJIANG_PARSE_DICT_FILE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
