#pragma once
#include<iostream>
using namespace std;
#define INF 10000
struct node
{
	node* prev;
	double distance;
	int x;
	int y;
	node* next;
	node()
	{
		distance = INF;
	}
};
class pqueue {
public:
	node* front = NULL;
	node* rear = NULL;
	void enqueue(double d, int x, int y)
	{
		node* temp = new node;
		temp->distance = d;
		temp->x = x;
		temp->y = y;
		temp->prev = NULL;
		temp->next = NULL;
		if (front == NULL && rear == NULL)
		{
			rear = front = temp;
		}
		else if (front == rear)		//if only one element in queue
		{
			if (d >= front->distance)			//insert element after front
			{
				rear->next = temp;
				temp->prev = rear;
				rear = temp;
			}
			else
			{					//inserting element before front
				temp->next = rear;
				rear->prev = temp;
				front = temp;
			}
		}
		else
		{
			if (d >= rear->distance)		//inserting at end of queue
			{
				rear->next = temp;
				temp->prev = rear;
				rear = temp;
				return;
			}
			node* temp2 = rear;
			while (temp2 != NULL && temp2->distance > d)
			{
				temp2 = temp2->prev;		//moving back till null is reached or a node with greater value is found
			}
			if (temp2 == NULL)			//inserting at start
			{
				temp->next = front;
				front->prev = temp;
				front = temp;
			}
			else
			{								//inserting temp between temp2 and its next
				temp2->next->prev = temp;
				temp->next = temp2->next;
				temp2->next = temp;
				temp->prev = temp2;
			}
		}
	}
	void dequeue()
	{
		if (front == NULL && rear == NULL)
		{
			cout << "Queue is EMPTY!" << endl;
			return;
		}
		node* temp = front;
		if (front == rear)
		{
			front = rear = NULL;
			delete temp;
			temp = NULL;
		}
		else
		{
			front = front->next;
			front->prev = NULL;
			delete temp;
			temp = NULL;
		}
	}
	node* getFront()
	{
		return front;
	}
	void display()
	{
		if (front == NULL && rear == NULL)
		{
			cout << "Queue is EMPTY!" << endl;
			return;
		}
		node* temp = NULL;
		temp = front;
		while (temp != NULL)
		{
			cout << temp->distance << " " << temp->x << " " << temp->y << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	bool isEmpty()
	{
		if (front == NULL)
			return true;
		else
			return false;
	}
	bool exists(int i, int j) {
		node* p = front;
		while (p != NULL) {
			if (p->x == i && p->y == j)
				return true;
			p = p->next;
		}
		return false;
	}
};