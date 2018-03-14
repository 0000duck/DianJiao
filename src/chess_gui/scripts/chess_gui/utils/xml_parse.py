#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 17-12-21 下午3:47
# @Author  : yu
# @File    : xml_parse.py
# @Desc    :
import xml.etree.cElementTree as ET
from std_msgs.msg import String
def xml_parse(xml_content):
    root = ET.fromstring(xml_content)
    result = root.find('result')
    confidence = result.find('confidence').text
    if int(confidence) < 25:
        return -1
    word = result.find('object').find('word')
    id = int(word.attrib['id'])
    return id




