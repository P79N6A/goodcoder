#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
参数解析类
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/06 10:22:49
"""
import sys
import getopt
    
class OptParser(object):
    """
    参数解析模块
    """
    def __init__(self):
        """获取参数
        return: 0 参数正确，不需退出
                1 参数正确，需要退出
                -1 出现异常，需要退出
        Except : getopt.GetoptError
        """
        ret_val = 0
        try:
            self.conf = "spider.conf"
            opts, args = getopt.getopt(sys.argv[1:], 'hvc:', ['help'])
            for opt, arg in opts:
                if (opt == '-h') or (opt == '--help'):
                    self.usage()
                    ret_val = 1
                elif opt == '-v':
                    print(" mini_spider version 1.0.0.1")
                    ret_val = 1
                else:
                    self.conf = arg
                    if os.path.exists(self.conf) == False:
                        print "conf not exists: %s " % self.conf 
                        ret_val = -1
        except getopt.GetoptError as e:
            print e
            self.usage()
            ret_val = -1
        if ret_val != 0:
            sys.exit(ret_val)

    def usage(self):
        """help information
        """
        print("Usage:python mini_sider.py -c spider.conf")
        print("-----------------------------------------------------------")
        print("     -h(--help)        :    show help info")
        print("     -v                :    the version of mini_spider")
        print("     -c                :    Configuration file")
        print("-----------------------------------------------------------")
