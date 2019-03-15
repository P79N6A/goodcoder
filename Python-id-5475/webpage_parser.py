#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
解析类,用于解析网页
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/07 12:01:58
"""
import urlparse
from sgmllib import SGMLParser

class WebpageParser(SGMLParser):
    """
    解析html
    Attributes:
        logger: 用于写日志的对象
        max_depth:抓取的最大深度
    """ 
    
    def __init__(self, logger, max_depth):
        """初始化
        Args:
        logger: 用于写日志的对象
        Returns:
        """
        SGMLParser.__init__(self)
        self.logger = logger
        self.get_url_list = []
        self.max_depth = max_depth
        
    def analys_html(self, html, url_node):   
        """解析html中的url
        Args:
            html:需要解析的html
            url_node:需要抓取的url_node
        Returns: 解析出的url_list
        """ 
        self.feed(html)
        url_node_list = []
        url = url_node['url']
        for pars_url in self.get_url_list:
            curr_node = {}   
            #获取url的绝对路径
            curr_node['url'] = self.get_url_path(url, pars_url)
            curr_node['level'] = url_node['level'] + 1
            curr_node['father'] = url_node['father']
            #self.logger.info('curr_level:' + str(curr_node['level']) + ' max_level:' + str(self.max_depth))
            #如果大于最大深度则不用入队列
            if int(curr_node['level']) <= int(self.max_depth):
                url_node_list.append(curr_node)
        self.logger.info('len url: ' + str(len(self.get_url_list))) 
        return url_node_list
    
    def get_url_path(self, father_url, url):   
        """获取url的绝对路径
        Args:url:需要判断的url
             father_url:url的父节点
        Returns: 返回url绝对路径
        """   
        parser_tuple = urlparse.urlparse(url)
        if parser_tuple.scheme != "": 
            return url
        curr_url = parser_tuple[2]
        domain = self.get_url_head(father_url)
        url = domain + '/' + curr_url
        return url  

    def get_url_head(self, url):
        """获取url的最后一个/
           Args:url: 需要查找的url 
           Returns: 返回url除去最后一个/之前的内容
        """  
        parser = urlparse.urlparse(url)
        path = parser.path
        if path == "":
            self.logger.info('this is domian url') 
            return url
        pos = url.rfind('/', 0, len(url))
        url = url[0:pos]
        return  url
       
    def start_a(self, attrs): 
        """获取html中的url
           Args:
           Returns:
        """
          
        href = [v for k, v in attrs if k == 'href']   
        if href:            
            self.get_url_list.append(href[0])
            
    def start_img(self, attrs): 
        """获取html中的image
           Args:
           Returns:
        """          
        href = [v for k, v in attrs if k == 'src']   
        if href:            
            self.get_url_list.append(href[0])  
            
    def start_link(self, attrs): 
        """获取html中的link
           Args:
           Returns:
        """          
        href = [v for k, v in attrs if k == 'href']   
        if href:            
            self.get_url_list.append(href[0])   
      
    def start_base(self, attrs): 
        """获取html中的base
           Args:
           Returns:
        """
        for key, value in attrs: 
            if key == "href": 
                self.get_url_list.append(value)
                break   
