/*
 * C++ Program to Convert Decimal to Binary Value
 */
 
#include<iostream>
using namespace std;
 
void binary(int num)
{
    int rem;
 
    if (num <= 1)
    {
        cout << num;
        return;
    }
    rem = num % 2;
    binary(num / 2);
    cout << rem;
}
 
int main()
{
    int dec, bin;
    cout << "Enter the number : ";
    cin >> dec;
 
    if (dec < 0)
        cout << dec << " is not a positive integer." << endl;
    else
    {
        cout << "The binary form of " << dec << " is ";
        binary(dec);
        cout << endl;
    }
    return 0;
}



/*
 * C++ program to convert binary number into decimal
 */
#include<iostream>
using namespace std;
 
int main()
{
    long bin, dec = 0, rem, num, base = 1;
 
    cout << "Enter the binary number(1s and 0s) : ";
    cin >> num;
    bin = num;
    while (num > 0)
    {
        rem = num % 10;
        dec = dec + rem * base;
        base = base * 2;
        num = num / 10;
    }
    cout << "The decimal equivalent of " << bin << " : " << dec << endl;
    return 0;
}