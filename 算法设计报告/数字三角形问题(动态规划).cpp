#include <iostream>
using namespace std;

int digit_triangle(int (*triangle)[5],int n)
{
    for(int row=n-2;row>=0;row--)
    for(int col=0;col<=row;col++)
    if(triangle[row+1][col]>triangle[row+1][col+1])
    triangle[row][col]+=triangle[row+1][col];
    else
    triangle[row][col]+=triangle[row+1][col+1];
    return triangle[0][0];
}     
int main()
{
    int n;
    cout<<"���������������ε�����:"<<endl;
    cin>>n;
    int (*array)[5];
    cout<<"������������֣�"<<endl;
    for(int i=0;i<n;i++)
    for(int j=0;j<i+1;j++)
    cin>>array[i][j]; 
    int result;
    result = digit_triangle(array, n); 
    cout <<"���ֵΪ��"<<result << endl;
    system("pause");
    return 0;
}                                    

