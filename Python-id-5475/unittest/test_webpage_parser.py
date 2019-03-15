#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
webpage_parser的单元测试
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/07 13:23:43
"""
import unittest
import urllib
import sys
import inspect
sys.path.append("../")
import webpage_parser
import webpage_crawler
import log

class WebPageparseTest(unittest.TestCase):  
    """
    测试WebPageparse的测试类
    Attributes:
    """
    
    def setUp(self): 
                
        """测试准备
           Args:
           Returns:
        """
        spider_log = log.Log()
        logger = spider_log.get_log('log', 'test.log', 'ERROR')
        self.webpage_parser_test = webpage_parser.WebpageParser(logger, 3)
        self.webpage_crawler_test = webpage_crawler.WebpageCrawler(logger)
       
    def tearDown(self): 
        
        """测试结束，清除数据
           Args:
           Returns:
        """ 
        pass  
     
    def test_analys_html(self):
        
        """test analys_html
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url_node = {}
        url_node['level'] = 0
        url_node['father'] = 'http://pycm.baidu.com:8081/'
        url = 'http://pycm.baidu.com:8081/'
        url_node['url'] = url
        html = self.webpage_crawler_test.get_html(url)
        url_list = self.webpage_parser_test.analys_html(html, url_node)
        res = len(url_list)
        self.assertEqual(res, 5, 'test_analys_html fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])        

    def test_get_url_path(self):
        
        """test get_get_url_path
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res = self.webpage_parser_test.get_url_path('http://pycm.baidu.com:8081/', 'page4.html')
        self.assertEqual(res, 'http://pycm.baidu.com:8081/page4.html', 'test_get_url_path fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])        
        
    def test_get_url_head_domain(self):
        
        """test get_url_head,有二级域名
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res = self.webpage_parser_test.get_url_head('http://pycm.baidu.com:8081/page4.html')
        self.assertEqual(res, 'http://pycm.baidu.com:8081', 'test_get_url_head_not_domain fail')   
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])        
    
    def test_get_url_head_not_domain(self):
        
        """test get_url_head,没有二级域名
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        res = self.webpage_parser_test.get_url_head('http://pycm.baidu.com:8081')
        self.assertEqual(res, 'http://pycm.baidu.com:8081', 'test_get_url_head_not_domain fail')    
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])        
       
if __name__ == '__main__': 
    
    """main函数
           Args:
           Returns:
    """  
    unittest.main()
    sys.exit(0)  
