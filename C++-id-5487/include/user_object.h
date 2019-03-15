/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file user_object.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:32:21
 * @brief �̳л��࣬����build_in���ͺ��û��Զ�������
 **/

#ifndef GOODCODER_ZHANGYUNJIANG_USER_OBJECT_H
#define GOODCODER_ZHANGYUNJIANG_USER_OBJECT_H

#include <vector>
#include "base_object.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&); \
        TypeName& operator=(const TypeName&)

namespace good_coder {
/**
 * @brief int��Ӧ�����ͣ��̳�BaseObject
 **/
class IntObject : public BaseObject {
public:
    IntObject();

    /**
     * @brief ��stringת����int
     * @param [in] str : string& ����parse���ַ���
     * @return IntObject *
     * @retval �ɹ�����this��ʧ�ܷ���NULL
     **/
    IntObject *parse(const std::string &str);

    /**
     * @brief ���int����
     * @param [in] for_array : bool �ж��Ƿ�������ArrayObject���������
     **/
    void output(bool for_array);

    /**
     * @brief �õ������intֵ_value
     * @return int
     * @retval ����_value
     **/
    int get_value();

    /**
     * @brief �����µ�ʵ��
     * @return IntObject *
     * @retval ����ʵ��
     **/
    IntObject *new_instance();
    ~IntObject() {}

private:
    DISALLOW_COPY_AND_ASSIGN(IntObject);
    int _value;
};

/**
 * @brief float��Ӧ�����ͣ��̳�BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:32:41
 **/
class FloatObject : public BaseObject {
public:
    FloatObject();

    /**
     * @brief ��stringת����float��Ӧ������
     * @param [in] str : string& ����parse���ַ���
     * @return FloatObject *
     * @retval �ɹ�����this��ʧ�ܷ���NULL
     **/
    FloatObject *parse(const std::string &str);

    /**
     * @brief ���float����
     * @param [in] for_array : bool �ж��Ƿ�������ArrayObject���������
     **/
    void output(bool for_array);

    /**
     * @brief �õ������floatֵ
     * @return float
     * @retval ����_value
     **/
    float get_value();

    /**
     * @brief �����µ�ʵ��
     * @return FloatObject *
     * @retval ����ʵ��
     **/
    FloatObject *new_instance();
    ~FloatObject() {}

private:
    DISALLOW_COPY_AND_ASSIGN(FloatObject);
    float _value;
};

/**
 * @brief char *��Ӧ�����ͣ��̳�BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:05:07
 **/
class CharObject : public BaseObject {
public:
    CharObject();

    /**
     * @brief ��stringת����char *��Ӧ������
     * @param [in] str : string& ����parse���ַ���
     * @return CharObject *
     * @retval �ɹ�����this��ʧ�ܷ���NULL
     **/
    CharObject *parse(const std::string &str);

    /**
     * @brief ���char *����
     * @param [in] for_array : bool �ж��Ƿ�������ArrayObject���������
     **/
    void output(bool for_array);

    /**
     * @brief �õ������char *ֵ
     * @return char *
     * @retval ����_value
     **/
    char *get_value();

    /**
     * @brief �����µ�ʵ��
     * @return CharObject *
     * @retval ����ʵ��
     **/
    CharObject *new_instance();
    ~CharObject();

private:
    DISALLOW_COPY_AND_ASSIGN(CharObject);
    char *_value;
};

/**
 * @brief �����Ӧ�����ͣ��̳�BaseObject������������Ҳ��BaseObject *
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/16 11:04:19
 **/
class ArrayObject : public BaseObject {
public:
    ArrayObject() {}

    /**
     * @brief ���캯��
     * @param [in] type_name : string ָ�����������������ͣ�����int, char*��float��Ӧ������
     **/
    ArrayObject(std::string type_name, BaseObject *obj);

    /**
     * @brief ��stringת���������Ӧ������
     * @param [in] str : string& ����parse���ַ���
     * @return ArrayObject *
     * @retval �ɹ�����this��ʧ�ܷ���NULL
     **/
    ArrayObject *parse(const std::string &str);

    /**
     * @brief �����������
     * @param [in] for_array : bool �ж��Ƿ�������ArrayObject���������
     **/
    void output(bool for_array);

    /**
     * @brief ��ʼ�����飬�õ�ָ������type_name�����鳤��_array_len����г�ʼ��
     * @return int
     * @retval ��ʼ���ɹ�����0�����򷵻�-1
     **/
    int init_array(int array_len);

    /**
     * @brief �õ����������_vec
     * @return const std::vector<BaseObject *>&
     * @retval ����_vec
     **/
    const std::vector<BaseObject *>& get_value();

    /**
     * @brief �����µ�ʵ��
     * @return ArrayObject *
     * @retval ����ʵ��
     **/
    ArrayObject *new_instance();

    /**
     * @brief  �������
     **/
    void clear();
    ~ArrayObject();

private:
    std::string _type_name;
    BaseObject *_obj;
    std::vector<BaseObject *> _vec;
    DISALLOW_COPY_AND_ASSIGN(ArrayObject);
};

/**
 * @brief �Զ������ͣ�����shouji_1�����»���_�ָ�̳�BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/16 11:21:20
 **/
class TestObject : public BaseObject {
public:
    TestObject();

    /**
     * @brief ���캯��
     * @param [in] type  : std::string �»���ǰΪtype��
     * @param [in] value : int �»��ߺ�Ϊvalue
     **/
    TestObject(std::string type, int value) : _type(type), _value(value) {}

    /**
     * @brief ��stringת�����Զ�������
     * @param [in] str  : string& ����parse���ַ���
     * @return TestObject *
     * @retval �ɹ�����this��ʧ�ܷ���NULL
     **/
    TestObject *parse(const std::string &str);

    /**
     * @brief ����Զ�������
     * @param [in] for_array : bool �ж��Ƿ�������ArrayObject���������
     **/
    void output(bool for_array);

    /**
     * @brief �õ������tpye
     * @return std::string
     * @retval ����_type
     **/
    std::string get_type();

    /**
     * @brief �õ������value
     * @return int
     * @retval ����_value
     **/
    int get_value();

    /**
     * @brief �����µ�ʵ��
     * @return TestObject *
     * @retval ����ʵ��
     **/
    TestObject *new_instance();
    ~TestObject() {}

private:
    std::string _type;
    int _value;
    DISALLOW_COPY_AND_ASSIGN(TestObject);
};

}

#endif  //GOODCODER_ZHANGYUNJIANG_USER_OBJECT_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
