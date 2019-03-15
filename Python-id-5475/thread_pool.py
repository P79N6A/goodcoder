#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
线程池，用于获取线程和保存线程
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/10 11:02:23
"""
import threading
import work_thread
    
class ThreadPool(object):
    """
    抓取url和读写html文件的线程
    Attributes:
        log:日志对象
        webpage_cralwer:用于获取url的html类
        webpage_parser:解析html类
        webpage_save:保存html类
        url_queue:抓取队列
        thread_max_num:当前启动的线程个数
        thread_list:线程list
    """  
    
    def __init__(self, logger, thread_max_num, webpage_cralwer, 
                 webpage_parser, webpage_saver, url_queue):
        
        """初始化
         Args:
         Returns:
        """ 
        self.log = logger
        self.thread_max_num = thread_max_num
        self.mutex = threading.Lock()
        self.cralwer = webpage_cralwer
        self.parser = webpage_parser
        self.saver = webpage_saver
        self.url_queue = url_queue
        self.thread_list = []
       
    def wait(self):  
            
        """等等线程池结束
           Args:
           Returns:
        """ 
        for thread in self.thread_list:#等待进程完成，后再判断是否停止
            if thread.isAlive():
                thread.join(2) 
        
    def get_thread(self):
    
        """获取线程
           Args:
           Returns:work 返回新建线程
        """
        self.mutex.acquire(1)
        self.check_thread()#先把线程池中，执行完的线程从thread_list中去掉
        #线程数小于最大线程数，则分配新的线程
        if len(self.thread_list) < self.thread_max_num:
            work_threads = work_thread.WorkThread(self.log, self.cralwer, 
                                                  self.parser, self.saver, self.url_queue) 
            self.thread_list.append(work_threads)
            self.mutex.release()
            return work_threads
        else:
            self.log.info('no thread could get')
            self.mutex.release()
            return -1

    def check_thread(self):
    
        """从线程池中去掉执行完的线程
            Args:
            Returns:
        """
        for work in self.thread_list:
            if not work.thread_is_runed():
                self.log.info('have thread finish')
                self.thread_list.remove(work)
    
    
