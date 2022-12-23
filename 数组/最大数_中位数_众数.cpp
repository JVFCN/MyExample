#include <iostream>
#include<vector>//引入vector头文件
#include <map>

void Crowd(std::vector<double> vec) {
    std::map<double, double> Map_Num;
    for (int i = 0; i < vec.size(); ++i) {
        if (Map_Num.find(vec[i]) != Map_Num.end()) {
//            在
                Map_Num[vec[i]] = ((Map_Num[vec[i]]) + 1);

        } else {
//            不在
            Map_Num[vec[i]] = 1;
        }
    }
//    for (auto iter = Map_Num.begin(); iter != Map_Num.end(); ++iter) {
//        std::cout << iter->first << " " << iter->second << std::endl;
//    }
    double most_common_num = 0;
    int max_count = 0;
    // 遍历 map，找到出现次数最多的数字
    for (const auto& p : Map_Num) {
        if (p.second > max_count) {
            most_common_num = p.first;
            max_count = p.second;
        }
    }

    std::cout << "众数: " << most_common_num << std::endl;
    std::cout << "出现的次数: " << max_count << std::endl;
}

// 快速排序函数，对 vector 容器里的 double 类型数组进行快速排序
void quickSort(std::vector<double> &vec, int left, int right) {
    // 如果左边界大于右边界，退出递归
    if (left >= right) return;

    // 选取基准元素
    int pivot = left + (right - left) / 2;
    double pivotValue = vec[pivot];

    // 初始化左边界和右边界
    int i = left;
    int j = right;

    // 将小于基准的元素放在基准元素的左边，将大于基准的元素放在基准元素的右边
    while (i <= j) {
        // 找到大于基准的元素
        while (vec[i] < pivotValue) i++;

        // 找到小于基准的元素
        while (vec[j] > pivotValue) j--;

        // 如果左边界小于等于右边界，交换两个元素
        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }
    quickSort(vec, left, j);
    quickSort(vec, i, right);
}

int main() {
    std::cout << "请输入一个数组:";
    std::vector<double> array;//定义一个vector数组array
    double number;
    while (1) {
        std::cin >> number;
        array.push_back(number);//每输入一个数字就把它添加到数组的最后
        if (std::cin.get() == '\n')//如果是回车符则跳出循环
            break;
    }
//    int len = array.size();//返回数组长度为len


//中位数
    double Half, Half_Two;
    if ((array.size() % 2) == 0) {
        //std::cout << (array.size()) / 2 << std::endl;
        Half = (array.size() + 1) / 2;
        Half_Two = (array[Half] + array[Half - 1]) / 2;
        std::cout << "中位数:" << Half_Two << std::endl;
    } else {
//        std::cout << (array.size() + 1) / 2 << std::endl;
        Half = (array.size()) / 2;
        std::cout << "中位数:" << array[Half] << std::endl;
    }

//最大的数
    quickSort(array, 0, array.size() - 1);
    std::cout << "最大的数:" << array.back() << std::endl;

//众数
    Crowd(array);

    system("pause");
    return 0;
}
