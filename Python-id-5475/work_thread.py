#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
线程类，调用crawler,parser,syyave进行抓取,分析,保存
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/10 11:30:41
"""
import threading
 
class WorkThread(threading.Thread):
    """
    抓取线程，从url_queue获取待抓取url，并调用crawler,parser,saver进行抓取，分析，保存
    Attributes:
        crawler:抓取类
        parser:分析类
        saver:保存类
        url_queue:抓取队列
        is_run:线程状态
        logger:打印日志
    """  
    
    def __init__(self, logger, crawler, parser, saver, url_queue):
        
        """初始化
         Args:crawler:抓取类
              url_queue:抓取队列
              parser:分析类
              saver:保存类
              url_queue:抓取队列
              logger:打印日志
         Returns:
        """ 
        threading.Thread.__init__(self)
        self.crawler =crawler
        self.parser = parser
        self.saver = saver
        self.url_queue = url_queue
        self.is_run = False
        self.logger = logger
        
    def thread_is_runed(self):
        
        """获取线程状态
         Args:
         Returns:返回状态值
        """ 
        return self.is_run
    
    def run(self):
        
        """线程执行
         Args:
         Returns:
        """ 
        self.is_run = True
        if self.url_queue.get_url_node_len() > 0:
            #获取待抓取url_node
            url_node = self.url_queue.get_url_node()
            url = url_node['url']
            html = self.crawler.get_html(url)
            if html != -1:
                url_node_list = self.parser.analys_html(html, url_node)
                self.url_queue.add_url_node_list(url_node_list)
                self.saver.save_url(url, html)
        #更新线程状态
        self.is_run = False  
