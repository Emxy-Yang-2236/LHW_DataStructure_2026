#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

// 使用复数库
typedef complex<double> cd;
const double PI = acos(-1.0);

/**
 * 辅助函数：位逆序置换 (Bit-reversal Permutation)
 * 将数组下标按照二进制翻转排序，为迭代版 FFT 做准备
 */
void change(vector<cd> &a, int n) {
    for (int i = 1, j = n / 2; i < n - 1; i++) {
        if (i < j) swap(a[i], a[j]);
        int k = n / 2;
        while (j >= k) {
            j -= k;
            k /= k ? 2 : 1; // 防止除0，逻辑上等同于 k >>= 1
            if (k == 0) break;
        }
        if (j < k) j += k;
    }
}

/**
 * 核心 FFT 实现 (支持正变换和逆变换)
 * type == 1 为 DFT, type == -1 为 IDFT
 */
void fft(vector<cd> &a, int n, int type) {
    change(a, n);
    for (int h = 2; h <= n; h <<= 1) {
        cd wn(cos(2 * PI / h), type * sin(2 * PI / h));    //w_n = e^((2*pi*i)/n)
        for (int j = 0; j < n; j += h) {
            cd w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                cd u = a[k];
                cd t = w * a[k + h / 2];
                a[k] = u + t;
                a[k + h / 2] = u - t;
                w *= wn;
            }
        }
    }
    if (type == -1) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

// --- 按照要求分出的四个主要函数 ---

/**
 * 1. Selection: 确定采样点数量 n
 * 多项式乘积最高为 14 次(8+8-2)，所以 n 至少需要是大于 15 的 2 的幂次，即 16
 */
int Selection(int d1, int d2) {
    int n = 1;
    while (n < d1 + d2) n <<= 1;
    return n;
}

/**
 * 2. Evaluation: 系数表示法 -> 点值表示法
 */
void Evaluation(vector<cd> &A, int n) {
    fft(A, n, 1);
}

/**
 * 3. Multiplication: 点值对应相乘
 */
vector<cd> Multiplication(const vector<cd> &A_val, const vector<cd> &B_val, int n) {
    vector<cd> C_val(n);
    for (int i = 0; i < n; i++) {
        C_val[i] = A_val[i] * B_val[i];
    }
    return C_val;
}

/**
 * 4. Interpolation: 点值表示法 -> 系数表示法 (逆变换)
 */
void Interpolation(vector<cd> &C, int n) {
    fft(C, n, -1);
}

int main() {
    // 假设输入 A 和 B 各 8 项 (0次到7次)
    vector<cd> A(16, 0), B(16, 0);
    
    cout << "请输入多项式 A 的 8 个系数 (从低次到高次): " << endl;
    for (int i = 0; i < 8; i++) {
        double x; cin >> x;
        A[i] = cd(x, 0);
    }

    cout << "请输入多项式 B 的 8 个系数 (从低次到高次): " << endl;
    for (int i = 0; i < 8; i++) {
        double x; cin >> x;
        B[i] = cd(x, 0);
    }

    // --- 流程开始 ---
    
    // 1. Selection
    int n = Selection(8, 8); // n 会得到 16

    // 2. Evaluation
    Evaluation(A, n);
    Evaluation(B, n);

    // 3. Multiplication
    vector<cd> C = Multiplication(A, B, n);

    // 4. Interpolation
    Interpolation(C, n);

    // 输出结果
    cout << "\n乘积多项式的系数为 (16项):" << endl;
    for (int i = 0; i < n; i++) {
        // 取实部并四舍五入
        cout << (int)(C[i].real() + 0.5) << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}