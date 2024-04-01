#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template <class T>
class TList
{
protected:
	TNode<T>* pFirst; // ������ �����
	TNode<T>* pCurrent; // ������� �����
	TNode<T>* pPrevious; // ����� ����� �������
	TNode<T>* pLast; // ��������� �����
	TNode<T>* pStop; // �������� ���������, ����������� ����� ������
	int length; // ���������� ������� � ������

public:
	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // ������ ���� ?
	// ������� �������
	void InsertFirst(T item); // ����� ������
	void InsertCurrent(T item); // ����� ������� 
	void InsertLast(T item);  // �������� ���������

	// �������� �������
	void DeleteFirst(); // ������� ������ ����� 
	void DeleteCurrent(); // ������� ������� �����

	void GoNext(); // ����� ������ �������� �����
	// (=1 ����� ���������� GoNext ��� ���������� ����� ������)

	void Reset(); // ���������� �� ������ ������
	bool IsEnd(); // ������ �������� ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }
};

template <class T>
TList<T>::TList()
{
	pFirst = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pLast = nullptr;
	pStop = nullptr;
	length = 0;
}

template <class T>
TList<T>::~TList()
{
}

template <class T>
bool TList<T>::IsEmpty()
{
	return pFirst == nullptr;
}

template <class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* New_Node = new TNode<T>{ item, pFirst };
	pFirst = New_Node;
	if (length == 0) { pLast = pFirst; }
	length++;
}

template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (pCurrent == nullptr) throw runtime_error("Current node is null");

	TNode<T>* New_Node = new TNode<T>{ item, nullptr };
	New_Node->pNext = pCurrent->pNext;
	pCurrent->pNext = New_Node;

	if (pCurrent == pLast) {
		pLast = New_Node;
	}

	length++;
}

template <class T>
void TList<T>::DeleteFirst()
{
	if (IsEmpty()) throw runtime_error("List is empty");
	TNode<T>* temp = pFirst;
	pFirst = pFirst->pNext;
	if (pFirst == nullptr) pLast = nullptr;
	delete temp;
	length--;
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (pCurrent == nullptr) throw runtime_error("Current node is null");

	if (pCurrent == pFirst)
	{
		DeleteFirst();
		return;
	}

	if (pCurrent == pLast)
	{
		delete pCurrent;
		pPrevious->pNext = nullptr;
		pLast = pPrevious;
		pCurrent = nullptr;
	}
	else
	{
		Node<T>* temp = pCurrent;
		pCurrent = pCurrent->pNext;
		pPrevious->pNext = pCurrent;
		delete temp;
	}
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (pCurrent == nullptr)
		throw std::runtime_error("Current node is null")
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
}

template <class T>
void TList<T>::GoNext()
{
	if (pCurrent != nullptr)
	{
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;

		if (pCurrent == nullptr)
		{
			pLast = pPrevious;
		}
	}
}

template <class T>
bool TList<T>::IsEnd()
{
	return pCurrent == pStop;
}





