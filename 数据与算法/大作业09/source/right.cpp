#include <iostream>
#define SIZE 10001
 
using namespace std;
 
int main()
{
    int i, j, n, top, temp;
    int stack[SIZE];
    cin >> n;
 
    top = 0;
    /* ��һ��Ԫ�ؿ���Ϊ0 */
    stack[0] = -1;
    for (i = 0; i < n; i++)
    {
        cin >> temp;
        /* ��ջ��Ԫ�ش�������ջ */
        if (temp > stack[top])
        {
            stack[++top] = temp;
        }
        else
        {
            int low = 1, high = top;
            int mid;
            /* ���ּ���ջ�б�temp��ĵ�һ���� */
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
            /* ��temp�滻 */
            stack[low] = temp;
        }
    }
 
    /* �����������ջ�Ĵ�С */
    cout << top << endl;
    for(int i=0;i<top;++i)
    {
        cout<<stack[i+1]<<" ";
    }
 
    //system("pause");
    return 0;
}