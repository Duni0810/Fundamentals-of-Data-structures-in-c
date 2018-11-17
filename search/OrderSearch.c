#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

/** \brief 数组打印 */ 
void println(int array[], int len)
{
    int i = 0;
    
    for(i=0; i<len; i++) {
        printf("%d ", array[i]);
    }
    
    printf("\n");
}

/** \brief 置换 */ 
void swap(int array[], int i, int j)
{
    int temp = array[i];
    
    array[i] = array[j];
    
    array[j] = temp;
}

/** \brief 选择排序 */ 
void SelectionSort(int array[], int len) // O(n*n)
{
    int i = 0;
    int j = 0;
    int k = -1;
    
    for(i = 0; i<len; i++) {
        k = i;
        
        for(j=i; j<len; j++) {
            if( array[j] < array[k] ) {
                k = j;
            }
        }
        // 交换 
        swap(array, i, k);
    }
}

/**
 * \brief 递归二分法 
 *
 * param[in] a[in] : 查找表
 * patam[in] low   : 查找区间低位
 * param[in] high  : 查找区间高位
 * param[in] key   : 查找的关键字 
 *
 * retval : -1 没找到 
 */ 
int binary_search(int a[], int low, int high, int key) // O(logn)
{
    int ret = -1;
    
    if( low <= high ) {
        int mid = (low + high) / 2;
        
        if( a[mid] == key ) {
            ret = mid;
        } else if( key < a[mid] ) {
            ret = binary_search(a, low, mid-1, key);
        } else if( key > a[mid] ) {
            ret = binary_search(a, mid+1, high, key);
        }
    }
    
    return ret;
}

/**
 * \brief 非递归二分法 
 *
 * param[in] a[in] : 查找表
 * patam[in] low   : 查找区间低位
 * param[in] high  : 查找区间高位
 * param[in] key   : 查找的关键字 
 *
 * retval : -1 没找到 
 */ 
int binary_search_ex(int a[], int low, int high, int key) // O(logn)
{
    int ret = -1;
    
    while( low <= high ) {
        int mid = (low + high) / 2;
        
        if( a[mid] == key ) {
            ret = mid;
            break;
        } else if( key < a[mid] ) {
            high = mid - 1;
        } else if( key > a[mid] ) {
            low = mid + 1;
        }
    }
    
    return ret;
}

/**
 * \brief 插值查找 
 *
 * param[in] a[in] : 查找表
 * patam[in] low   : 查找区间低位
 * param[in] high  : 查找区间高位
 * param[in] key   : 查找的关键字 
 *
 * retval : -1 没找到 
 */ 
int interpolation_search(int a[], int low, int high, int key)
{
    int ret = -1;
    
    while( (low <= high) && (a[low] <= key) && (key <= a[high]) )
    {
    	// 计算取值 
        float fx = 1.0f * (key - a[low]) / (a[high] - a[low]);
        int mid = low + fx * (high - low);
        
        if( a[mid] == key ) {
            ret = mid;
            break;
        } else if( key < a[mid] ) {
            high = mid - 1;
        } else if( key > a[mid] ) {
            low = mid + 1;
        }
    }
    
    return ret;
}

int main(int argc, char *argv[]) 
{
    int a[SIZE] = {0};
    int i       = 0;
    int key     = 0;
    int index   = 0;
    
    // 随机数种子 
    srand((unsigned int)time(NULL));
    
    for(i=1; i<=SIZE; i++) {
    	// 随机产生 0~99 数并赋值 
        a[i] = rand() % 100;
    }
    
    key = 50;
    
    printf("Binary Search Demo\n");
    printf("Key: %d\n", key);
    printf("Array: \n");
    
    SelectionSort(a, SIZE);
    
    println(a, SIZE);
    
    index = interpolation_search(a, 0, SIZE-1, key);
    
    if( index > 0 ) {
        printf("Success: a[%d] = %d\n", index, a[index]);
    } else {  // 查找失败 
        printf("Failed!\n");
    }
    
	return 0;
}
