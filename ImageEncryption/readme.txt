时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
A fancy square image encryption algorithm works as follow:

0. consider the image as an N x N matrix

1. choose an integer k∈ {0, 1, 2, 3}

2. rotate the square image k * 90 degree clockwise

3. if N is odd stop the encryption process

4. if N is even split the image into four equal sub-squares whose length is N / 2 and encrypt them recursively starting from step 0

Apparently different choices of the k serie result in different encrypted images. Given two images A and B, your task is to find out whether it is POSSIBLE that B is encrypted from A. B is possibly encrypted from A if there is a choice of k serie that encrypt A into B.

输入
Input may contains multiple testcases.

The first line of the input contains an integer T(1 <= T <= 10) which is the number of testcases.

The first line of each testcase is an integer N, the length of the side of the images A and B.

The following N lines each contain N integers, indicating the image A.

The next following N lines each contain N integers, indicating the image B.

For 20% of the data, 1 <= n <= 15

For 100% of the data, 1 <= n <= 100, 0 <= Aij, Bij <= 100000000

输出
For each testcase output Yes or No according to whether it is possible that B is encrypted from A.

样例输入
3
2
1 2
3 4
3 1
4 2
2
1 2
4 3
3 1
4 2
4
4 1 2 3
1 2 3 4
2 3 4 1
3 4 1 2
3 4 4 1
2 3 1 2
1 4 4 3
2 1 3 2
样例输出
Yes
No
Yes




hiho一下第114周《Image Encryption》题目分析

4
2
题目大意
给定一个长宽均为N的矩阵，可以对矩阵进行如下操作：

若N为偶数，则可以将原矩阵分割为4个长宽N/2子矩阵，并且分别对4个子矩阵进行同样的操作
将该矩阵顺时针旋转90°，180°，或270°，也可以选择不旋转
题目中有对旋转操作更详细的说明，这里不再赘述。

现在给定一对矩阵，问其中一个能否通过上述操作变换至另一个矩阵。

解题思路
首先需要发现一点："变换成"实际上是一个等价关系，A->B(A能旋转到B)意味着B->A，A->B->C意味着A->C。题目的要求就是给定两个矩阵，判断它们是不是等价的。解决这类等价问题的一个常用方法是"最小表示法"。

我们来看一个简单的"最小表示法"的例子：

给定两个长度相等的字符串S1和S2，判断是否可以通过"若干次交换S1中任意两个字符"使得S1->S2。

容易看出这里的变换规则也是一种等价关系。我们不太容易直接判断S1和S2是否等价，但是能够容易判断出S1能变换到的"字典序最小"的字符串是什么(只需要将S1的字符排序即可)。例如232112能够变成的最小字符串是112223，321221能够变换成的最小字符串也是112223，所以我们判断出132112和321221等价。



所以本题的解决思路也是一样：对于给定的两个数字矩阵，我们均计算出其最小表示，检查两个矩阵的最小表示是否相等。

首先我们需要去定义在数字矩阵中的最小字典序含义。

这里给出一个定义：对于两个数字矩阵A,B，我们从上至下、从左至右逐个元素比较。若存在一个A(i,j)<B(i,j)，则我们认为A<B。

例如下面两个例子，右边的数字矩阵就为左边矩阵的最小表示：

3 1         1 4
2 4  ====>  3 2

3 1 3 2         1 2 1 2
2 4 1 4         4 3 3 4
2 4 1 2  ====>  1 3 1 4
1 3 4 3         4 2 3 2
接下来考虑如何求解最小表示。

由于题目中可以队切割后的子矩阵进行同样的变换，因此考虑迭代完成。

先将矩阵分割为最小的单元，再逐步往上回溯，其伪代码为：

