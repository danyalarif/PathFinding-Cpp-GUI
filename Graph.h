#pragma once
#include<iostream>
#include "pqueue.h"
#include "Stack.h"
#include "minHeap.h"
#include <wx/grid.h>
using namespace std;
#define INF 10000
class Graph
{
private:
	int nodes;		//total vertices
	int** grid;			//adjancey matrix
public:
	const double d = 1;		//non-diganol distance
	const double dd = 1.4;		//diganol distance
	bool instant = false;		//determine max speed
	Graph()			//Default constructor
	{
		nodes = 5;
		grid = new int* [nodes];		//Creating 2d array
		for (int i = 0; i < nodes; i++)		//Inializing memory for each segment
		{
			grid[i] = new int[nodes];
		}
	}
	Graph(int s)		//Argument constructor
	{
		nodes = s;
		grid = new int* [nodes];
		for (int i = 0; i < nodes; i++)
		{
			grid[i] = new int[nodes];
		}
	}
	void setVertices(int s)		//Creating grid
	{
		nodes = s;
		grid = new int* [nodes];
		for (int i = 0; i < nodes; i++)
		{
			grid[i] = new int[nodes];
		}
	}
	int getNodes()
	{
		return nodes;
	}
	int** getGrid()
	{
		return grid;
	}
	int getEdge(int i, int j)
	{
		return grid[i][j];
	}
	void fillGrid()		//Default grid
	{
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				grid[i][j] = 1;
			}
		}
	}
	void printGrid()
	{
		for (int i = 0; i < nodes; i++)
		{
			cout << "Row: " << i << endl;
			for (int j = 0; j < nodes; j++)
			{
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
	}
	void insertEdge(int source, int destination, int weight)		//inserting weights
	{
		grid[source][destination] = weight;
	}
	void printEdges()
	{
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (grid[i][j] != 0)
					cout << i << " -> " << j << " = " << grid[i][j] << endl;
			}
		}
	}
	bool isValid(int i)		//checking the validaty of 
	{
		if (i >= 0 && i < nodes)
			return true;
		else
			return false;
	}
	bool dijkstra(wxGrid* displayGrid,int sourceX, int sourceY, int destinationX, int destinationY)
	{
		//priority queues for keeping distances
		//a priority queue with 3 items can be used and only the first item that is distance should be compared for sorting it
		pqueue pq;
		bool pathfound = false;			
		int vertices = nodes;
		double** distances = new double* [vertices];		//for storing temp. distances of each nodes from itself to source
		for (int i = 0; i < vertices; i++)
		{
			distances[i] = new double[vertices];
		}
		//for storing distances of source nodes to others
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				distances[i][j] = INF;		//initial distance will be infinity
			}
		}
		distances[sourceX][sourceY] = 0;		//distance of source node to itself is always 0
		bool** visited = new bool* [vertices];			//for storing visited nodes
		for (int i = 0; i < vertices; i++)
		{
			visited[i] = new bool[vertices];
		}
		//for storing nodes that have been visisted
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				visited[i][j] = false;
			}
		}
		visited[sourceX][sourceY] = true;
		int** prev = new int* [vertices];			//for storing parent of each node
		for (int i = 0; i < vertices; i++)
		{
			prev[i] = new int[vertices];
		}
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				prev[i][j] = -1;		//initially nodes will have no parents
			}
		}
		int i = 0;
		int j = 0;
		pq.enqueue(0, sourceX, sourceY);		//putting the source node in priority queue
		while (!(pq.isEmpty()))			//till queue gets empty
		{
			node* current = NULL;
			current = pq.getFront();		//getting node with min distance from the queue
			i = current->x;
			j = current->y;
			pq.dequeue();				//deleting
			if (i == destinationX && j == destinationY)		//if path is found
			{
				pathfound = true;
				break;
			}
			//Checking all 8 adjacent vertices
			//Checking for validatity of vertex whether it exists also the new distance to that node must be smaller than the previously assinged node
			//Top Left
			if (isValid(i - 1) && isValid(j - 1) && grid[i - 1][j - 1] == 1 && (!visited[i - 1][j - 1]) && (distances[i - 1][j - 1] > distances[i][j] + dd))
			{
				distances[i - 1][j - 1] = distances[i][j] + dd;			//Updating distance
				prev[i - 1][j - 1] = (i * 1000) + j;				//Updating the parent - Storing parent as 1D coordinate
				pq.enqueue(distances[i - 1][j - 1], i - 1, j - 1);			//putting the node in queue
			}
			//Left
			if (isValid(j - 1) && grid[i][j - 1] == 1 && (!visited[i][j - 1]) && (distances[i][j - 1] > distances[i][j] + d))
			{
				distances[i][j - 1] = distances[i][j] + d;
				prev[i][j - 1] = (i * 1000) + j;
				pq.enqueue(distances[i][j - 1], i, j - 1);
			}
			//Bottom Left
			if (isValid(i + 1) && isValid(j - 1) && grid[i + 1][j - 1] == 1 && (!visited[i + 1][j - 1]) && (distances[i + 1][j - 1] > distances[i][j] + dd))
			{
				distances[i + 1][j - 1] = distances[i][j] + dd;
				prev[i + 1][j - 1] = (i * 1000) + j;
				pq.enqueue(distances[i + 1][j - 1], i + 1, j - 1);
			}
			//Top
			if (isValid(i - 1) && grid[i - 1][j] == 1 && (!visited[i - 1][j]) && (distances[i - 1][j] > distances[i][j] + d))
			{
				distances[i - 1][j] = distances[i][j] + d;
				prev[i - 1][j] = (i * 1000) + j;			
				pq.enqueue(distances[i - 1][j], i - 1, j);
			}
			//Bottom
			if (isValid(i + 1) && grid[i + 1][j] == 1 && (!visited[i + 1][j])  && (distances[i + 1][j] > distances[i][j] + d))
			{
				distances[i + 1][j] = distances[i][j] + d;
				prev[i + 1][j] = (i * 1000) + j;
				pq.enqueue(distances[i + 1][j], i + 1, j);
			}
			//Top Right
			if (isValid(i - 1) && isValid(j + 1) && grid[i - 1][j + 1] == 1 && (!visited[i - 1][j + 1]) && (distances[i - 1][j + 1] > distances[i][j] + dd))
			{
				distances[i - 1][j + 1] = distances[i][j] + dd;
				prev[i - 1][j + 1] = (i * 1000) + j;
				pq.enqueue(distances[i - 1][j + 1], i - 1, j + 1);
			}
			//Right
			if (isValid(j + 1) && grid[i][j + 1] == 1 && (!visited[i][j + 1]) && (distances[i][j + 1] > distances[i][j] + d))
			{
				distances[i][j + 1] = distances[i][j] + d;
				prev[i][j + 1] = (i * 1000) + j;	//1 1 0 0 
				pq.enqueue(distances[i][j + 1], i, j + 1);
			}
			//Bottom Right
			if (isValid(i + 1) && isValid(j + 1) && grid[i + 1][j + 1] == 1 && (!visited[i + 1][j + 1]) && (distances[i + 1][j + 1] > distances[i][j] + dd))
			{
				distances[i + 1][j + 1] = distances[i][j] + dd;
				prev[i + 1][j + 1] = (i * 1000) + j;
				pq.enqueue(distances[i + 1][j + 1], i + 1, j + 1);
			}
			if (i == sourceX && j == sourceY)
				continue;
			visited[i][j] = true;
			if (!(instant))		//checking instant speed
			{
				displayGrid->Update();
				displayGrid->Refresh(false);
			}
			else
			{
				displayGrid->Refresh();
			}
			displayGrid->SetCellBackgroundColour(i, j, wxColour("BLUE"));		//coloring the node
		}
		int u = (destinationX * 1000) + destinationY;		//Converting in 1D coordinate
		if (!(pathfound))
			return false;
		Stack s;
		while (u != -1)
		{
			int x = u / 1000;		//Converting back in 2d
			int y = u % 1000;
			s.push(x, y);		//pushing on the stack
			u = prev[x][y];		//going to parent of current
		}
		//Printing path
		while (!(s.isEmpty()))
		{
			point* current = s.getTop();
			displayGrid->SetCellBackgroundColour(current->x, current->y, wxColour("GREEN"));
			displayGrid->ForceRefresh();
			displayGrid->Update();
			s.pop();
		}
		return true;
		//exit(0);
	}
	//Detecting cycles in a 2d grid through dfs
	bool checkCycle(int** graph,bool** visited, int i, int j, int parentI, int parentJ)
	{
		if (visited[i][j])		//if current node is already visited terminate it
			return false;
		visited[i][j] = true;
		//Left
		if (isValid(j - 1))
		{
			if (visited[i][j - 1] && graph[i][j] == 1 && graph[i][j - 1] == 1 && parentI != i && parentJ != j - 1)
			{
				return true;			//if parent isn't the same as caller that is a back edge exists
			}
			else
			{
				bool flag = checkCycle(graph, visited, i, j - 1, i, j);		//If not visited check the cycle by updating parent
				if (flag)
					return true;
			}
		}
		//Top
		if (isValid(i - 1))
		{
			if (visited[i - 1][j] && graph[i][j] == 1 && graph[i - 1][j] == 1 && parentI != i - 1 && parentJ != j)
			{
				return true;
			}
			else
			{
				bool flag = checkCycle(graph, visited, i - 1, j, i, j);
				if (flag)
					return true;
			}
		}
		//Bottom
		if (isValid(i + 1))
		{
			if (visited[i + 1][j] && graph[i][j] == 1 && graph[i + 1][j] == 1 && parentI != i + 1 && parentJ != j)
			{
				return true;
			}
			else
			{
				bool flag = checkCycle(graph, visited, i + 1, j, i, j);
				if (flag)
					return true;
			}
		}
		//Right
		if (isValid(j + 1))
		{
			if (visited[i][j + 1] && graph[i][j] == 1 && graph[i][j + 1] == 1 && parentI != i && parentJ != j + 1)
			{
				return true;
			}
			else
			{
				bool flag = checkCycle(graph, visited, i, j + 1, i, j);
				if (flag)
					return true;
			}
		}
		return false;
	}
	bool isCyclic(int** graph)
	{
		bool** visited = new bool* [nodes];		//for visited nodes
		for (int i = 0; i < nodes; i++)
		{
			visited[i] = new bool[nodes];
		}
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				visited[i][j] = false;
			}
		}
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (!(visited[i][j]))		//checking cycle for each node
				{
					bool flag = checkCycle(graph, visited, i, j, -1, -1);
					if (flag)
						return true;
				}
			}
		}
		return false;
	}
	void kruskal(wxGrid* displayGrid)
	{
		MinHeap h(nodes * nodes);		//Creating a minHeap equal to amount of vertices
		int** tempGraph = new int* [nodes];		//Graph for storing obstacles
		for (int i = 0; i < nodes; i++)
		{
			tempGraph[i] = new int[nodes];
		}
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				tempGraph[i][j] = 0;
			}
		}
		for (int i = 0; i < nodes; i++)		//Assinging random weights to graph
		{
			for (int j = 0; j < nodes; j++)
			{
				grid[i][j] = 1 + (std::rand() % (100 - 1 + 1));	//random numbers in range of 1 to 100
				h.insert(i, j, grid[i][j]);
			}
		}
		int count = 0;
		int total = nodes * nodes;		//total nodes
		int rand = 1 + (std::rand() % (4 - 1 + 1));		//a random number to reduce the total number of nodes
		total = total / rand;
		while (!(h.isEmpty()) && count < total)			//generating a sort of MST
		{
			Edge current = h.getTop();			//getting the top edges from min heap
			h.deleteMin();
			tempGraph[current.source][current.destination] = 1;		//assigning edge weight
			bool res = isCyclic(tempGraph);
			if (res)		//if cycle is detected
			{
				tempGraph[current.source][current.destination] = 0;		//removing edge
			}
			count++;
		}
		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if (tempGraph[i][j] != 0)		//if exists
				{
					grid[i][j] = 0;	//blocking cell
					if (!(instant))
					{
						displayGrid->Update();
						displayGrid->Refresh(false);
					}
					else
					{
						displayGrid->Refresh();
					}
					displayGrid->SetCellBackgroundColour(i, j, wxColour("RED"));
				}
				else
				{
					grid[i][j] = 1;		//else normal edge
				}
			}
		}
	}
	int min(int a, int b)
	{
		if (a < b)
			return a;
		else
			return b;
	}
	double heuristic(int currentX, int currentY, int destinationX, int destinationY) 
	{	//calculting with diganol distances
		int dx = abs(currentX - destinationX);
		int dy = abs(currentY - destinationY);
		return 1 * (dx + dy) + (1.4 - 2 * 1) * min(dx, dy);
	}
	bool A_star(wxGrid* displayGrid, int sourceX, int sourceY, int destinationX, int destinationY)
	{
		bool pathfound = false;
		int vertices = nodes;
		pqueue openList;
		openList.enqueue(0, sourceX, sourceY);			//putting source in queue
		int** parents = new int* [vertices];		//for parents
		double** fCost = new double* [vertices];		
		double** gCost = new double* [vertices];
		double** hCost = new double* [vertices];
		bool** closedList = new bool* [vertices];		//for visited nodes
		for (int i = 0; i < vertices; i++)
		{
			parents[i] = new int[vertices];
			fCost[i] = new double[vertices];
			gCost[i] = new double[vertices];
			hCost[i] = new double[vertices];
			closedList[i] = new bool[vertices];
		}
		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				parents[i][j] = -1;
				fCost[i][j] = INF;		//initial costs
				gCost[i][j] = INF;
				hCost[i][j] = INF;
				closedList[i][j] = false;
			}
		}
		while (!(openList.isEmpty()))
		{
			node* current = NULL;
			current = openList.getFront();
			int i = current->x;
			int j = current->y;
			openList.dequeue();
			if (i == destinationX && j == destinationY)
			{
				pathfound = true;
				break;
			}
			closedList[i][j] = true;		//marking as visited
			if (!(instant))
			{
				displayGrid->Update();
				displayGrid->Refresh(false);
			}
			else
			{
				displayGrid->Refresh();
			}
			if (i != sourceX && j != sourceY)
				displayGrid->SetCellBackgroundColour(i, j, wxColour("BLUE"));
			//Generating all adjacent nodes
			if (isValid(i - 1) && isValid(j - 1) && grid[i - 1][j - 1] == 1 && !(closedList[i - 1][j - 1]))		//if not visited and not blocked
			{
				double NewhCost = heuristic(i - 1, j - 1, destinationX, destinationY);		//calculating heuristaics
				double NewgCost = gCost[i][j] + dd;		//new diganol distance
				double NewfCost = NewgCost + NewhCost;		//new function cost
				if (openList.exists(i, j))			//if node already exists in queue
				{
					if (NewfCost < fCost[i - 1][j - 1]) {		//if a smaller cost is found
						gCost[i - 1][j - 1] = NewgCost;			//updating and enqueing
						hCost[i - 1][j - 1] = NewhCost;
						fCost[i - 1][j - 1] = NewfCost;
						openList.enqueue(NewfCost, i - 1, j - 1);
						parents[i - 1][j - 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i - 1][j - 1] = NewgCost;		//direct enqueue
					hCost[i - 1][j - 1] = NewhCost;
					fCost[i - 1][j - 1] = NewfCost;
					openList.enqueue(NewfCost, i - 1, j - 1);
					parents[i - 1][j - 1] = i * 1000 + j;
				}
			}
			if (isValid(j - 1) && grid[i][j - 1] == 1 && !(closedList[i][j - 1]))
			{
				double NewhCost = heuristic(i, j - 1, destinationX, destinationY);
				double NewgCost = gCost[i][j] + d;		
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i][j - 1]) {
						gCost[i][j - 1] = NewgCost;
						hCost[i][j - 1] = NewhCost;
						fCost[i][j - 1] = NewfCost;
						openList.enqueue(NewfCost, i, j - 1);
						parents[i][j - 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i][j - 1] = NewgCost;
					hCost[i][j - 1] = NewhCost;
					fCost[i][j - 1] = NewfCost;
					openList.enqueue(NewfCost, i, j - 1);
					parents[i][j - 1] = i * 1000 + j;
				}
			}
			if (isValid(i + 1) && isValid(j - 1) && grid[i + 1][j - 1] == 1 && !(closedList[i + 1][j - 1]))
			{
				double NewhCost = heuristic(i + 1, j - 1, destinationX, destinationY);
				double NewgCost = gCost[i][j] + dd;
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i + 1][j - 1]) {
						gCost[i + 1][j - 1] = NewgCost;
						hCost[i + 1][j - 1] = NewhCost;
						fCost[i + 1][j - 1] = NewfCost;
						openList.enqueue(NewfCost, i + 1, j - 1);
						parents[i + 1][j - 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i + 1][j - 1] = NewgCost;
					hCost[i + 1][j - 1] = NewhCost;
					fCost[i + 1][j - 1] = NewfCost;
					openList.enqueue(NewfCost, i + 1, j - 1);
					parents[i + 1][j - 1] = i * 1000 + j;
				}
			}
			if (isValid(i - 1) && grid[i - 1][j] == 1 && !(closedList[i - 1][j]))
			{
				double NewhCost = heuristic(i - 1, j, destinationX, destinationY);
				double NewgCost = gCost[i][j] + d;		
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i - 1][j]) {
						gCost[i - 1][j] = NewgCost;
						hCost[i - 1][j] = NewhCost;
						fCost[i - 1][j] = NewfCost;
						openList.enqueue(NewfCost, i - 1, j);
						parents[i - 1][j] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i - 1][j] = NewgCost;
					hCost[i - 1][j] = NewhCost;
					fCost[i - 1][j] = NewfCost;
					openList.enqueue(NewfCost, i - 1, j);
					parents[i - 1][j] = i * 1000 + j;
				}
			}
			if (isValid(i + 1) && grid[i + 1][j] == 1 && !(closedList[i + 1][j]))
			{
				double NewhCost = heuristic(i + 1, j, destinationX, destinationY);
				double NewgCost = gCost[i][j] + d;
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i + 1][j]) {
						gCost[i + 1][j] = NewgCost;
						hCost[i + 1][j] = NewhCost;
						fCost[i + 1][j] = NewfCost;
						openList.enqueue(NewfCost, i + 1, j);
						parents[i + 1][j] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i + 1][j] = NewgCost;
					hCost[i + 1][j] = NewhCost;
					fCost[i + 1][j] = NewfCost;
					openList.enqueue(NewfCost, i + 1, j);
					parents[i + 1][j] = i * 1000 + j;
				}
			}
			if (isValid(i - 1) && isValid(j + 1) && grid[i - 1][j + 1] == 1 && !(closedList[i - 1][j + 1]))
			{
				double NewhCost = heuristic(i - 1, j + 1, destinationX, destinationY);
				double NewgCost = gCost[i][j] + dd;
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i - 1][j + 1]) {
						gCost[i - 1][j + 1] = NewgCost;
						hCost[i - 1][j + 1] = NewhCost;
						fCost[i - 1][j + 1] = NewfCost;
						openList.enqueue(NewfCost, i - 1, j + 1);
						parents[i - 1][j + 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i - 1][j + 1] = NewgCost;
					hCost[i - 1][j + 1] = NewhCost;
					fCost[i - 1][j + 1] = NewfCost;
					openList.enqueue(NewfCost, i - 1, j + 1);
					parents[i - 1][j + 1] = i * 1000 + j;
				}
			}
			if (isValid(j + 1) && grid[i][j + 1] == 1 && !(closedList[i][j + 1]))
			{
				double NewhCost = heuristic(i, j + 1, destinationX, destinationY);
				double NewgCost = gCost[i][j] + d;
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i][j + 1]) {
						gCost[i][j + 1] = NewgCost;
						hCost[i][j + 1] = NewhCost;
						fCost[i][j + 1] = NewfCost;
						openList.enqueue(NewfCost, i, j + 1);
						parents[i][j + 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i][j + 1] = NewgCost;
					hCost[i][j + 1] = NewhCost;
					fCost[i][j + 1] = NewfCost;
					openList.enqueue(NewfCost, i, j + 1);
					parents[i][j + 1] = i * 1000 + j;
				}
			}
			if (isValid(i + 1) && isValid(j + 1) && grid[i + 1][j + 1] == 1 && !(closedList[i + 1][j + 1]))
			{
				double NewhCost = heuristic(i + 1, j + 1, destinationX, destinationY);
				double NewgCost = gCost[i][j] + dd;
				double NewfCost = NewgCost + NewhCost;
				if (openList.exists(i, j))
				{
					if (NewfCost < fCost[i + 1][j + 1]) {
						gCost[i + 1][j + 1] = NewgCost;
						hCost[i + 1][j + 1] = NewhCost;
						fCost[i + 1][j + 1] = NewfCost;
						openList.enqueue(NewfCost, i + 1, j + 1);
						parents[i + 1][j + 1] = i * 1000 + j;
					}
				}
				else
				{
					gCost[i + 1][j + 1] = NewgCost;
					hCost[i + 1][j + 1] = NewhCost;
					fCost[i + 1][j + 1] = NewfCost;
					openList.enqueue(NewfCost, i + 1, j + 1);
					parents[i + 1][j + 1] = i * 1000 + j;
				}
			}
		}
		if (!(pathfound))
			return false;
		//printing path after loop termination
		Stack s;
		int u = destinationX * 1000 + destinationY;
		while (u != -1)
		{
			int x = u / 1000;
			int y = u % 1000;
			s.push(x, y);
			u = parents[x][y];
		}
		while (!(s.isEmpty()))
		{
			point* current = s.getTop();
			displayGrid->SetCellBackgroundColour(current->x, current->y, wxColour("GREEN"));
			displayGrid->Refresh();
			s.pop();
		}
		return true;
	}
};
