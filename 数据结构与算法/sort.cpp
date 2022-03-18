#include <iostream>
#include <algorithm>
using namespace std;

const int MAXSIZE = 10;
// ��С��������
class SqList_Sort
{
public:
    SqList_Sort() : element(new int[MAXSIZE + 1]()){};

    SqList_Sort(int arr[], int n)
    {
        element = new int[MAXSIZE + 1];

        for (int i = 1; i <= n; i++)
            element[i] = arr[i - 1];
        length = n;
    };

    // ���ڵıȽϣ�ÿִ��һ�����ѭ�����ҳ��ò���Сֵ
    void BubbleSort();

    // ÿһ����һ���̶�ֵ�Ƚϣ�ÿִ��һ�����ѭ�����ҳ��ò���Сֵ
    void SelectSort();

    // ���뵽һ���Ѿ�����õ�����
    void InsertSort();

    void ShellSort();

    void HeapSort();

    void QuickSort() { QSort(1, length); }

    void QSort(int low, int high);

    void MergeSort() { MSort(element, element, 1, length); }

    void MSort(int *sr, int *tr1, int s, int t);

    void Merge(int *tr2, int *tr1, int i, int m, int t);

    void HeapAdjust(int s, int m);

    int partition(int low, int high);

    void read()
    {
        for (int i = 1; i <= length; i++)
            cout << element[i] << " ";
        cout << endl;
    }

    ~SqList_Sort()
    {
        if (element)
        {
            delete[] element;
            element = nullptr;
        }
    }

private:
    int *element = nullptr;
    int length = 0;
};

int main()
{
    int arr[] = {50, 10, 90, 30, 70, 40, 80, 60, 20};
    int n = sizeof(arr) / sizeof(int);

    cout << "����ǰ" << endl;
    SqList_Sort s(arr, n);
    s.read();
    cout << "---------------" << endl;

    cout << "�����" << endl;
    s.MergeSort();
    s.read();
    cout << "---------------" << endl;

    return 0;
}

void SqList_Sort::BubbleSort()
{
    bool flag = true;
    for (int i = 1; i < length && flag; ++i)
    {
        flag = false; // flagû�б��true ��˵��������
        for (int j = length - 1; j >= i; j--)
            if (element[j] > element[j + 1]) // �Ӵ�С �� < ��� > ����
            {
                swap(element[j], element[j + 1]);
                flag = true; // flag ���ڱ���Ƿ������ݽ���
            }
    }
}

void SqList_Sort::SelectSort()
{
    for (int i = 1; i <= length; ++i)
    {
        int min = i;
        for (int j = i + 1; j <= length; j++)
            if (element[j] < element[min]) // �Ӵ�С �� < ��� > ����
                min = j;
        if (min != i)
            swap(element[i], element[min]);
    }
}

void SqList_Sort::InsertSort()
{
    for (int i = 2; i <= length; ++i)
    {
        if (element[i] < element[i - 1]) // �Ӵ�С �� < ��� > ����
        {
            element[0] = element[i]; // �ڱ�
            int j = i - 1;
            for (; element[j] > element[0]; j--) // �Ӵ�С �� > ��� < ����
                element[j + 1] = element[j];
            element[j + 1] = element[0];
        }
    }
}

void SqList_Sort::ShellSort()
{
    int increment = length;

    do
    {
        increment = increment / 3 + 1;
        for (int i = increment + 1; i <= length; i++)
        {
            if (element[i] < element[i - increment])
            {
                element[0] = element[i];

                int j = i - increment;
                for (; j > 0 && element[j] > element[0]; j -= increment)
                    element[j + increment] = element[j];
                element[j + increment] = element[0];
            }
        }
    } while (increment > 1);
}

void SqList_Sort::HeapSort()
{
    for (int i = length / 2; i > 0; i--)
        HeapAdjust(i, length);
    for (int i = length; i > 1; i--)
    {
        swap(element[1], element[i]);
        HeapAdjust(1, i - 1);
    }
}

void SqList_Sort::HeapAdjust(int s, int m)
{
    int temp = element[s];

    int j = 2 * s;
    for (; j <= m; j *= 2)
    {
        if (j < m && element[j] < element[j + 1])
            j++;
        if (temp >= element[j])
            break;
        element[s] = element[j];
        s = j;
    }
    element[s] = temp;
}

void SqList_Sort::QSort(int low, int high)
{
    int pviot;
    if (low < high)
    {
        pviot = partition(low, high);
        QSort(low, pviot - 1);
        QSort(pviot + 1, high);
    }
}

int SqList_Sort::partition(int low, int high)
{
    /* int mid = (low + high) / 2;
        if (element[low] > element[high])
            myswap(element[low], element[high]);
        if (element[mid] > element[high])
            myswap(element[mid], element[high]);
        if(element[low]>element[mid])
            myswap(element[low], element[mid]); */

    int pviotkey = element[low];
    element[0] = pviotkey;

    while (low < high)
    {
        while (low < high && element[high] > pviotkey)
            high--;
        // myswap(element[low], element[high]);
        element[low] = element[high];

        while (low < high && element[low] < pviotkey)
            low++;
        // myswap(element[low], element[high]);
        element[high] = element[low];
    }
    element[low] = element[0];
    return low;
}

void SqList_Sort::MSort(int *sr, int *tr1, int s, int t)
{
    int tr2[MAXSIZE + 1];
    int m;

    if (s == t)
    {
        tr1[s] = sr[s];
    }
    else
    {
        m = (s + t) / 2;
        MSort(sr, tr2, s, m);
        MSort(sr, tr2, m + 1, t);
        Merge(tr2, tr1, s, m, t);
    }
}

void SqList_Sort::Merge(int *tr2, int *tr1, int i, int m, int t)
{
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= t; k++)
    {
        if (tr2[i] < tr2[j])
            tr1[k] = tr2[i++];
        else
            tr1[k] = tr2[j++];
    }
    if (i <= m)
        for (int L = 0; L <= m - i; L++)
            tr1[k + L] = tr2[i + L];

    if (j <= t)
        for (int L = 0; L <= t - i; L++)
            tr1[k + L] = tr2[i + L];
}
