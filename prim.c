#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "prim.h"

// ввод матрицы смежности для графа
int** input(int count_vertex, int** matrix)
{
	printf("если ребра нет длина равна 0\nукажите длину ребра между точками:\n");
	for (int i = 0; i < count_vertex; i++)
		for (int j = i; j < count_vertex; j++)
		{
			printf("%d и %d: ", i + 1, j + 1);
			scanf_s("%d", &matrix[i][j]);
			matrix[j][i] = matrix[i][j];
		}
	return matrix;
}
// вывод матрицы смежности для графа
void output(int count_vertex, int** matrix)
{
	printf("новая матрица смежности:\n");
	for (int i = 0; i < count_vertex; i++)
	{
		for (int j = 0; j < count_vertex; j++)
			printf("%4d", matrix[i][j]);
		printf("\n");
	}
}

//нахождение минимального незаписаннного ребра из вершины (минимальное ненулевое значение в строке)
int minimum(int string, int count_vertex, int** adjacency_matrix, int* recorded_points)
{
	int min = 0, num = -1;
	for (int i = 0; i < count_vertex; i++)
		//минимальное ненулевое значение из записанной вершины в незаписанную
		if (((min == 0 && adjacency_matrix[string][i] != 0) || (adjacency_matrix[string][i] < min && adjacency_matrix[string][i] != 0)) && recorded_points[string] == 1 && recorded_points[i] == 0)
		{
			min = adjacency_matrix[string][i];
			num = i;
		}
	//возвращает номер в строке
	return num;
}

// запись подходящего ребра в новую матрицу смежности
int step(int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree)
{
	int  min = 0, min_from, min_to, num;
	for (int i = 0; i < count_vertex; i++)
		if (recorded_points[i] == 1)
		{
			//нахождение минимального незаписаннного ребра из каждой записанной вершины
			num = minimum(i, count_vertex, adjacency_matrix, recorded_points);
			// нахождение минимального незаписанного ребра среди всех записанных вершин графа
			if ((adjacency_matrix[i][num] < min && num != -1) || (min == 0 && num != -1))
			{
				min = adjacency_matrix[i][num];
				min_to = num;
				min_from = i;
			}
		}
	// если такое ребро есть
	if (min != 0)
	{
		// записать в новую матрицу смежности
		spanning_tree[min_to][min_from] = min;
		spanning_tree[min_from][min_to] = min;
		//записать в массив пройденных точек обе вершины
		recorded_points[min_to] = 1;
		recorded_points[min_from] = 1;
		return 1;
	}
	// если свободных ребер нет
	else return 0;
}

// алгоритм Прима для каждого компонента связности
int algorithm_from_point(int point, int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree)
{
	//записать в массив пройденных точек первую вершину
	recorded_points[point] = 1;
	//a - нашлось ли ребро минимальной длины, count - количество незаписанных точек 
	int a = 1, count = 0;
	// пока есть подходящие ребра
	while (a == 1)
		//найти его, записать в новую матрицу смежности
		a = step(count_vertex, recorded_points, adjacency_matrix, spanning_tree);

	//счет незаписанных точек
	for (int i = 0; i < count_vertex; i++)
		if (recorded_points[i] == 0)
			count++;
	return count;
}

int** algorithm_prim(int count_vertex, int** adjacency_matrix)
{
	// count - количество незаписанных вершин , point - точка с которой  начать алгоритм
	int* recorded_points, count = count_vertex, point = 0, ** spanning_tree;
	//создание мссива записанный вершин (сейчас нулевой т.к. ничего не записано)
	recorded_points = calloc(count_vertex, sizeof(int));
	//создание матрицы смежности для нового графа
	spanning_tree = calloc(count_vertex, sizeof(int*));
	for (int i = 0; i < count_vertex; i++)
		spanning_tree[i] = calloc(count_vertex, sizeof(int));
	//пока есть незаписанные точки
	while (count != 0)
	{
		// пройти алгоритм Прима для компонента связности
		count = algorithm_from_point(point, count_vertex, recorded_points, adjacency_matrix, spanning_tree);
		// выбор нового компонента связности (первая незаписанная вершина)
		for (point = 0; point < count_vertex; point++)
			if (recorded_points[point] == 0)
				break;
	}
	// удаление памяти для записанных точек
	free(recorded_points);
	//удаление старой матрицы
	for (int i = 0; i < count_vertex; i++)
		free(adjacency_matrix[i]);
	free(adjacency_matrix);
	return spanning_tree;
}
