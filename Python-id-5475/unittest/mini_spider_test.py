#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
MiniSpider单测
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/14 10:11:59
"""
import unittest
import urllib
import sys
import inspect
sys.path.append("../")
import log
import mini_spider

class MiniSpiderTest(unittest.TestCase):  
    """
    测试MiniSpider的测试类
    Attributes:
    """
    
    def setUp(self): 
                
        """测试准备
           Args:
           Returns:
        """
        self.mini_spider_test = mini_spider.MiniSpider('./spider.conf')
    
    def tearDown(self): 
        
        """测试结束，清除数据
           Args:
           Returns:
        """ 
        pass  

    def test_init(self):
        
        """测试init
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res_init = self.mini_spider_test.init()
        self.assertEqual(res_init, 0, 'init_sucess fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_get_url_list_sucess(self):
        
        """测试get_url_list,正常获取url列表
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res_exits = self.mini_spider_test.get_url_list('../urls')
        self.assertEqual(len(res_exits), 1, 'get_url_list_sucess fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_get_url_list_fail(self):
        
        """测试get_url_list,未获取url列表
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res = self.mini_spider_test.get_url_list('../url')
        self.assertEqual(res, -1, 'get_url_list_fail fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        
    def test_init_url_queue(self):
        
        """测试init_url_queue
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        self.mini_spider_test.url_list_file = '../urls'
        res = self.mini_spider_test.init_url_queue()
        self.assertEqual(res.get_url_node_len(), 1, 'init_url_queue_sucess fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

        
if __name__ == '__main__':
     
    """main函数
           Args:
           Returns:
    """  
    unittest.main()
    sys.exit(0)  
