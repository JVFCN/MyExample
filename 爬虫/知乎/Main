import time
import requests
import re
from lxml import etree
from fake_useragent import UserAgent
ua = UserAgent()
headers = {
    'User-Agent': ua.random
}
url = 'https://www.zhihu.com/question/***'
page_text = requests.get(url=url, headers=headers).text
html = etree.HTML(page_text)
result = html.xpath("//img/@src")
list_img = []
for i in result:
    tmp = re.findall(r"(.+)\?", i)
    tmp = "".join(tmp)
    list_img.append(tmp)

while '' in list_img:
    list_img.remove('')

for i in list_img:
    print(i)
Num = 0
for i in list_img:
    t = time.time()
    Num += 1
    if Num == 5:
        time.sleep(1)
        Num = 0
    now = str(int(round(t * 1000000)))
    Data = requests.get(i)
    print(f"正在下载:{i}")
    fileName = "Path" + now + i[-4:]
    with open(fileName, "wb") as f:
        f.write(Data.content)
