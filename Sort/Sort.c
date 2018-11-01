#include <stdio.h>

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Print(int array[], int size);
void SelectSort_0(int array[], int size) {
    int max = 0;         //用来保存本次求出的最大值的下标
    int i = 0;
    int j = 0;
    for (i = 0; i < size - 1; i++) {
        max = 0;
        for (j = 0; j < size - 1 - i; j++) {
            if (array[j + 1] > array[max]) {
                max = j + 1;
            }
        }
        if (max != j) {
        Swap(array + max, array + j);
        }
    }
}
void SelectSort_1(int array[], int size)
{
    int min = 0;
    int max = 0;
    int left = 0;
    int right = size - 1;
    while(left < right) {
        min = left;
        max = right;
        for (int j = 0; j <= right; j++) {

            if (array[left + j] > array[max]) {
                max = j;
            }
            if (array[left + j] < array[min]) {
                min = j;
            }
            if (min != left) {
                Swap(array + min, array + left);
            }
            if (max == left) {
                max = min;
            }
            if (max != right) {
                Swap(array + max, array + right);
            }
        }
        left++;
        right--;
    }
}

void AdjustDown(int array[], int size, int root)
{
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if (left >= size) {
        return;
    }
    int max = array[left];
    if (right < size && array[right] > array[left]) {
        max = right;
    } 
    if (array[root] >= array[max]) {
        return;
    }
    
    Swap(array + root, array + max);
    
    AdjustDown(array, size, max);


}

void CreatHeap(int array[], int size)
{
    int root = (size - 1 - 1) / 2;
    while(root >= 0) {
        AdjustDown(array, size, root);
        root--;
    } 
    
}

void BubbleSort(int array[], int size)
{
    int flag = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 -i; j++) {
            if (array[j] > array[j + 1]) {
                Swap(array + j, array + j + 1);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

int Partition_01(int array[], int left, int right)
{
    int start = left;
    int end = right - 1;
    while(start < end) {
        while(start < end && array[start] <= array[right]) {
            start++;
        }
        while(start < end && array[end] >= array[right]) {
            end--;
        }
        Swap(array + start, array + end);
    }
    Swap(array + end, array + right);
    return start;
}

int Partition_02(int array[], int left, int right)
{
    int begin = left;
    int end = right;
    int tmp = array[right];
    while(begin < end) {
        while(begin < end && array[begin] <= tmp) {
            begin++;
        }
        array[end] = array[begin];
        while(begin < end && array[end] >= tmp) {
            end--;
        }
        array[begin] = array[end];
    }
    array[begin] = tmp;
    return begin;
}

int Partition_03(int array[], int left, int right)
{
    int less = left;       //第一个大于基准的 最后与基准进行交换 并返回
    int great = left;      //大于基准的最右边
    while (great < right) {
        if (array[great] < array[right]) {
                Swap(array + less, array + great);
                less++;     //多了一个小于的 往前走一步
 //               printf("less == %d", less);
        }
        great++;
    }
    Swap(array + less, array + right);
    return less;    //指向的是基准
}

#if 0
void QuickSort(int array[], int size)             //数组的首地址和数组的元素的个数
{
    int left = 0;
    int right = size - 1;
    if (size <= 1) {    //当个数小于等于一个的时候，不继续排序
        return;
    }
  //  printf("未：");
  //  Print(array, size);
    int i = Partition_03(array, left, right);
  //  printf("已：");
 //   Print(array, size);
//    printf("i == %d\n", i);
    QuickSort(array, i);        
    QuickSort(array + i + 1, size - i - 1);
}

#else 

void QuickSort(int array[], int left, int right) {
    if (left >= right) {
        return;
    }
    int i = Partition_01(array, left , right);
    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);

}

#endif 

void Print(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


int main()
{
    int array[] = {2, 6, 4, 3, 7, 1, 0, 8, 9, 5};
    int size = sizeof(array) / sizeof(array[0]);
    Print(array, size);
  //  QuickSort(array, size);
    SelectSort_0(array, size);
    Print(array, size);
    return 0;
}
