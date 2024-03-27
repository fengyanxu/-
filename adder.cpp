#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>
using namespace std;


// ƽ���㷨������ۼ�
long long trivialSum(const vector<int>& nums) {
    long long sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

// �Ż��㷨���ǵݹ��㷨���������ֱ�����ս��
long long optimizedSum(const vector<int>& nums) {
    long long sum1 ,sum2 = 0;
    int len = nums.size();
    for (int i=0;i<len;i+=2){
        sum1 += nums[i];
        sum2+= nums[i+1];

    }
    return sum1+sum2;
}

int main() {
    const int n = pow(2, 20); // ������131,072����
    const int s = pow(2, 20); // �ظ�����
    const int measurements = 10000; // ��������
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }
  // ����ƽ���㷨����
    LARGE_INTEGER freq, head, tail;
    QueryPerformanceFrequency(&freq); // ��ȡ���ܼ�������Ƶ��

    double trivialSumElapsedTime = 0.0;
    for (int j = 0; j < measurements; ++j) {
        QueryPerformanceCounter(&head); // ��ȡ��ʼʱ��
        for (int i = 0; i < s; i++) {
            trivialSum(nums);
        }
        QueryPerformanceCounter(&tail); // ��ȡ����ʱ��
        trivialSumElapsedTime += static_cast<double>(tail.QuadPart - head.QuadPart) / static_cast<double>(freq.QuadPart);
    }
    trivialSumElapsedTime /= measurements; // ����ƽ��ʱ��
    cout << "ƽ���㷨��ƽ��ʱ��Ϊ��" << trivialSumElapsedTime << endl;

     // �����Ż��㷨����
    double optimizedSumElapsedTimeTotal = 0.0;
    LARGE_INTEGER freq1, head1, tail1;
    QueryPerformanceFrequency(&freq1); // ��ȡ���ܼ�������Ƶ��

    for (int j = 0; j < measurements; ++j) {
        QueryPerformanceCounter(&head1); // ��ȡ��ʼʱ��
        for (int i = 0; i < s; i++) {
            optimizedSum(nums);
        }
        QueryPerformanceCounter(&tail1); // ��ȡ����ʱ��
        double elapsedTime = static_cast<double>(tail1.QuadPart - head1.QuadPart) / static_cast<double>(freq1.QuadPart);
        optimizedSumElapsedTimeTotal += elapsedTime; // �ۼ�ÿ�β�����ʱ��
    }

    double optimizedSumElapsedTimeAverage = optimizedSumElapsedTimeTotal / measurements; // ����ƽ��ʱ��
    cout << "�Ż��㷨��ƽ��ʱ��Ϊ��" << optimizedSumElapsedTimeAverage << endl;

    return 0;
}
