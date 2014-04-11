#include <iostream>
#define SIZE 10001
 
using namespace std;
 
int main()
{
    int i, j, n, top, temp;
    int stack[SIZE];
    cin >> n;
 
    top = 0;
    /* 第一个元素可能为0 */
    stack[0] = -1;
    for (i = 0; i < n; i++)
    {
        cin >> temp;
        /* 比栈顶元素大数就入栈 */
        if (temp > stack[top])
        {
            stack[++top] = temp;
        }
        else
        {
            int low = 1, high = top;
            int mid;
            /* 二分检索栈中比temp大的第一个数 */
            while(low <= high)
            {
                mid = (low + high) / 2;
                if (temp > stack[mid])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            /* 用temp替换 */
            stack[low] = temp;
        }
    }
 
    /* 最长序列数就是栈的大小 */
    cout << top << endl;
    for(int i=0;i<top;++i)
    {
        cout<<stack[i+1]<<" ";
    }
 
    //system("pause");
    return 0;
}