//Language     : C++ 11 
//Project Name : моделирование RSA 
//Author       : nomiram 
//Created      : 09.11.2020 
//Last Modified: 03.12.2020 
//Description  : Моделирует работу алгоритма РСА. Производит шифрование и дешифровку
//#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <random> 
using namespace std;

long long getRandomNumber(long long min, long long max);
bool RabinTest(long long n, int k);
long long ModPow(long long a, long long n, long long m);
long long Euclid(long long a, long long b);
/////////////////////////////////////////////////////////////////////
//Алгоритм Евклида. Алгоритм для нахождения наибольшего
//общего делителя двух целых чисел. Используется для проверки
//чисел на взаимопростоту.
long long gcd(long long a, long long b)
{
long long c;
while (b)
{
c = a % b;
a = b;
b = c;
}
return abs(a);
}
/////////////////////////////////////////////////////////////////////
int main()
{
cout << "Please wait... Key generation process." << endl << endl;
// Генерация двух чисел и выбор двух простых чисел.
long long min = 10;
long long max = min*10;
//srand( (unsigned)time( NULL ) );
long long p=0;
long long q=0;
do{
p = getRandomNumber(min,max);
}while(RabinTest(p, 100)!=true);
do{
q = getRandomNumber(min,max);
}while((p==q)||(RabinTest(q, 100)!=true));
long long p_simple = p;
long long q_simple = q;
cout<<"p q "<<p<<" "<<q<<endl;
//Находим число n.
unsigned long long n = p_simple*q_simple;

////////////****
unsigned long long fi = ((p_simple-1)*(q_simple-1));
unsigned long long e = 17, e_simple = e;
unsigned long long d, d_simple = 0;
do{
//do{
//e = getRandomNumber(1,fi);
//}while(gcd(e, fi)!=1);
//Генерация числа d и проверка его на взаимопростоту
//с числом fi = ((p_simple-1)*(q_simple-1)).


d = Euclid(e,fi);
d_simple = gcd (d, fi );
}while(e==d);//Проверка чтобы е!=d
cout<<d<<endl;
/*******************/
//Определение числа e, для которого является истинным
//соотношение (e*d)%((p_simple-1)*(q_simple-1))=1.

//while (e_simple !=1)
//{
//e += 1;
//e_simple = (e*d)%((p_simple-1)*(q_simple-1));
cout<<"check "<<(e*d)%(fi)<<endl;
//}
//Сгенерированные ключи.
cout << '{' << setw(12) << e << ',' << setw(12) << n << '}' << " - Open key" << endl;
cout << '{' << setw(12) << d << ',' << setw(12) << n << '}' << " - Secret key" << endl << endl;
//////////////////////////////////////////////////////////////////////////////////////////////////
//Ввод шифруемых данных.
int MAX = 20;
//char *Text = new char [MAX];
string Text;
cout << "Please enter the Text. Use <Enter> button when done." << endl;
getline(cin, Text, '\n');
// cin>>Text;
cout<<Text<<endl;
MAX=Text.length();
//Массив для хранения шифротекста.
unsigned long long *CryptoText = new unsigned long long [MAX]{0};
unsigned long long *Tdecrypt   = new unsigned long long [MAX]{0};
//Получение из введённых данных десятичного кода ASCII и
//дальнейшее его преобразование по формуле ci = (mj^e)%n.
long long b = 256;
long long c;

for (int j = 0; j < MAX; j++)
{
c = 1;
unsigned long long i = 0;
int ASCIIcode = (static_cast<int>(Text[j]))+b;
//long long ASCIIcode = (static_cast<long long>(Text[j]))+b;
while (i<e)
{
c = c*ASCIIcode;
c = c%n;
i++;
}
CryptoText[j] = c;
b+=1;
}
////////////////////////////////////////////////////////////////////////////////////////////
//Расшифровка полученного кода по формуле mi = (ci^d)%n
//и перевод его в десятичный код ASCII.
b = 256;
long long m;
for (int j = 0; j < MAX; j++)
{
m = 1;
unsigned long long i = 0;
while (i<d)
{
m = m*CryptoText[j];
m = m%n;
i++;
}
m = m-b;
Tdecrypt[j] = m;
b+=1;
}
cout << endl << setw(5) << "Text" << setw(6) << "ASCII"
<< setw(20) <<"CryptoText/Block#" << setw(14)
<< "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl
<< "------------------------------------------------------------" << endl;
for (int j = 0; j < MAX; j++)
{
cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) << setw(20)
<< CryptoText[j] << "|" << setw(14)  << Tdecrypt[j] << setw(14) << static_cast<char>(Tdecrypt[j]) << endl;
}
cout<<e<<' '<<n<<endl;
for (int j = 0; j < MAX; j++)
cout<<CryptoText[j]<<' ';
//delete [] Text;
delete [] CryptoText;
delete [] Tdecrypt;
getchar();
return 0;
}

