#include <iostream>
#include "TList.h"
#include "TMonom.h"
#include "TPolinom.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "������� �������:" << endl;
    string str;
    cin >> str;

    TPolinom p1(str);

    double x, y, z;
    std::cout << "������� �������� x, y, z ��� ���������� �������� � �����:" << std::endl;
    std::cin >> x >> y >> z;

    TPolinom resultPoint = p1.CalcPoint(x, y, z);
    std::cout << "��������� ���������� �������� � ����� (" << x << ", " << y << ", " << z << "): " << resultPoint.ToString() << std::endl;

    TPolinom resultDerivative = p1.Derivative();
    std::cout << "����������� ��������: " << resultDerivative.ToString() << std::endl;

    TPolinom resultIntegral = p1.Integral();
    std::cout << "�������� ��������: " << resultIntegral.ToString() << std::endl;

    cout << "������� ������ �������:" << endl;
    string str2;
    cin >> str2;

    TPolinom p2(str2);

    TPolinom res;
    res = p1 + p2;

    TPolinom res1;
    res1 = p1 - p2;

    TPolinom res2;
    res2 = p1 / p2;

    TPolinom res3;
    res3 = p1 * p2;

    double constant = 5.0;
    TPolinom res4;
    res4 = p1 * constant; // ��������� �������� �� ���������

    cout << "��������� ��������: " << res.ToString() << endl;
    cout << "��������� ���������: " << res1.ToString() << endl;
    cout << "��������� �������: " << res2.ToString() << endl;
    cout << "��������� ���������: " << res3.ToString() << endl;
    cout << "��������� ��������� �� ���������: " << res4.ToString() << endl;

    return 0;
}