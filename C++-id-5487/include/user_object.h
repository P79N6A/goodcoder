/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file user_object.h
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:32:21
 * @brief 继承基类，各种build_in类型和用户自定义类型
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
 * @brief int对应的类型，继承BaseObject
 **/
class IntObject : public BaseObject {
public:
    IntObject();

    /**
     * @brief 将string转换成int
     * @param [in] str : string& 用于parse的字符串
     * @return IntObject *
     * @retval 成功返回this，失败返回NULL
     **/
    IntObject *parse(const std::string &str);

    /**
     * @brief 输出int类型
     * @param [in] for_array : bool 判断是否用于在ArrayObject类型内输出
     **/
    void output(bool for_array);

    /**
     * @brief 得到具体的int值_value
     * @return int
     * @retval 返回_value
     **/
    int get_value();

    /**
     * @brief 生成新的实例
     * @return IntObject *
     * @retval 返回实例
     **/
    IntObject *new_instance();
    ~IntObject() {}

private:
    DISALLOW_COPY_AND_ASSIGN(IntObject);
    int _value;
};

/**
 * @brief float对应的类型，继承BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:32:41
 **/
class FloatObject : public BaseObject {
public:
    FloatObject();

    /**
     * @brief 将string转换成float对应的类型
     * @param [in] str : string& 用于parse的字符串
     * @return FloatObject *
     * @retval 成功返回this，失败返回NULL
     **/
    FloatObject *parse(const std::string &str);

    /**
     * @brief 输出float类型
     * @param [in] for_array : bool 判断是否用于在ArrayObject类型内输出
     **/
    void output(bool for_array);

    /**
     * @brief 得到具体的float值
     * @return float
     * @retval 返回_value
     **/
    float get_value();

    /**
     * @brief 生成新的实例
     * @return FloatObject *
     * @retval 返回实例
     **/
    FloatObject *new_instance();
    ~FloatObject() {}

private:
    DISALLOW_COPY_AND_ASSIGN(FloatObject);
    float _value;
};

/**
 * @brief char *对应的类型，继承BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/15 15:05:07
 **/
class CharObject : public BaseObject {
public:
    CharObject();

    /**
     * @brief 将string转换成char *对应的类型
     * @param [in] str : string& 用于parse的字符串
     * @return CharObject *
     * @retval 成功返回this，失败返回NULL
     **/
    CharObject *parse(const std::string &str);

    /**
     * @brief 输出char *类型
     * @param [in] for_array : bool 判断是否用于在ArrayObject类型内输出
     **/
    void output(bool for_array);

    /**
     * @brief 得到具体的char *值
     * @return char *
     * @retval 返回_value
     **/
    char *get_value();

    /**
     * @brief 生成新的实例
     * @return CharObject *
     * @retval 返回实例
     **/
    CharObject *new_instance();
    ~CharObject();

private:
    DISALLOW_COPY_AND_ASSIGN(CharObject);
    char *_value;
};

/**
 * @brief 数组对应的类型，继承BaseObject，数组内类型也是BaseObject *
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/16 11:04:19
 **/
class ArrayObject : public BaseObject {
public:
    ArrayObject() {}

    /**
     * @brief 构造函数
     * @param [in] type_name : string 指明数组存的是哪种类型，包含int, char*和float对应的类型
     **/
    ArrayObject(std::string type_name, BaseObject *obj);

    /**
     * @brief 将string转换成数组对应的类型
     * @param [in] str : string& 用于parse的字符串
     * @return ArrayObject *
     * @retval 成功返回this，失败返回NULL
     **/
    ArrayObject *parse(const std::string &str);

    /**
     * @brief 输出数组类型
     * @param [in] for_array : bool 判断是否用于在ArrayObject类型内输出
     **/
    void output(bool for_array);

    /**
     * @brief 初始化数组，得到指定类型type_name和数组长度_array_len后进行初始化
     * @return int
     * @retval 初始化成功返回0，否则返回-1
     **/
    int init_array(int array_len);

    /**
     * @brief 得到具体的数组_vec
     * @return const std::vector<BaseObject *>&
     * @retval 返回_vec
     **/
    const std::vector<BaseObject *>& get_value();

    /**
     * @brief 生成新的实例
     * @return ArrayObject *
     * @retval 返回实例
     **/
    ArrayObject *new_instance();

    /**
     * @brief  清空数组
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
 * @brief 自定义类型，类似shouji_1，以下划线_分割。继承BaseObject
 * @see
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/16 11:21:20
 **/
class TestObject : public BaseObject {
public:
    TestObject();

    /**
     * @brief 构造函数
     * @param [in] type  : std::string 下划线前为type，
     * @param [in] value : int 下环线后为value
     **/
    TestObject(std::string type, int value) : _type(type), _value(value) {}

    /**
     * @brief 将string转换成自定义类型
     * @param [in] str  : string& 用于parse的字符串
     * @return TestObject *
     * @retval 成功返回this，失败返回NULL
     **/
    TestObject *parse(const std::string &str);

    /**
     * @brief 输出自定义类型
     * @param [in] for_array : bool 判断是否用于在ArrayObject类型内输出
     **/
    void output(bool for_array);

    /**
     * @brief 得到具体的tpye
     * @return std::string
     * @retval 返回_type
     **/
    std::string get_type();

    /**
     * @brief 得到具体的value
     * @return int
     * @retval 返回_value
     **/
    int get_value();

    /**
     * @brief 生成新的实例
     * @return TestObject *
     * @retval 返回实例
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
