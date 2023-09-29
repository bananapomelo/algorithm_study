/* 基于环形数组实现的双向队列 */
struct arrayDeque {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
};

typedef struct arrayDeque arrayDeque;

/* 构造函数 */
arrayDeque *newArrayDeque(int capacity) {
    arrayDeque *deque = (arrayDeque *)malloc(sizeof(arrayDeque));
    // 初始化数组
    deque->queCapacity = capacity;
    deque->nums = (int *)malloc(sizeof(int) * deque->queCapacity);
    deque->front = deque->queSize = 0;
    return deque;
}

/* 析构函数 */
void delArrayDeque(arrayDeque *deque) {
    free(deque->nums);
    deque->queCapacity = 0;
}

/* 获取双向队列的容量 */
int capacity(arrayDeque *deque) {
    return deque->queCapacity;
}

/* 获取双向队列的长度 */
int size(arrayDeque *deque) {
    return deque->queSize;
}

/* 判断双向队列是否为空 */
bool empty(arrayDeque *deque) {
    return deque->queSize == 0;
}

/* 计算环形数组索引 */
int dequeIndex(arrayDeque *deque, int i) {
    // 通过取余操作实现数组首尾相连
    // 当 i 越过数组尾部时，回到头部
    // 当 i 越过数组头部后，回到尾部
    return ((i + capacity(deque)) % capacity(deque));
}

/* 队首入队 */
void pushFirst(arrayDeque *deque, int num) {
    if (deque->queSize == capacity(deque)) {
        printf("双向队列已满\r\n");
        return;
    }
    // 队首指针向左移动一位
    // 通过取余操作，实现 front 越过数组头部回到尾部
    deque->front = dequeIndex(deque, deque->front - 1);
    // 将 num 添加到队首
    deque->nums[deque->front] = num;
    deque->queSize++;
}

/* 队尾入队 */
void pushLast(arrayDeque *deque, int num) {
    if (deque->queSize == capacity(deque)) {
        printf("双向队列已满\r\n");
        return;
    }
    // 计算尾指针，指向队尾索引 + 1
    int rear = dequeIndex(deque, deque->front + deque->queSize);
    // 将 num 添加至队尾
    deque->nums[rear] = num;
    deque->queSize++;
}

/* 访问队首元素 */
int peekFirst(arrayDeque *deque) {
    // 访问异常：双向队列为空
    assert(empty(deque) == 0);
    return deque->nums[deque->front];
}

/* 访问队尾元素 */
int peekLast(arrayDeque *deque) {
    // 访问异常：双向队列为空
    assert(empty(deque) == 0);
    int last = dequeIndex(deque, deque->front + deque->queSize - 1);
    return deque->nums[last];
}

/* 队首出队 */
int popFirst(arrayDeque *deque) {
    int num = peekFirst(deque);
    // 队首指针向后移动一位
    deque->front = dequeIndex(deque, deque->front + 1);
    deque->queSize--;
    return num;
}

/* 队尾出队 */
int popLast(arrayDeque *deque) {
    int num = peekLast(deque);
    deque->queSize--;
    return num;
}

/* 打印队列 */
void printArrayDeque(arrayDeque *deque) {
    int arr[deque->queSize];
    // 拷贝
    for (int i = 0, j = deque->front; i < deque->queSize; i++, j++) {
        arr[i] = deque->nums[j % deque->queCapacity];
    }
    printArray(arr, deque->queSize);
}
