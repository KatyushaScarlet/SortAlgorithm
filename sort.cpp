#include <iostream>
#include <vector>

using namespace std;

class LinkList
{
public:
    int value;
    LinkList* next;
    LinkList() :value(0), next(nullptr) {}
    LinkList(int element) :value(element), next(nullptr) {}
};

int GetMinElement(vector<int>& input)
{
    int min = input[0];
    for (int item : input)
    {
        if (item < min)
        {
            min = item;
        }
    }
    return min;
}

int GetMaxElement(vector<int>& input)
{
    int max = input[0];
    for (int item : input)
    {
        if (item > max)
        {
            max = item;
        }
    }
    return max;
}

int GetPow(int x, int y)
{
    int result = 1;
    for (size_t i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}

void BobbleSort(vector<int>& input)//冒泡排序
{
    int size = input.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - 1 - i; j++)//最后i个数已经被排序过了，所以减去
        {
            if (input[j] > input[j + 1]) swap(input[j], input[j + 1]);
        }
    }
}

void SectionSort(vector<int>& input)//选择排序
{
    int size = input.size();
    int minIndex = 0;
    for (int i = 0; i < size - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < size; j++)//因为min默认为i，j可以从i下一个数开始查找
        {
            if (input[j] < input[minIndex])minIndex = j;
        }
        swap(input[i], input[minIndex]);
    }
}

void InsertionSort(vector<int>& input)//插入排序
{
    int size = input.size();
    int ptr = 0;
    int current = 0;

    for (int i = 1; i < size; i++)
    {
        current = input[i];
        ptr = i;
        while (ptr > 0 && input[ptr - 1] > current)//未遍历完，且前一个数比当前的大，继续向下遍历
        {
            input[ptr] = input[ptr - 1];//将前一个数向后挪一位
            ptr--;//指针指向前一个数
        }
        input[ptr] = current;//指针指向比当前值小的后一个值；
    }
}

void QuickSort(vector<int>& input, int low, int high)//快速排序
{
    if (low < high)
    {
        int privotIndex = low;//设定基准值
        int storageIndex = low;//默认从数组左前方开始比较

        swap(input[privotIndex], input[high]);//将基准值移动到数组最后

        for (size_t i = low; i <= high - 1; i++)//因为最后一个数为基准值，但high为下标值，所以索引可以到high-1
        {
            if (input[i] <= input[high])//比较当前值和基准值
            {
                swap(input[i], input[storageIndex]);//小于基准值，则往前挪动
                storageIndex++;//存储位置向右移动
            }
        }
        swap(input[high], input[storageIndex]);//将基准值移动回来
        QuickSort(input, low, privotIndex - 1);//继续排序前半部分数组
        QuickSort(input, privotIndex + 1, high);//继续排序后半部分数组
    }
}

void QuickSortStart(vector<int>& input)//快速排序开始
{
    int low = 0;
    int high = input.size() - 1;
    QuickSort(input, low, high);
}

void CountingSort(vector<int>& input)//计数排序
{
    int max = GetMaxElement(input);

    vector<int> counter(max + 1);//默认范围[0,max]


    for (int item : input)
    {
        counter[item]++;
    }

    input.clear();

    int size = counter.size();
    for (int i = 0; i < size; i++)
    {
        while (counter[i] != 0)
        {
            input.push_back(i);
            counter[i]--;
        }
    }
}
LinkList* BucketSortInsertBucket(LinkList* head, int element)//桶排序插入（有序链表的插入）
{
    if (head == nullptr)return new LinkList(element);//桶是空的，返回一个新节点

    LinkList* newHead = new LinkList();//新的头部节点
    newHead->next = head;
    LinkList* current = head;//当前头部节点
    LinkList* prev = newHead;//当前头部节点的前一个节点

    while (true)
    {
        if (element > current->value)//如果新节点比当前节点大
        {
            if (current->next == nullptr)//如果当前节点后面没有节点了
            {
                current->next = new LinkList(element);//新节点附加在尾部
                break;//插入成功，跳出
            }
            else//如果当前节点后还有节点，向后继续查找
            {
                prev = current;//前一个节点指向当前节点
                current = current->next;//当前节点指向下一个节点
                continue;//继续
            }
        }
        else//新节点小于等于当前节点，插入在前面
        {
            LinkList* newNode = new LinkList(element);//创建新节点
            newNode->next = current;//新节点的下一个节点为当前节点
            prev->next = newNode;//前一个节点的下一个节点为当前节点
            break;//插入成功，跳出
        }
    }

    return newHead->next;//返回新头部节点的下一个节点
}

