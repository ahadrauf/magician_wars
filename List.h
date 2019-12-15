#pragma once
#include <iostream>
#include "ListNode.h"
#include "Item.h"
using namespace std;

template <typename T>
class List
{
private:
	ListNode<T> *first;
	ListNode<T> *last;
	int size;
public:
	List();
	List(List &);
	~List();

	void insertAtFront(const T); //inserts a value at front
	void insertAtBack(T); //inserts at value at back
	void insert(T); //inserts based on value
	bool deleteAtFront();
	bool deleteAtBack();
	bool deleteElement(T); //deletes a specific element
	bool isEmpty();
	void print(); //prints list
	void reverse();
	int getSize();
	T getLast();
	T &operator[] (const int &);
};

template <typename T>
List<T>::List()
{
	first = last = NULL;
	size = 0;
}

template <typename T>
List<T>::List(List &obj)
{
	if (obj.isEmpty())
	{
		first = last = NULL;
		size = 0;
	}
	else
	{
		size = 0;
		first = last = NULL;
		ListNode<T> *currentPtr = obj.first;
		for (int i = 0; i < obj.size; i++)
		{
			insertAtBack(currentPtr->data); 
			currentPtr = currentPtr->next;
		}

	}

}

template <typename T>
List<T>::~List()
{
	if (!isEmpty())
	{
		ListNode<T> *currentPtr = first;
		ListNode<T> *tempPtr;
		while (currentPtr)
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete tempPtr;
		}
	}
}

template <typename T>
void List<T>::insertAtFront(const T value)
{
	ListNode<T> *newPtr = new ListNode<T>(value);
	if (isEmpty())
		first = last = newPtr;
	else
	{
		newPtr->next = first;
		first = newPtr;
	}
	size++;
}


template <typename T>
void List<T>::insertAtBack(T value)
{
	ListNode<T> *newPtr = new ListNode<T>(value);
	if (isEmpty())
		first = last = new ListNode<T>(value);
	else
	{
		last->next = newPtr;
		last = newPtr;
	}
	size++;
}

template <typename T>
void List<T>::insert(T value)
{
	ListNode<T> *newPtr = new ListNode<T>(value);
	if (!first)
		first = last = newPtr;
	else
	{
		ListNode<T> *prevPtr = NULL;
		ListNode<T> *currentPtr = first;
		while (currentPtr && newPtr->data > currentPtr->data)
		{
			prevPtr = currentPtr;
			currentPtr = currentPtr->next;
		}
		if (!prevPtr)
		{
			newPtr->next = first;
			first = newPtr;
		}
		else
		{
			prevPtr->next = newPtr;
			newPtr->next = currentPtr;
			if (!currentPtr)
				last = newPtr;
		}
	}
	size++;
}

template <typename T>
bool List<T>::deleteAtFront()
{
	if (isEmpty())
		return false;
	else
	{
		ListNode<T> *temp = first;
		if (first == last)
			first = last = NULL;
		else
			first = first->next;
		delete temp;
		size--;
		return true;
	}
}

template <typename T>
bool List<T>::deleteAtBack()
{
	if (isEmpty())
		return false;
	else
	{
		ListNode<T> *tempPtr = last;
		if (first == last)
			first = last = NULL;
		else
		{
			ListNode<T> *current = first;
			while (current->next != last)
				current = current->next;
			last = current;
			current->next = NULL;
		}
		delete tempPtr;
		size--;
		return true;
	}
}

template <typename T>
bool List<T>::deleteElement(T obj)
{
	if (!first)
	{
		return false;
	}
	else
	{
		if (*first == ListNode<T>(obj))
		{
			deleteAtFront();
			insertAtFront(obj);
			return true;
		}
		ListNode<T> *prevPtr = NULL;
		ListNode<T> *currentPtr = first;
		while (prevPtr != last)
		{
			if (*currentPtr == obj)
			{
				prevPtr->next = currentPtr->next;
				delete currentPtr;
				return true;
			}
			else
			{
				prevPtr = currentPtr;
				currentPtr = currentPtr->next;
			}
		}
	}
	return false;
}

template <>
bool List<Item *>::deleteElement(Item * obj)
{
	if (!first)
	{
		return false;
	}
	else
	{
		if (*first == ListNode<Item *>(obj))
		{
			deleteAtFront();
			return true;
		}
		ListNode<Item *> *prevPtr = NULL;
		ListNode<Item *> *currentPtr = first;
		while (prevPtr != last)
		{
			if (*currentPtr == obj)
			{
				prevPtr->next = currentPtr->next;
				delete currentPtr;
				return true;
			}
			else
			{
				prevPtr = currentPtr;
				currentPtr = currentPtr->next;
			}
		}
	}
	return false;
}

template <>
bool List<Skill *>::deleteElement(Skill * obj)
{
	if (!first)
	{
		return false;
	}
	else
	{
		if (*first == ListNode<Skill *>(obj))
		{
			deleteAtFront();
			insertAtFront(obj);
			return true;
		}
		ListNode<Skill *> *prevPtr = NULL;
		ListNode<Skill *> *currentPtr = first;
		while (prevPtr != last)
		{
			if (*currentPtr == obj)
			{
				prevPtr->next = currentPtr->next;
				delete currentPtr;
				return true;
			}
			else
			{
				prevPtr = currentPtr;
				currentPtr = currentPtr->next;
			}
		}
	}
	return false;
}

template <typename T>
void List<T>::print()
{
	if (isEmpty())
	{
		cout << "You have no items!" << endl;
	}
	else
	{
		ListNode<T> *current = first;
		while (current)
		{
			cout << current->getData();
			current = current->next;
		}
		delete current;
		cout << endl;
	}
}


template <typename T>
bool List<T>::isEmpty()
{
	return !first;
}

template <typename T>
void List<T>::reverse()
{
	List temp;
	if (isEmpty())
	{
		temp.first = temp.last = NULL;
		temp.size = 0;
	}
	else
	{
		ListNode<T> *currentPtr = first;
		for (int i = 0; i < size; i++)
		{
			temp.insertAtFront(currentPtr->getData());
			currentPtr = currentPtr->next;
		}
	}
	for (int i = 0; i < size + 1; i++)
		deleteAtFront();
	if (temp.isEmpty())
	{
		first = last = NULL;
		size = 0;
	}
	else
	{
		ListNode<T> *currentPtr = temp.first;
		for (int i = 0; i < temp.size; i++)
		{
			insertAtBack(currentPtr->getData());
			currentPtr = currentPtr->next;
		}
	}
}

template <typename T>
T List<T>::getLast()
{
	return last->data;
}

template <>
Skill *List<Skill *>::getLast() //specialized template for Skill *
{
	return last->data;
}

template <typename T>
int List<T>::getSize()
{
	return size;
}

template <typename T>
T &List<T>::operator[] (const int &sub) //overloaded [] operator
{
	if (sub < 1 || sub > size)
	{
		cout << "This input is invalid." << endl;
		exit(0);
	}
	else
	{
		ListNode<T> *ptr = first;
		for (int i = 1; i < sub; i++)
		{
			ptr = ptr->next;
		}
		return ptr->data;
	}
}