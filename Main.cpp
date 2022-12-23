#include <iostream>
#include<vector>//����vectorͷ�ļ�
#include <map>

void Crowd(std::vector<double> vec) {
    std::map<double, double> Map_Num;
    for (int i = 0; i < vec.size(); ++i) {
        if (Map_Num.find(vec[i]) != Map_Num.end()) {
//            ��
                Map_Num[vec[i]] = ((Map_Num[vec[i]]) + 1);

        } else {
//            ����
            Map_Num[vec[i]] = 1;
        }
    }
//    for (auto iter = Map_Num.begin(); iter != Map_Num.end(); ++iter) {
//        std::cout << iter->first << " " << iter->second << std::endl;
//    }
    double most_common_num = 0;
    int max_count = 0;
    // ���� map���ҵ����ִ�����������
    for (const auto& p : Map_Num) {
        if (p.second > max_count) {
            most_common_num = p.first;
            max_count = p.second;
        }
    }

    std::cout << "����: " << most_common_num << std::endl;
    std::cout << "���ֵĴ���: " << max_count << std::endl;
}

// �������������� vector ������� double ����������п�������
void quickSort(std::vector<double> &vec, int left, int right) {
    // �����߽�����ұ߽磬�˳��ݹ�
    if (left >= right) return;

    // ѡȡ��׼Ԫ��
    int pivot = left + (right - left) / 2;
    double pivotValue = vec[pivot];

    // ��ʼ����߽���ұ߽�
    int i = left;
    int j = right;

    // ��С�ڻ�׼��Ԫ�ط��ڻ�׼Ԫ�ص���ߣ������ڻ�׼��Ԫ�ط��ڻ�׼Ԫ�ص��ұ�
    while (i <= j) {
        // �ҵ����ڻ�׼��Ԫ��
        while (vec[i] < pivotValue) i++;

        // �ҵ�С�ڻ�׼��Ԫ��
        while (vec[j] > pivotValue) j--;

        // �����߽�С�ڵ����ұ߽磬��������Ԫ��
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
    std::cout << "������һ������:";
    std::vector<double> array;//����һ��vector����array
    double number;
    while (1) {
        std::cin >> number;
        array.push_back(number);//ÿ����һ�����־Ͱ�����ӵ���������
        if (std::cin.get() == '\n')//����ǻس���������ѭ��
            break;
    }
//    int len = array.size();//�������鳤��Ϊlen


//��λ��
    double Half, Half_Two;
    if ((array.size() % 2) == 0) {
        //std::cout << (array.size()) / 2 << std::endl;
        Half = (array.size() + 1) / 2;
        Half_Two = (array[Half] + array[Half - 1]) / 2;
        std::cout << "��λ��:" << Half_Two << std::endl;
    } else {
//        std::cout << (array.size() + 1) / 2 << std::endl;
        Half = (array.size()) / 2;
        std::cout << "��λ��:" << array[Half] << std::endl;
    }

//������
    quickSort(array, 0, array.size() - 1);
    std::cout << "������:" << array.back() << std::endl;

//����
    Crowd(array);

    system("pause");
    return 0;
}