void BucketSort(vector<int>& input)//桶排序
{
    int min = GetMinElement(input);
    int max = GetMaxElement(input);

    int bucketCount = input.size();//桶的数量等于数组长度
    int bucketSize = (max - min) / bucketCount + 1;//桶的大小等于每个桶之间的间距
    vector<LinkList*> bucket(bucketCount);//桶

    for (size_t i = 0; i < bucketCount; i++)//放入桶中
    {
        int bucketIndex = (input[i] - min) / bucketSize;//决定元素应被放入哪个桶（当前值与最小值的差距，除以每个桶的大小）
        bucket[bucketIndex] = BucketSortInsertBucket(bucket[bucketIndex], input[i]);//放入桶中
    }

    int index = 0;
    for (size_t i = 0; i < bucketCount; i++)//取出桶
    {
        LinkList* ptr = bucket[i];//取出指针
        while (ptr != nullptr)//若指针不为空
        {
            input[index] = ptr->value;//赋值
            ptr = ptr->next;//指向桶中下一个对象
            index++;//指向原始数组中下一个对象
        }
    }
}

void ShellSort(vector<int>& input)//希尔排序
{
    int size = input.size();//数组大小
    int gap = size / 2;//间隔

    while (gap >= 1)
    {
        for (int i = 0; i < gap; i++)
        {
            for (int j = i + gap; j < size; j += gap)//从第2个元素开始插入排序。起始位置为i，因此第2个元素为i+gap。同时下标小于总长度
            {
                int current = input[j];//当前元素的值
                int ptr = j;//当前元素的下标
                while (ptr - gap >= i && input[ptr - gap] > current)//如果未遍历完，且前一个元素比当前元素大（先判下标是否超出）
                {
                    input[ptr] = input[ptr - gap];//将前一个元素向后挪动
                    ptr -= gap;
                }
                input[ptr] = current;
            }
        }
        gap /= 2;
    }
}

void MergeSortMerge(vector<int>& input, vector<int>& spareSpace, int left, int right,int middle)//归并排序 合并
{
    int i = left;//左半边数组起始指针
    int j = middle + 1;//右半边数组起始指针
    int x = 0;//临时数组起始指针

    while (i<=middle&&j<=right)
    {
        if (input[i]<input[j])//左边小于右边，放左边的值
        {
            spareSpace[x++] = input[i++];
        }
        else//左边大于等于右边，放右边的值
        {
            spareSpace[x++] = input[j++];
        }
    }

    while (i <= middle)//将左边数组剩余的元素放进临时空间
    {
        spareSpace[x++] = input[i++];
    }

    while (j <= right)//将右边数组剩余的元素放进临时空间
    {
        spareSpace[x++] = input[j++];
    }

    x = 0;//备用数组从头遍历
    while (left<=right)//只遍历当前范围内的数据（重要）
    {
        input[left++] = spareSpace[x++];
    }
}
void MergeSortSplit(vector<int>& input, vector<int>& spareSpace,int left,int right)//归并排序 分割
{
    if (left<right)
    {
        int middle = (right + left) / 2;
        MergeSortSplit(input, spareSpace, left, middle);
        MergeSortSplit(input, spareSpace, middle+1, right);
        MergeSortMerge(input, spareSpace, left, right, middle);
    }
}

