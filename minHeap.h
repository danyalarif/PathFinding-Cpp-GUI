#pragma once
#include<iostream>

using namespace std;

struct Edge		//struct for holding an edge
{
	int source;
	int destination;
	int weight;
};
class MinHeap
{
private:
	Edge* heap;		//heap array
	int nodes;		//total size
	int last;		//pointer to last element
public:
	MinHeap()
	{
		nodes = 5;
		heap = new Edge[nodes];		//creating an array of edges
		last = -1;
	}
	MinHeap(int size)
	{
		nodes = size;
		heap = new Edge[nodes];
		last = -1;
	}
	void swap(int index1, int index2)		//swapping two edges by deep copy
	{
		Edge temp;
		temp.source = heap[index1].source;
		temp.destination = heap[index1].destination;
		temp.weight = heap[index1].weight;
		heap[index1].source = heap[index2].source;
		heap[index1].destination = heap[index2].destination;
		heap[index1].weight = heap[index2].weight;
		heap[index2].source = temp.source;
		heap[index2].destination = temp.destination;
		heap[index2].weight = temp.weight;
	}
	void insert(int source, int destination, int weight)
	{
		Edge temp;		//initilazing an edge
		temp.source = source;
		temp.destination = destination;
		temp.weight = weight;		//if heap empty
		if (last == -1)
		{
			last++;
			heap[last] = temp;
		}
		else if (last == nodes - 1)
		{
			cout << "No space" << endl;
		}
		else
		{
			last++;
			heap[last] = temp;
			int key = last;
			int parent = (key - 1) / 2;		//getting parent
			while (parent >= 0 && heap[key].weight < heap[parent].weight)		//placing at correct positions
			{
				swap(parent, key);
				key = parent;
				parent = (key - 1) / 2;
			}
		}
	}
	bool isEmpty()
	{
		if (last == -1)
			return true;
		else
			return false;
	}
	int getMin(int a, int b)
	{
		if (heap[a].weight < heap[b].weight)
			return a;
		else
			return b;
	}
	Edge getTop()
	{
		return heap[0];
	}
	void deleteMin()
	{
		heap[0] = heap[last];
		last--;
		int current = 0;
		int leftChild = (2 * current) + 1;		//index of left child
		int rightChild = (2 * current) + 2;		//index of right child
		int minChild = getMin(leftChild, rightChild);		//index of Min child 
		//Heapify
		while (current < last && heap[minChild].weight < heap[current].weight)
		{
			swap(current, minChild);
			current = minChild;		//updating the current; Current moves to the position of the node that was swapped
			leftChild = (2 * current) + 1;
			rightChild = (2 * current) + 2;
			if (leftChild < last && rightChild < last)		//if both children exist
			{
				minChild = getMin(leftChild, rightChild);
			}
			else if (leftChild < last)		//if only left child exists
			{
				minChild = leftChild;
			}
			else if (rightChild < last)		//if only right child exists
			{
				minChild = rightChild;
			}
			else
			{
				break;		//if no children exist
			}
		}
	}
	bool exists(int source, int destination, int weight)
	{
		for (int i = 0; i < nodes; i++)
		{
			if (heap[i].source == source && heap[i].destination == destination && heap[i].weight == weight)		
				return true;
		}
		return false;
	}
};