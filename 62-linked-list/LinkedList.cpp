#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList()
{
	front = back = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& oth)
{
	delete_list();
	Node * tmp = oth.front;
	while (tmp)
	{
		if (front)
		{
			back->next = new Node(tmp->value);
			back = back->next;
		}
		else
		{
			front = new Node(tmp->value);
			back = front;
		}
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& oth)
{
	if (this != &oth)
	{
		delete_list();
		LinkedList(oth);
	}
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	delete_list();
}

template<class T>
void LinkedList<T>::delete_list()
{
	if (front)
	{
		while (front != back)
		{
			front = front->next;
			delete front->prev;
		}
		delete front;
	}
}

template<class T>
void LinkedList<T>::push_front(const T& _value)
{
	length++;
	if (front)
	{
		front->prev = new Node(_value);
		front->prev->next = front;
		front = front->prev;
	}
	else
	{
		front = new Node(_value);
		back = front;
	}
}

template<class T>
void LinkedList<T>::push_back(const T& _value)
{
	length++;
	if (front)
	{
		back->next = new Node(_value);
		back->next->prev = back;
		back = back->next;
	}
	else
	{
		front = new Node(_value);
		back = front;
	}
}

template<class T>
void LinkedList<T>::pop_front()
{
	length--;
	if (front)
	{
		if (front->next)
		{
			front = front->next;
			delete front->prev;
		}
		else
		{
			delete front;
		}
	}
}

template<class T>
void LinkedList<T>::pop_back()
{
	length--;
	if (back)
	{
		if (back->prev)
		{
			back = back->prev;
			delete back->next;
		}
		else
		{
			delete back;
		}
	}
}

template<class T>
void LinkedList<T>::remove(const T& _value)
{
	Node * ptr = front;
	while (ptr)
	{
		Node * tmp = ptr;
		ptr = ptr->next;
		if (tmp->value == _value)
			remove(tmp);
	}
}

template<class T>
void LinkedList<T>::remove(Node* ptr)
{
	if (ptr->prev && ptr->next)
	{
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		Node * tmp = ptr;
		ptr = ptr->next;
		delete tmp;
	}
	else if (ptr->prev)
	{
		ptr->prev->next = nullptr;
		back = ptr->prev;
		Node * tmp = ptr;
		ptr = ptr->next;
		delete tmp;
	}
	else if (ptr->next)
	{
		ptr->next->prev = nullptr;
		front = ptr->next;
		Node * tmp = ptr;
		ptr = ptr->next;
		delete tmp;
	}
	else
	{
		delete ptr;
	}
}

template<class T>
void LinkedList<T>::unique()
{
	T last_value;
	Node * ptr = front;
	while (ptr)
	{
		Node * tmp = ptr;
		ptr = ptr->next;
		if (tmp->value == last_value)
		{
			remove(tmp);
		}
		else
		{
			last_value = tmp->value;
		}
	}
}

template<class T>
void LinkedList<T>::print()
{
	Node * ptr = front;
	while (ptr)
	{
		std::cout << ptr->value << std::endl;
		ptr = ptr->next;
	}
}

template<class T>
void LinkedList<T>::sort()
{
	merge_sort(front, back);
}

template<class T>
void LinkedList<T>::merge_sort(Node * a, Node * b)
{
	Node * ptr = a;

	int sz = 1;
	while (ptr && ptr != b)
	{
		sz++;
		ptr = ptr->next;
	}

	if (sz < 2)
		return;

	int mid = sz / 2;

	ptr = a;
	while (--mid)
		ptr = ptr->next;
	

	merge_sort(a, ptr);
	merge_sort(ptr->next, b);
	merge(a, ptr->next, b);
}

template<class T>
void LinkedList<T>::merge(Node * const a, Node * const b, Node * const c)
{
	std::vector<T> values;
	Node * ptra = a;
	Node * ptr = b;
	Node * tmp = a;
	while (ptra && ptra != b && ptr && ptr != c)
	{
		if (ptra->value < ptr->value)
		{
			values.push_back(ptra->value);
			ptra = ptra->next;
		}
		else
		{
			values.push_back(ptr->value);
			ptr = ptr->next;
		}
	}
	while (ptra && ptra != b)
	{
		values.push_back(ptra->value);
		ptra = ptra->next;
	}
	while (ptr && ptr != c)
	{
		values.push_back(ptr->value);
		ptr = ptr->next;
	}
	int i = 0;
	while (tmp != c)
	{
		tmp->value = values[i];
		tmp = tmp->next;
		i++;
	}
}

template<class T>
void LinkedList<T>::reverse()
{
	std::vector<T> values;
	Node * ptr = front;
	while (ptr)
	{
		values.push_back(ptr->value);
		ptr = ptr->next;
	}
	ptr = front;
	while (ptr)
	{
		ptr->value = values.back();
		values.pop_back();
		ptr = ptr->next;
	}
}

template class LinkedList<std::string>;