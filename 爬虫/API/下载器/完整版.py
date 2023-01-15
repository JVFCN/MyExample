import os
import time
import requests
from fake_useragent import UserAgent
import hashlib

def getmd5(filename):
    file_txt = open(filename, 'rb').read()
    m = hashlib.md5(file_txt)
    return m.hexdigest()

def main(InPath):
    path = InPath
    all_size = {}
    total_file = 0
    total_delete = 0
    start = time.time()
    for file in os.listdir(path):
        total_file += 1
        real_path = os.path.join(path, file)
        if os.path.isfile(real_path) == True:
            size = os.stat(real_path).st_size
            size_and_md5 = [""]
            if size in all_size.keys():
                new_md5 = getmd5(real_path)
                if all_size[size][0] == "":
                    all_size[size][0] = new_md5
                if new_md5 in all_size[size]:
                    print('删除', real_path)
                    os.remove(real_path)
                    total_delete += 1
                else:
                    all_size[size].append(new_md5)
            else:
                all_size[size] = size_and_md5
    end = time.time()
    time_last = end - start
    print('文件总数：', total_file)
    print('重复文件删除个数：', total_delete)
    print('耗时：', time_last, '秒')

ua = UserAgent()
Num = 0
head = {
    'User-Agent': ua.random
}
Download_Num = int(input("下几张:"))
Path = input("下载路径:")
for i in range(Download_Num):
    Num += 1
    if Num == 5:
        head['User-Agent'] = ua.random
        Num = 0
    print(f"正在下载第{i}张")
    Get_Req = requests.get("https://xiaobapi.top/api/xb/api/pixiv_r18.php", headers=head)
    Get_URL, Format = Get_Req.json()['data'][0]['urls']['original'], Get_Req.json()['data'][0]['ext']

    get_File = requests.get(Get_URL)
    Now = str(int(time.time()))
    FileName = f"{Path}\\{Now}.{Format}"
    with open(FileName, "wb") as f:
        f.write(get_File.content)
    print(f"第{i}张下好了")
print("都下好啦")

DamageFile = 0
if os.path.exists(Path):
    files = os.listdir(Path)
    for i in files:
        i = f"{Path}\\{i}"
        s = round(os.path.getsize(i) / float(1024), 2)
        if s < 60.0:
            DamageFile += 1
            print(f"{i}为损坏文件, 已清除")
            os.remove(i)
else:
    print('this path not exist')
print(f"共有{DamageFile}个损坏文件")

main(Path)
