#!/usr/bin/env python
#coding=utf-8
################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
File:test_all
Authors: zhangyunjiang(zhangyunjiang@baidu.com)
Date:    2015/11/12 18:12:42
"""
import unittest
import os
import sys
sys.path.append('./unittest')

if __name__ == '__main__':
    print os.getcwd()
    all_files = os.listdir('./unittest')
    test_files = [ff for ff in all_files if ff.startswith('test_')]
    for ff in test_files: 
        import_exec_str = 'from %s import *' % ff.split('.')[0]
        exec(import_exec_str)
    unittest.main()
