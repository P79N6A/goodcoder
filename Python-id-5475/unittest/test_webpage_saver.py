#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
webpage_saver的单元测试
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/07 13:23:43
"""
import unittest
import urllib
import sys
import inspect
sys.path.append("../")
import webpage_saver
import webpage_crawler
import log

class WebpageSaveTest(unittest.TestCase):  
    """
    测试WebpageSave的测试类
    Attributes:
    """
    
    def setUp(self): 
        
        """测试准备
           Args:
           Returns:
        """
        spider_log = log.Log()
        logger = spider_log.get_log('log', 'test.log', 'ERROR')
        target_url = 'http'
        output_path = '../output'
        self.webpage_crawler_test = webpage_crawler.WebpageCrawler(logger)
        self.webpage_saver_test = webpage_saver.WebpageSaver(logger, target_url, output_path)
  
    def tearDown(self): 
        
        """测试结束，清除数据
           Args:
           Returns:
        """ 
        pass  
     
    def test_judge_chaset_ascii(self):
        
        """测试get_url_list编码是ascii
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url = 'http://pycm.baidu.com:8081/'
        html = self.webpage_crawler_test.get_html(url)
        res = self.webpage_saver_test.judge_chaset(html)
        self.assertEqual(res, 'ascii', 'test_judge_chaset_ascii fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_judge_chaset_GB2312(self):
        
        """测试get_url_list编码是GB2312
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url = 'http://pycm.baidu.com:8081/page3.html'
        html = self.webpage_crawler_test.get_html(url)
        res = self.webpage_saver_test.judge_chaset(html)
        self.assertEqual(res, 'GB2312', 'test_judge_chaset_GB2312 fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_is_image_yes(self):
        
        """测试test_is_image,是图片
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url_image = 'http://pycm.baidu.com:8081/3/image.jpg'
        res_image = self.webpage_saver_test.is_image(url_image)
        self.assertEqual(res_image, True, 'test_is_image true fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        
    def test_is_image_no(self):
        
        """测试test_is_image,不是是图片
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url = 'http://pycm.baidu.com:8081/'
        res = self.webpage_saver_test.is_image(url)
        self.assertEqual(res, False, 'test_is_image false fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_transfer_url_sucess(self):
        
        """测试test_transfer_url转换成功
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3]) 
        url = 'http://pycm.baidu.com:8081/'
        res = self.webpage_saver_test.transfer_url(url)
        self.assertEqual(res, 'http$--pycm.baidu.com$8081-', 'test_transfer_url_sucess fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])

    def test_save_url_sucess(self):
        
        """测试save_url
           Args:
           Returns:
        """
        print '\n[Start]\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])
        url = 'http://pycm.baidu.com:8081/'
        html = self.webpage_crawler_test.get_html(url)
        res = self.webpage_saver_test.save_url(url, html)
        self.assertEqual(res, 0, 'test_ave_url_sucess fail')
        print '\033[1;32m[PASS]\033[0m\tclass:\033[1;33m%s\033[0m\tcase:\033[1;33m%s\033[0m' \
                    % (self.__class__.__name__, inspect.stack()[0][3])      
        
if __name__ == '__main__': 
    """main函数
           Args:
           Returns:
    """  
    unittest.main()
    sys.exit(0)  