dfs(matrix, n):
  If (n is odd) Then
  // matrix为最小单元
  //         // 直接旋转当前矩阵，获取最小表示
  //                 min = matrix
  //                         tp = matrix
  //                                 For i = 1 .. 3  // 旋转3次
  //                                             tp = rotate(tp) // 旋转矩阵
  //                                                         If (min > tp) Then
  //                                                                         // 比较字典序
  //                                                                                         min = tp
  //                                                                                                     End If
  //                                                                                                             End For
  //                                                                                                                     matrix = min
  //                                                                                                                         Else
  //                                                                                                                                 // matrix可以分割
  //                                                                                                                                         // 继续切割，先处理子矩阵
  //                                                                                                                                                 dfs(sub_matrix_top_left, n / 2)
  //                                                                                                                                                         dfs(sub_matrix_top_right, n / 2)
  //                                                                                                                                                                 dfs(sub_matrix_bottom_left, n / 2)
  //                                                                                                                                                                         dfs(sub_matrix_bottom_right, n / 2)
  //                                                                                                                                                                                 // 到这一步时，原矩阵的4个子矩阵均为最小表示
  //                                                                                                                                                                                         // 此时的旋转，我们采用以块为单位旋转
  //                                                                                                                                                                                                 min = matrix
  //                                                                                                                                                                                                         tp = matrix
  //                                                                                                                                                                                                                 For i = 1 .. 3  // 旋转3次
  //                                                                                                                                                                                                                             tp = rotate_matrix(tp) // 旋转矩阵
  //                                                                                                                                                                                                                                         If (min > tp) Then
  //                                                                                                                                                                                                                                                         // 比较字典序
  //                                                                                                                                                                                                                                                                         min = tp
  //                                                                                                                                                                                                                                                                                     End If
  //                                                                                                                                                                                                                                                                                             End For
  //                                                                                                                                                                                                                                                                                                     matrix = min
  //                                                                                                                                                                                                                                                                                                         End If
  //                                                                                                                                                                                                                                                                                                         在上面的代码中rotate()函数即为简单的旋转操作。
  //
  //                                                                                                                                                                                                                                                                                                         rotate_matrix()的为块的旋转操作，其思想为将原矩阵分割为4块，进行swap而不改变子矩阵的方向：
  //
  //                                                                                                                                                                                                                                                                                                                  A(1) | A(2)
  //                                                                                                                                                                                                                                                                                                                  matrix = -----------
  //                                                                                                                                                                                                                                                                                                                           A(4) | A(3)
  //                                                                                                                                                                                                                                                                                                                           则执行rotate_matrix(matrix)变换后为：
  //
  //                                                                                                                                                                                                                                                                                                                                    A(4) | A(1)
  //                                                                                                                                                                                                                                                                                                                                    matrix = -----------
  //                                                                                                                                                                                                                                                                                                                                             A(3) | A(2)
  //                                                                                                                                                                                                                                                                                                                                             举个例子：
  //
  //                                                                                                                                                                                                                                                                                                                                              1  2  3  4         9 10  1  2
  //                                                                                                                                                                                                                                                                                                                                               5  6  7  8   =>   13 14  5  6
  //                                                                                                                                                                                                                                                                                                                                                9 10 11 12        11 12  3  4
  //                                                                                                                                                                                                                                                                                                                                                 13 14 15 16        15 16  7  8
  //                                                                                                                                                                                                                                                                                                                                                 所以rotate_matrix的操作更像是：
  //
  //                                                                                                                                                                                                                                                                                                                                                 rotate_matrix():
  //                                                                                                                                                                                                                                                                                                                                                     swap(top_left, top_right)
  //                                                                                                                                                                                                                                                                                                                                                         swap(top_right, bottom_right)
  //                                                                                                                                                                                                                                                                                                                                                             swap(bottom_right, bottom_left)
  //                                                                                                                                                                                                                                                                                                                                                             这样做的目的是为了保证每个不能分割的单元其方向不再改变。
  //
  //                                                                                                                                                                                                                                                                                                                                                             由于本题中N的数据范围不大，因此直接采用寻找最小表示的算法也能够顺利通过所有的测试数据。
  //
  //
