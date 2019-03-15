/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
/**
 * @file test_user_object.cpp
 * @author zhangyunjiang(zhangyunjiang@baidu.com)
 * @date 2015/11/24 10:53:30
 * @brief used for test IntObject
 *  
 **/

#include <string>
#include <vector>
#include "user_object.h"
#include "base_object.h"
#include "gtest/gtest.h"

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); //Ë³ÐòÖ´ÐÐ

}

namespace good_coder {

class TestIntSuite : public ::testing::Test {
public:
    virtual ~TestIntSuite(){}
protected:
    virtual void SetUp(){
        _obj = new IntObject();
    }
    virtual void TearDown(){
        if (_obj != NULL){
            delete _obj;
            _obj = NULL;
        }
    }
private:
    IntObject *_obj;
};

TEST_F(TestIntSuite, test_int){
    ASSERT_EQ(5, _obj->parse("5")->get_value());
    ASSERT_EQ(-5, _obj->parse("-5")->get_value());
    ASSERT_EQ(0, _obj->parse("0")->get_value());
    ASSERT_EQ(10, _obj->parse("+10")->get_value());
    ASSERT_EQ((IntObject *)NULL, _obj->parse("9.2"));
    ASSERT_EQ((IntObject *)NULL, _obj->parse(""));

}

class TestFloatSuite : public ::testing::Test {
public:
    virtual ~TestFloatSuite(){}
protected:
    virtual void SetUp(){
        _obj = new FloatObject();
    }
    virtual void TearDown(){
        if (_obj != NULL){
            delete _obj;
            _obj = NULL;
        }
    }
    
private:
    FloatObject *_obj;
};

TEST_F(TestFloatSuite, test_float){
    ASSERT_FLOAT_EQ(5.91, _obj->parse("5.91")->get_value());
    ASSERT_FLOAT_EQ(-5.3, _obj->parse("-5.3")->get_value());
    ASSERT_FLOAT_EQ(0.0, _obj->parse("0.0")->get_value());
    ASSERT_FLOAT_EQ(100, _obj->parse("100")->get_value());
    ASSERT_EQ((FloatObject *)NULL, _obj->parse("notFloat"));
    ASSERT_EQ((FloatObject *)NULL, _obj->parse(""));
}

class TestCharSuite : public ::testing::Test {
public:
    virtual ~TestCharSuite(){}
protected:
    virtual void SetUp(){
        _obj = new CharObject();
    }
    virtual void TearDown(){
        if (_obj != NULL){
            delete _obj;
            _obj = NULL;
        }
    }
    
private:
    CharObject *_obj;
};

TEST_F(TestCharSuite, test_char){
    ASSERT_STREQ("test", _obj->parse("test")->get_value());
    ASSERT_STREQ("9000", _obj->parse("9000")->get_value());
    ASSERT_EQ((CharObject *)NULL, _obj->parse(""));
}

class TestArraySuite : public ::testing::Test {
public:
    virtual ~TestArraySuite(){}
protected:
    virtual void SetUp(){
        _obj = new ArrayObject("int", new IntObject());
    }
    virtual void TearDown(){
        if (_obj != NULL){
            delete _obj;
            _obj = NULL;
        }
    }
    
private:
    ArrayObject *_obj;
};

TEST_F(TestArraySuite, test_array){
    vector<BaseObject*> _vec = _obj->parse("3:1,2,3")->get_value();
    ASSERT_EQ(3, _vec.size());
    ASSERT_EQ(2, (dynamic_cast<IntObject *>(_vec[1]))->get_value());
    ASSERT_EQ((ArrayObject *)NULL, _obj->parse("5:1,2,3"));
    ASSERT_EQ((ArrayObject *)NULL, _obj->parse("1,2,3"));
    ASSERT_EQ((ArrayObject *)NULL, _obj->parse(""));
}

class TestUserSuite : public ::testing::Test {
public:
    virtual ~TestUserSuite(){}
protected:
    virtual void SetUp(){
        _obj = new TestObject();
    }
    virtual void TearDown(){
        if (_obj != NULL){
            delete _obj;
            _obj = NULL;
        }
    }
    
private:
    TestObject *_obj;
};

TEST_F(TestUserSuite, test_user){
    ASSERT_EQ("meizu", _obj->parse("meizu_3")->get_type());
    ASSERT_EQ(3, _obj->parse("meizu_3")->get_value());
    ASSERT_EQ((TestObject *)NULL, _obj->parse("baidu_9000a"));
    ASSERT_EQ((TestObject *)NULL, _obj->parse("baidu_"));
    ASSERT_EQ((TestObject *)NULL, _obj->parse("3"));
    ASSERT_EQ((TestObject *)NULL, _obj->parse(""));
}
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
