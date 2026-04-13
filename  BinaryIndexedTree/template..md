没问题。下面我为你整理两份开箱即用的树状数组（Fenwick Tree）C++ 模板。代码结构经过优化，注重命名规范和注释说明，非常适合在比赛或刷题时直接套用。

### 一、 基础版：单点修改 + 区间查询

这是树状数组最经典、最原始的形态。它维护的是**原数组本身的信息**。

```cpp
#include <vector>

// 适用场景：修改某一个元素的值，查询某一段连续区间的和
class FenwickTree {
private:
    int n;
    std::vector<long long> tree; // 使用 long long 防止求和溢出

    // 核心位运算：提取最低位的 1
    int lowbit(int x) {
        return x & -x;
    }

public:
    // 构造函数，传入数组最大长度。注意：树状数组下标必须从 1 开始！
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    // 单点修改：将原数组中第 i 个元素加上 k
    // 时间复杂度: O(log n)
    void add(int i, long long k) {
        for (; i <= n; i += lowbit(i)) {
            tree[i] += k;
        }
    }

    // 前缀查询：求原数组前 i 个元素的和 (即 a[1] + a[2] + ... + a[i])
    // 时间复杂度: O(log n)
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

    // 区间查询：求原数组在 [L, R] 闭区间内的总和
    // 时间复杂度: O(log n)
    long long queryRange(int L, int R) {
        if (L > R) return 0;
        return query(R) - query(L - 1);
    }
};
```

---

### 二、 进阶版：区间修改 + 单点查询

要实现这个功能，我们需要引入**差分数组（Difference Array）**的思想。
假设原数组为 $a$，我们构建一个差分数组 $d$，其中 $d[i] = a[i] - a[i-1]$。
这样一来，差分数组和原数组有两个极其美妙的对应关系：
1. **原数组的单点值，等于差分数组的前缀和**：$a[x] = \sum_{i=1}^{x} d[i]$。
2. **原数组的区间 $[L, R]$ 整体加 $v$，等价于差分数组的单点修改**：只需要让 $d[L] \mathrel{+}= v$，然后让 $d[R+1] \mathrel{-}= v$。

所以，**“区间修改 + 单点查询”** 的板子，实际上就是用普通的树状数组去**维护这个差分数组 $d$**！

```cpp
#include <vector>

// 适用场景：对某一段连续区间内的所有元素同时加上一个值，查询某一个具体元素的值
class FenwickTreeDiff {
private:
    int n;
    std::vector<long long> tree; // 这里维护的是“差分数组”的树状数组

    int lowbit(int x) {
        return x & -x;
    }

    // 内部方法：对差分数组进行单点修改
    void add(int i, long long k) {
        for (; i <= n; i += lowbit(i)) {
            tree[i] += k;
        }
    }

public:
    // 构造函数
    FenwickTreeDiff(int size) : n(size), tree(size + 1, 0) {}

    // 区间修改：将原数组在 [L, R] 闭区间内的所有元素都加上 k
    // 时间复杂度: O(log n)
    void addRange(int L, int R, long long k) {
        add(L, k);         // 差分数组 L 处加上 k
        add(R + 1, -k);    // 差分数组 R+1 处减去 k
    }

    // 单点查询：求原数组中第 i 个元素的当前值
    // 时间复杂度: O(log n)
    long long queryPoint(int i) {
        long long val = 0;
        // 差分数组的前缀和，就是原数组第 i 个元素的值
        for (; i > 0; i -= lowbit(i)) {
            val += tree[i];
        }
        return val;
    }
};
```

**小贴士**：在使用进阶版时，如果原数组初始有值（不是全 0），你可以通过遍历原数组，依次调用 `addRange(i, i, a[i])` 来进行初始化建树。

掌握了这两个板子，你就已经能解决绝大多数的树状数组基础题了。其实，巧妙结合这两个思路，我们还可以利用两个树状数组推导出一个**终极版：“区间修改 + 区间查询”**。你需要我继续为你讲解这个终极版的数学推导公式和代码模板吗？