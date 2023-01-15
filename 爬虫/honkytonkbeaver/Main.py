# 引用库文件：
import time # 获取时间
import requests # 请求数据
import os # 新建目录
import re # 正则表达式
from lxml import etree # xml

# 建立目录，文件名：
if not os.path.exists('下载'):
    os.mkdir('下载') # 新建文件夹“下载”
父网页页数 = 1 # 定义父网页页数
while 1: # 父网页翻页
    # 获取父网页：
    父网页页数字符串 = str(父网页页数)
    父网页源码 = etree.HTML(requests.get('https://honkytonkbeaver.com/' + 'page/' + 父网页页数字符串 + '/').text) # 获取首页源码
    子网页序号 = 0
    while 1: # 子网页
        # 获取子网页：
        子网页列表 = 父网页源码.xpath("//a/@href") # 获取父网页中子网页列表
        子网页列表 = 子网页列表[10:] # 去除无效
        子网页列表整理 = list(set(子网页列表)) # 去重
        子网页列表整理.sort(key=子网页列表.index) # 乱序       
        # 第一张图片
        子网页源码 = etree.HTML(requests.get(子网页列表整理[子网页序号]).text) # 获取子网页源码
        # 获取图片：
        图片直链 = 子网页源码.xpath("//img/@src") # 获取子网页中图片直链列表
        for 行 in 图片直链: # 遍历列表的每个元素
            if "content" in 行: # 寻找“content”
                if ".jpeg" in 行: # 寻找“.jpeg”
                    下载的直链 = 行
        图片序号 = 1
        下载的直链格式前 = re.findall(r"https://.*_", 下载的直链)
        下载的直链格式后有多余 = re.findall(r"_.*jpeg", 下载的直链)
        下载的直链格式后有多余 = str(下载的直链格式后有多余)
        下载的直链格式后 = re.findall(r"-.*jpeg", 下载的直链格式后有多余)
        while 图片序号 != 11:
            图片序号个位 = 图片序号%10 # 个位
            图片序号十位 = (int(图片序号/10))%10 # 十位
            图片序号百位 = int(图片序号/100) # 百位
            图片序号字符串 = str(图片序号百位) + str(图片序号十位) + str(图片序号个位)
            for 行 in 下载的直链格式前: # 遍历列表的每个元素
                if "http" in 行: # 寻找“content”
                    下载的直链格式前字符串 = 行
            for 行 in 下载的直链格式后: # 遍历列表的每个元素
                if ".jpeg" in 行: # 寻找“.jpeg”
                    下载的直链格式后字符串 = 行
            下载的直链成品 = 下载的直链格式前字符串 + 图片序号字符串 + 下载的直链格式后字符串
            图片数据 = requests.get(下载的直链成品)
            时间 = time.time() # 获取时间
            时间戳 = str(int(round(时间 * 1000000))) # 计算时间戳
            文件 = "下载/" + 时间戳 + 下载的直链[-5:] # 定义输出路径
            with open(文件, "wb") as f: # 以二进制
                f.write(图片数据.content) # 写入文件
            图片序号 += 1
        子网页序号 += 1 # 计数
        if 子网页序号 == 35:
            子网页序号 = 0
            父网页页数 += 1
            break
