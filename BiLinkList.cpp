/*
Сделать двусвязный список не используя классы, 
с добавлением в конец, 
неупорядоченный, 
без повторов, 
с удалением заданного, 
с операцией симметрическая разность. 

Указатели храним голова-хвост, симметрическая разность. 
Должна быть проверка на пустоту списка. 
Добавление в пустой-непустой, 
удаление из пустого и не пустого.
*/

#include <iostream>
using namespace std;

//Элемент  списка
typedef struct Element
{
	int value; //Значение
	Element * next;//две ссылки
	Element * prev;
} Element;


typedef struct BiList
{
	Element * first; //Начало
	Element * last; //Конец
} BiList;

Element * NewElement(int value) //Создать элемент с заданным значением ключа
{
	Element * result = new Element();
	result->value = value;
	result->next = result->prev = NULL;
	return result;
}

//Проверка на пустой список
bool IsEmpty(BiList &L)
{
	return L.first == NULL;
}

//Найти в списке
Element * Find(BiList &L, int value)
{
	Element * e = L.first;
	while (e)
		if (e->value == value) return e;
		else e = e->next;
		return NULL; //Не найден
}

//Вывести на экран
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

void ReversePrint(BiList &L) // наоборот
{
    Element * e = L.last;
    while (e)
    {
        cout << e->value << " ";
        e = e->prev;
    }
    cout << endl;
}

//Добавить в пустой список
void AddToEmpty(BiList &L, Element * e)
{
	L.first = L.last = e;
}

//Добавить в начало
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

//Добавить в конец
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

//удаление заданного (неважно, пустой список или нет)
void Remove(BiList &L, int value)
{
	Element * e = Find(L,value);
	if (!e) return; //Нет такого

	if (e->prev)
		e->prev->next = e->next;
	else //Это начало списка!
		L.first = e->next;

	if (e->next)
		e->next->prev = e->prev;
	else //Конец
		L.last = e->prev;
	delete e; //Освободить память
	return;
}

//Очистить список
void Clear(BiList &L)
{
	while (!IsEmpty(L)) Remove(L, L.first->value);
}

//операция симметрическая разность
//Это множество, состоящее в точности из тех элементов, 
//которые принадлежат ровно одному из множеств: либо A, либо B.
void Symmetric(BiList &A, BiList &B, BiList &result)
{
	Clear(result);
	Element * e;
	//Для каждого элемента из A если его нет в B - добавить
	e = A.first;
	while (e)
	{
		if (!Find(B, e->value))
			AddLast(result, e->value);
		e = e->next; 
	}
	//Для каждого элемента из B если его нет в A - добавить
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
	system("chcp 1251>nul"); //Кириллическая кодировка Windows
	BiList L1{ NULL,NULL};
	BiList L2{ NULL,NULL};
	BiList S{ NULL,NULL};
	//Заполнить L1
	int I1[] = { 1,2,3,4,5,6,666,7,8,9,0,1,2}; //1,2 повторно не должны появиться
	for (int k = 0; k < sizeof(I1) / sizeof(int); k++)
		AddLast(L1, I1[k]);
        //if (!AddLast(L1, I1[k])) cout << "Повтор " << I1[k] << endl; // я теперь не могу вывести повтор :(((
	cout << "Первый список" << endl;
	Print(L1);
	cout << endl;
	cout << "Первый список после удаления 666" << endl;
	Remove(L1, 666);
	Print(L1);
    ReversePrint(L1);
	cout << endl;
	//Заполнить L2
	int I2[] = { 1,2,3,4,5,16,17,18,19,10 };
	for (int k = 0; k < sizeof(I2) / sizeof(int); k++)
		AddLast(L2, I2[k]);
	cout << "Второй список" << endl;
	Print(L2);
    ReversePrint(L2);
	cout << endl;
	//Разность
	Symmetric(L1, L2, S);
	cout << "Симметрическая разность" << endl;
	Print(S);
	cout << endl;
	cin.get();
}