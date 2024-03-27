#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
// ƽ���㷨�����з���Ԫ�ص��㷨

std::vector<int> dotProductNaive(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
    int n = matrix.size();
    std::vector<int> results(n, 0.0);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            results[j] += matrix[i][j] * vector[i];
        }
    }
    return results;
}

// Cache�Ż��㷨�������з��ʾ���Ԫ�����Ż���������
std::vector<int> dotProductOptimized(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
    int n = matrix.size();
    std::vector<int> results(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            results[j] += matrix[i][j] * vector[i];
        }
    }
    return results;
}

int main() {
    int n = 1500 ;// �����С
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::vector<int> vector(n);

    // ��ʼ�������������Ϊ�˼���������������ֵ��䣩
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = (i + j) ;
        }
        vector[i] = i ;
    }

 LARGE_INTEGER freq, head, tail;
    QueryPerformanceFrequency(&freq); // ��ȡ���ܼ�������Ƶ��
    QueryPerformanceCounter(&head); // ��ȡ��ʼʱ��
    for (int i=0;i<30;i++){
    dotProductNaive(matrix,vector);
    }
    QueryPerformanceCounter(&tail); // ��ȡ����ʱ��
    double elapsedTime = static_cast<double>(tail.QuadPart - head.QuadPart) / static_cast<double>(freq.QuadPart);
    cout<< "ƽ���㷨��ʱ��Ϊ ��"<<elapsedTime<<endl;

LARGE_INTEGER freq1, head1, tail1;
    QueryPerformanceFrequency(&freq1); // ��ȡ���ܼ�������Ƶ��
    QueryPerformanceCounter(&head1); // ��ȡ��ʼʱ��
    for (int i=0;i<30;i++){
    dotProductOptimized(matrix,vector);
    }
    QueryPerformanceCounter(&tail1); // ��ȡ����ʱ��
    double elapsedTime1 = static_cast<double>(tail1.QuadPart - head1.QuadPart) / static_cast<double>(freq1.QuadPart);
    cout<< "cache�Ż��㷨��ʱ��Ϊ ��"<<elapsedTime1<<endl;

    return 0;
}
