#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
抓取类,用于抓取对应的URL
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/07 11:02:23
"""
import urllib2
import socket

class WebpageCrawler(object):
    """
    抓取url
    Attributes:
        logger: 用于写日志的对象
    """ 
    
    def __init__(self, logger):
        
        """初始化
        Args:
        logger: 用于写日志的对象
        Returns:
        """
        self.logger = logger
 
    def get_html(self, url):  
        
        """从url获取html
        Args:需要抓取的url
        Returns: html
        """ 
        try:
            self.logger.info('start get url:' + url)
            page=urllib2.urlopen(url)
            html=page.read() 
            page.close()
        except urllib2.URLError as e:
            self.logger.warn('url error:' + url + ' ' + str(e))
            return -1
        except socket.timeout as e:
            self.logger.warn('time out' + str(e)) 
            return -2
        return html
        
