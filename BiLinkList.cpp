/*
������� ���������� ������ �� ��������� ������, 
� ����������� � �����, 
���������������, 
��� ��������, 
� ��������� ���������, 
� ��������� �������������� ��������. 

��������� ������ ������-�����, �������������� ��������. 
������ ���� �������� �� ������� ������. 
���������� � ������-��������, 
�������� �� ������� � �� �������.
*/

#include <iostream>
using namespace std;

//�������  ������
typedef struct Element
{
	int value; //��������
	Element * next;//��� ������
	Element * prev;
} Element;


typedef struct BiList
{
	Element * first; //������
	Element * last; //�����
} BiList;

Element * NewElement(int value) //������� ������� � �������� ��������� �����
{
	Element * result = new Element();
	result->value = value;
	result->next = result->prev = NULL;
	return result;
}

//�������� �� ������ ������
bool IsEmpty(BiList &L)
{
	return L.first == NULL;
}

//����� � ������
Element * Find(BiList &L, int value)
{
	Element * e = L.first;
	while (e)
		if (e->value == value) return e;
		else e = e->next;
		return NULL; //�� ������
}

//������� �� �����
void Print(BiList &L)
{
	Element * e = L.first;
	while (e)
	{
		cout << e->value << " ";
		e = e->next;
	}
	cout << endl;
}

void ReversePrint(BiList &L) // ��������
{
    Element * e = L.last;
    while (e)
    {
        cout << e->value << " ";
        e = e->prev;
    }
    cout << endl;
}

//�������� � ������ ������
void AddToEmpty(BiList &L, Element * e)
{
	L.first = L.last = e;
}

//�������� � ������
void AddFirst(BiList &L, int value)
{
	if (Find(L, value)) return;
	Element * e = NewElement(value);
	if (IsEmpty(L)) AddToEmpty(L, e); else
	{
		e->next = L.first;
		L.first->prev = e;
		L.first = e;
	}
	return;
}

//�������� � �����
void AddLast(BiList &L, int value)
{
	if (Find(L, value)) return;
	Element * e = NewElement(value);
	if (IsEmpty(L)) AddToEmpty(L, e); else
	{
		L.last->next = e;
		e->prev = L.last;
		L.last = e;
	}
	return;
}

//�������� ��������� (�������, ������ ������ ��� ���)
void Remove(BiList &L, int value)
{
	Element * e = Find(L,value);
	if (!e) return; //��� ������

	if (e->prev)
		e->prev->next = e->next;
	else //��� ������ ������!
		L.first = e->next;

	if (e->next)
		e->next->prev = e->prev;
	else //�����
		L.last = e->prev;
	delete e; //���������� ������
	return;
}

//�������� ������
void Clear(BiList &L)
{
	while (!IsEmpty(L)) Remove(L, L.first->value);
}

//�������� �������������� ��������
//��� ���������, ��������� � �������� �� ��� ���������, 
//������� ����������� ����� ������ �� ��������: ���� A, ���� B.
void Symmetric(BiList &A, BiList &B, BiList &result)
{
	Clear(result);
	Element * e;
	//��� ������� �������� �� A ���� ��� ��� � B - ��������
	e = A.first;
	while (e)
	{
		if (!Find(B, e->value))
			AddLast(result, e->value);
		e = e->next; 
	}
	//��� ������� �������� �� B ���� ��� ��� � A - ��������
	e = B.first;
	while (e)
	{
		if (!Find(A, e->value))
			AddLast(result, e->value);
		e = e->next;
	}
}


int main()
{
	system("chcp 1251>nul"); //������������� ��������� Windows
	BiList L1{ NULL,NULL};
	BiList L2{ NULL,NULL};
	BiList S{ NULL,NULL};
	//��������� L1
	int I1[] = { 1,2,3,4,5,6,666,7,8,9,0,1,2}; //1,2 �������� �� ������ ���������
	for (int k = 0; k < sizeof(I1) / sizeof(int); k++)
		AddLast(L1, I1[k]);
        //if (!AddLast(L1, I1[k])) cout << "������ " << I1[k] << endl; // � ������ �� ���� ������� ������ :(((
	cout << "������ ������" << endl;
	Print(L1);
	cout << endl;
	cout << "������ ������ ����� �������� 666" << endl;
	Remove(L1, 666);
	Print(L1);
    ReversePrint(L1);
	cout << endl;
	//��������� L2
	int I2[] = { 1,2,3,4,5,16,17,18,19,10 };
	for (int k = 0; k < sizeof(I2) / sizeof(int); k++)
		AddLast(L2, I2[k]);
	cout << "������ ������" << endl;
	Print(L2);
    ReversePrint(L2);
	cout << endl;
	//��������
	Symmetric(L1, L2, S);
	cout << "�������������� ��������" << endl;
	Print(S);
	cout << endl;
	cin.get();
}