void MergeSortStart(vector<int>& input)//归并排序 开始
{
    int size = input.size();
    vector<int> spareSpace(size);//开辟临时空间用于存放合并数组
    MergeSortSplit(input, spareSpace,0, size-1);
}

void Heapify(vector<int>& input,int index,int size)
{
    int largestIndex = index;//最大的节点默认为当前节点
    int leftChildIndex = index * 2 + 1;
    int rightChildIndex = index * 2 + 2;

    if (leftChildIndex < size && input[leftChildIndex] > input[largestIndex])//如果左子树在范围内，且比当前节点更大
    {
        largestIndex = leftChildIndex;//记录新的最大的节点
    }

    if (rightChildIndex < size && input[rightChildIndex] > input[largestIndex])
    {
        largestIndex = rightChildIndex;//记录新的最大的节点
    }

    if (largestIndex != index)//如果最大的节点发生过改变
    {
        swap(input[index], input[largestIndex]);//将传入的节点与最大节点交换
        Heapify(input, largestIndex, size);//递归，继续判断
    }
}

void BuildMaxHeap(vector<int>& input)//建立最大堆
{
    int size = input.size();
    for (int i = (size / 2)-1; i >= 0; i--)//i为堆下标，数组下标=堆下标-1。倒数第二层开始，向上逐渐建立最大堆
    {
        Heapify(input, i, size);
    }
}

void HeapSort(vector<int>& input)//堆排序
{
    BuildMaxHeap(input);//首先建立最大堆

    int size = input.size();
    for (int i = size-1; i >0; i--)
    {
        swap(input[0], input[i]);//将第一个（最大）的元素与堆尾（最小）交换
        size--;//最后一个数已被排序，从总长度中减去
        Heapify(input, 0, size);//将第一个（最小）的元素重新推到堆尾
    }
}

int GetMaxBit(vector<int>& input)//获取数组中最大的数字位数
{
    int max = GetMaxElement(input);

    int maxBit = 1;
    int mask = 10;

    while (max >= mask)
    {
        mask *= 10;
        maxBit++;
    }

    return maxBit;
}

void RadixSort(vector<int>& input)//基数排序
{
    int max = GetMaxElement(input);//获取数组中最大的数

    int maxBit = 1;
    int mask = 10;
    //获取数组中最大的数的位数
    while (max >= mask)
    {
        mask *= 10;//每次mask增大10倍
        maxBit++;//向更高位判断
    }

    int size = input.size();
    for (size_t i = 0; i < maxBit; i++)
    {
        mask = GetPow(10, i);//第一次为1，第二次为10...
        vector<vector<int>>bucket(10);//0~9共10个桶，每个桶大小等于数组

        for (size_t j = 0; j < size; j++)//将每个数根据其位数放进桶里
        {
            int index = (input[j] / mask) % 10;//除以mask后与10取余，得到要求得的位数，即为桶的编号
            bucket[index].push_back(input[j]);//放入桶中
        }

        //将排序过一次的桶内容重新放进原数组
        input.clear();
        for (size_t k = 0; k < 10; k++)//10个桶
        {
            for (int item: bucket[k])
            {
                input.push_back(item);//分别将每个桶中的元素倒进原数组
            }
        }

    }
}

void PrintArray(vector<int>& input)//打印数组
{
    for (int item : input)
    {
        cout << item << ",";
    }
    cout << "\n";
}

int main()
{
    vector<int> array = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };

    cout << "Before Sort:\n";
    PrintArray(array);

    //冒泡排序
    //BobbleSort(array);

    //选择排序
    //SectionSort(array);

    //插入排序
    //InsertionSort(array);

    //快速排序
    QuickSortStart(array);

    //计数排序
    //CountingSort(array);

    //桶排序
    //BucketSort(array);

    //希尔排序
    //ShellSort(array);

    //归并排序
    //MergeSortStart(array);

    //堆排序
    //HeapSort(array);

    //基数排序
    //RadixSort(array);

    cout << "After Sort:\n";
    PrintArray(array);
}