/////////////////////////////////////////////////////////////////////
///////***
bool RabinTest(long long n, int k) {
    // если n == 2 или n == 3 - эти числа простые, возвращаем true
    if (n == 2 || n == 3)
        return true;

    // если n < 2 или n четное - возвращаем false
    if (n < 2 || (unsigned long long)n % 2 == 0)
        return false;

    // представим n - 1 в виде (2^s)·t, где t нечётно, это можно сделать последовательным делением n - 1 на 2
    long long t = n - 1;

    int s = 0;

    while (t % 2 == 0)
    {
        t /= 2;
        s += 1;
    }

    // повторить k раз
    for (int i = 0; i < k; i++)
    {
        // выберем случайное целое число a в отрезке [2, n - 2]
        long long a = getRandomNumber(2, n - 2);
        // x < a^t mod n, вычислим с помощью возведения в степень по модулю
        long long x = ModPow(a, t, n);

        // если x == 1 или x == n - 1, то перейти на следующую итерацию цикла
        if (x == 1 || x == n - 1)
            continue;

        // повторить s ? 1 раз
        for (int r = 1; r < s; r++)
        {
            // x < x^2 mod n
            x = ModPow(x, 2, n);

            // если x == 1, то вернуть "составное"
            if (x == 1)
                return false;

            // если x == n - 1, то перейти на следующую итерацию внешнего цикла
            if (x == n - 1)
                break;
        }

        if (x != n - 1)
            return false;
    }

    // вернуть "вероятно простое"
    return true;
}
long long ModPow(long long a, long long n, long long m) {
    long long res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= m;
        }
        a *= (a % m);
        a %= m;
        n >>= 1;
    }
    return res % m;
}

long long getRandomNumber(long long min, long long max)
{
    static std::random_device random_device; // Источник энтропии.
    static std::mt19937 generator(random_device() * time(0)); // Генератор случайных чисел.
    std::uniform_int_distribution<> distribution(min, max); // Равномерное распределение
    long long x = distribution(generator); // Случайное число.
    return x;
}
long long Euclid(long long a, long long b)
{
	long long p1 = 1, p2 = 0, q1 = 0, q2 = 1, nod;//последовательности для нахождения коэффициентов Безу
    long long x, y;//коэффициенты Безу
    long long a1 = a, b1 = b;
    while (a && b) 
    {
        if (a >= b) {
            a = a - b;
            p1 = p1 - p2;
            q1 = q1 - q2;
        }
        else
        {
            b = b - a;
            p2 = p2 - p1;
            q2 = q2 - q1;
        }
        if (a > 0) { nod = a; }
    }//нахождение коэффициентов Безу
    if (a) {
        x = p1;
        y = q1;
    }
    else
    {
        x = p2;
        y = q2;
    } 
	if (x<=0)
	{ 
	x = (b1+x); 
	}
	return x;
}
///////***
//int _tmain(int argc, _TCHAR* argv[])
//{
//return 0;
//}
