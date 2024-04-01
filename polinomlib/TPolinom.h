#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
using namespace std;

const double EPSILON = 1e-6;

class TPolinom
{
private:
    vector<TMonom> monomList;

public:
    TPolinom();
    TPolinom(TPolinom& other);
    TPolinom(std::string str);
    TPolinom& operator=(TPolinom& other);
    TPolinom operator+(TPolinom& q);
    TPolinom operator-(TPolinom& q);
    TPolinom operator*(double coef);
    TPolinom operator*(TPolinom& other);
    TPolinom operator/(TPolinom& other);
    TPolinom CalcPoint(double x, double y, double z);
    TPolinom Derivative();
    TPolinom Integral();

    void AddMonom(TMonom newMonom);
    TPolinom MultMonom(TMonom monom);
    bool IsZero() const;
    std::string ToString();
};

TPolinom::TPolinom()
{
    // �����������
}

TPolinom::TPolinom(TPolinom& other)
{
    // ����������� �����������
    this->monomList = other.monomList;
}

TPolinom::TPolinom(std::string str)
{
    size_t pos = 0;
    while (pos < str.length()) {
        double coef = 0.0;
        int degX = 0, degY = 0, degZ = 0;
        char var;
        if (isdigit(str[pos]) || str[pos] == '-' || str[pos] == '+') {
            size_t nextPos;
            coef = stod(str.substr(pos), &nextPos);
            pos += nextPos;
        }
        while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'X' ||
            str[pos] == 'y' || str[pos] == 'Y' ||
            str[pos] == 'z' || str[pos] == 'Z')) {
            var = tolower(str[pos]);
            pos++;
            if (pos < str.length() && str[pos] == '^') {
                pos++;
                size_t nextPos;
                int deg = stoi(str.substr(pos), &nextPos);
                pos += nextPos;
                switch (var) {
                case 'x': degX = deg; break;
                case 'y': degY = deg; break;
                case 'z': degZ = deg; break;
                }
            }
            else {
                switch (var) {
                case 'x': degX = 1; break;
                case 'y': degY = 1; break;
                case 'z': degZ = 1; break;
                }
            }
        }
        this->AddMonom(TMonom(coef, degX, degY, degZ));
    }
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
    if (this != &other) {
        monomList.clear();
        for (const TMonom& monom : other.monomList) {
            monomList.push_back(monom);
        }
    }
    return *this;
}

void TPolinom::AddMonom(TMonom m)
{
    if (m.GetCoef() == 0) {
        throw std::invalid_argument("����������� �� ������ ���� ����� ����.");
    }
    bool isAdded = false;
    for (TMonom& monom : monomList) {
        if (monom == m) {
            monom.SetCoef(monom.GetCoef() + m.GetCoef());
            if (fabs(monom.GetCoef()) < EPSILON) {
                // �������� ������, ���� ����������� ���� ����� ����
                monomList.erase(std::remove(monomList.begin(), monomList.end(), monom), monomList.end());
            }
            isAdded = true;
            break;
        }
    }
    if (!isAdded) {
        monomList.push_back(m);
        // ���������� ������ ������� �� �������� ��������
        std::sort(monomList.begin(), monomList.end(), [](const TMonom& a, const TMonom& b) {
            return a < b; // ����� ������ ���� ���������� ������� ��������� �������
            });
    }
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
    TPolinom result;
    for (const TMonom& m : monomList) {
        TMonom multipliedMonom = m * monom;
        result.AddMonom(multipliedMonom);
    }
    return result;
}

TPolinom TPolinom::operator+(TPolinom& other)
{
    TPolinom result(*this); // ������� ����� ������, ������� �������
    for (const TMonom& monom : other.monomList) {
        result.AddMonom(monom);
    }
    return result; // ���������� ����� ������ � ������������ ��������
}

TPolinom TPolinom::operator-(TPolinom& other)
{
    TPolinom result(*this); // ������� ����� ������, ������� �������
    for (const TMonom& monom : other.monomList) {
        TMonom negatedMonom = monom;
        negatedMonom.coef *= -1; // ����������� ����������� ��� �������� ���������
        result.AddMonom(negatedMonom); // ��������� ����� � ��������������� �������������
    }
    return result; // ���������� ����� ������ � ���������� ��������
}

TPolinom TPolinom::operator*(double coef)
{
    for (TMonom& monom : monomList) {
        monom.coef *= coef;
    }
    return *this;
}

TPolinom TPolinom::operator*(TPolinom& other)
{
    TPolinom result;
    for (const TMonom& m1 : monomList) {
        for (const TMonom& m2 : other.monomList) {
            TMonom multipliedMonom = m1 * m2;
            result.AddMonom(multipliedMonom);
        }
    }
    return result;
}

TPolinom TPolinom::operator/(TPolinom& other)
{
    if (other.IsZero()) {
        throw std::invalid_argument("������� �� ���� ���������.");
    }

    if (monomList.size() < other.monomList.size()) {
        return TPolinom(); // ���������� ������� �������, ��� ��� ������� ������ ��������
    }

    TPolinom result;
    TPolinom cur(*this);

    while (!cur.IsZero() && cur.monomList[0].GetDegX() >= other.monomList[0].GetDegX()) {
        double coef = cur.monomList[0].GetCoef() / other.monomList[0].GetCoef();
        int degX = cur.monomList[0].GetDegX() - other.monomList[0].GetDegX();
        int degY = cur.monomList[0].GetDegY() - other.monomList[0].GetDegY();
        int degZ = cur.monomList[0].GetDegZ() - other.monomList[0].GetDegZ();

        TMonom divMonom(coef, degX, degY, degZ);
        result.AddMonom(divMonom);

        TPolinom temp = other.MultMonom(divMonom);
        cur = cur - temp;
    }

    return result;
}

bool TPolinom::IsZero() const
{
    return monomList.empty();
}

string TPolinom::ToString()
{
    string result;
    for (const TMonom& monom : monomList) {
        result += monom.ToString() + " ";
    }
    return result;
}
