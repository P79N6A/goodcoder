# !/usr/bin/env python
#coding:utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved 
#
################################################################################
"""
This module init log
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/10 16:22:09
"""
import os
import logging
import logging.handlers

class Log(object):
    """
    log
    Attributes:
        logger:log module
    """  
    
    def init_log(self, log_path, level_stream, level=logging.INFO, when="D", backup=7,
             format="%(levelname)s: %(asctime)s: %(filename)s:%(lineno)d * %(thread)d %(message)s",
             datefmt="%y-%m-%d %H:%M:%S"):
    
        """
        init_log - initialize log module

        Args:
          log_path      - Log file path prefix.
                      Log data will go to two files: log_path.log and log_path.log.wf
                      Any non-exist parent directories will be created automatically
          level_stream - msg above the level will be displayed,for stream
          level         - msg above the level will be displayed
                      DEBUG < INFO < WARNING < ERROR < CRITICAL
                      the default value is logging.INFO
          when          - how to split the log file by time interval
                      'S' : Seconds
                      'M' : Minutes
                      'H' : Hours
                      'D' : Days
                      'W' : Week day
                      default value: 'D'
          format        - format of the log
                      default format:
                      %(levelname)s: %(asctime)s: %(filename)s:%(lineno)d * %(thread)d %(message)s
                      INFO: 2015-11-10 15:28:56: log.py:50 * 140146946344672 debuginfo message
          backup        - how many backup file to keep
                      default value: 7

        Raises:
        OSError: fail to create log directories
        IOError: fail to open log file
        """
        formatter = logging.Formatter(format, datefmt)
        self.logger = logging.getLogger()
        self.logger.setLevel(level)
        dir = os.path.dirname(log_path)
        if not os.path.isdir(dir):
            try:
                os.makedirs(dir)  
            except IOError as err:
                return -1
        handler = logging.handlers.TimedRotatingFileHandler(log_path + ".log",
                                                        when=when,
                                                        backupCount=backup)
        handler.setLevel(level)
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)
    
        ch = logging.StreamHandler()  
        formatter = logging.Formatter('%(levelname)s - %(asctime)s - %(filename)s - %(message)s',\
                                     datefmt)  
        ch.setLevel(level_stream)  
        ch.setFormatter(formatter)
        handler = logging.handlers.TimedRotatingFileHandler(log_path + ".log.wf",
                                                        when=when,
                                                        backupCount=backup)
        handler.setLevel(logging.WARNING)
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)  
        self.logger.addHandler(ch) 
        return self.logger
    
    def get_log(self, log_path, log_file, level_stream=logging.INFO):
        
        """初始化日志
        Args:          log_path 日志相对路径
        log_file:      日志文件
        Returns:      日志对象
        """
        obs_path = os.path.abspath(log_path)
        logpath = os.path.join(obs_path, log_file)  
        logger = self.init_log(logpath, level_stream)
        return logger
