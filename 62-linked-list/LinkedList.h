#pragma once

#include <iostream>
#include <algorithm>

template<class T>
class LinkedList
{
private:
	struct Node										// wierzcholek
	{
		Node *prev, *next;
		T value;

		Node() { prev = next = nullptr; }
		Node(const T& _value) : value(_value) { }
		~Node() { prev = next = nullptr; }
	};
	int length;										// dlugosc listy
	Node *front, *back;								// wskaznik na poczatek i koniec listy

	virtual void delete_list();						// metoda usuwajaca liste
	virtual void merge_sort(Node*, Node*);			// funkcja pomocnicza do sortowania listy
	virtual void merge(Node*, Node*, Node*);		// funkcja pomocnicza do sortowania listy

public:
	LinkedList();									// konstruktor
	LinkedList(const LinkedList&);					// konstruktor kopiujący
	LinkedList& operator=(const LinkedList&);		// operator przypisania
	virtual ~LinkedList();							// destruktor

	virtual const Node* begin() { return front; }	// zwraca wskaznik na poczatek listy
	virtual const Node* end() { return back; }		// zwraca wskaznik na koniec listy

	virtual bool empty() { return (front); }		// sprawdza czy lista jest pusta
	virtual int size() { return length; }			// zwraca wielkosc listy

	virtual void push_front(const T&);				// wrzuca element na poczatek listy
	virtual void push_back(const T&);				// wrzuca element na koniec listy
	virtual void pop_front();						// usuwa element z poczatku listy
	virtual void pop_back();						// usuwa element z konca listy

	virtual void remove(Node*);						// usuwa element na ktory wskazuje wskaznik
	virtual void remove(const T&);					// usuwa wszystkie elementy o tej samej wartosci
	virtual void unique();							// usuwa powtorzenia elementow z listy (musi byc posortowana)
	virtual void sort();							// sortuje liste O(length * log2(length))
	virtual void reverse();							// odwraca liste
	virtual void print();							// wypisuje liste
};