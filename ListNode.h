#pragma once
template<typename T> class List;
#include "Item.h"
#include "Skill.h"

template <typename T>
class ListNode
{
	friend class List<T>;

private:
	T data;
	ListNode *next;
public:
	ListNode(const T &);
	T getData() const;
	bool operator==(const ListNode<T> &);
};

template <typename T>
ListNode<T>::ListNode(const T &value)
	: data(value), next(0)
{

}

template <typename T>
T ListNode<T>::getData() const
{
	return data;
}


template <typename T>
bool ListNode<T>::operator==(const ListNode<T> &right)
{
	return (data == right.data) ? true : false;
}

template<>
class ListNode < Item * > //specialized template for Item *
{
	friend class List<Item *>;

private:
	Item *data;
	ListNode *next;
public:
	ListNode(Item *value)
	{
		data = value;
	}
	Item getData() const { return *data; }


	/*
	string getData() const //old getData function
	{
		char temp[50];
		_itoa_s(data->getCost(), temp, 10);
		return data->getName() + "\t\t" + data->getDescription() + "\t\t" + temp;
	}
	*/

	bool operator==(const ListNode<Item *> &right)
	{
		return (getData() == right.getData()) ? true : false;
	}
};

template<>
class ListNode < Skill * > //specialized template for Skill *
{
	friend class List<Skill *>;

private:
	Skill *data;
	ListNode *next;
public:
	ListNode(Skill *value)
	{
		data = value;
	}
	Skill getData() const { return *data; }
	bool operator==(const ListNode<Skill *> &right)
	{
		return (getData() == right.getData()) ? true : false;
	}
};