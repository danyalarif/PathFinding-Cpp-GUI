#pragma once
#include<iostream>

using namespace std;

struct point
{
	int x;
	int y;
	point* next;
};

class Stack
{
private:
	point* top;
public:
	Stack()
	{
		top = NULL;
	}
	void push(int x, int y)
	{
		point* temp = new point;
		temp->x = x;
		temp->y = y;
		if (top == NULL)	//if stack is empty
		{
			top = temp;
			temp->next = NULL;
			return;
		}
		temp->next = top;
		top = temp;
	}
	void pop()
	{
		if (top == NULL)
		{
			cout << "Stack is Empty!" << endl;
			return;
		}
		point* temp = top;
		top = top->next;
		delete temp;
		temp = NULL;
	}
	point* getTop()
	{
		if (top == NULL)
		{
			cout << "Stack is Empty!" << endl;
			return NULL;
		}
		else
		{
			return top;
		}
	}
	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};