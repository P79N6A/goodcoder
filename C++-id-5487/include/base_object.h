/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file base_object.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 11:31:48
 * @brief ����build_in�Լ��û��������͵Ļ��࣬�ṩparse��output����
 **/

#ifndef GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H 
#define GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H

#include <string>

namespace good_coder{

class BaseObject {
public:
    BaseObject() {}
    
    /**
     * @brief parse��������string����parse�ɾ�������
     * @param [in] str : string& ����parse���ַ���
     * @return BaseObject *
     * @retval ����this��ʧ�ܷ���NULL
     **/
    virtual BaseObject *parse(const std::string &str) = 0;

    /**
     * @brief output����������������ת����string���
     * @param [in] for_array : bool �ж��Ƿ��������������������
     **/
    virtual void output(bool for_array) = 0;
    
    /**
     * @brief ����һ���µ�ʵ��
     * @return BaseObject *
     * @retval ����BaseObjectʵ��
     **/
    virtual BaseObject *new_instance() = 0;
    virtual ~BaseObject() {}
};

}

#endif // GOODCODER_ZHANGYUNJIANG_BASE_OBJECT_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
