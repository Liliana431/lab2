/*
удаление ребер графа, используя алгоритм Прима
Ганжа Лилиана
ИВТ-13БО
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "Prim.h"
void main()
{
	setlocale(LC_ALL, "RUS");
	int count_vertex, ** adjacency_matrix;
	printf("ведите число вершин: ");
	scanf_s("%d", &count_vertex);
	if (count_vertex < 1)
		return;
	// создание матрицы смежности для графа
	adjacency_matrix = malloc(count_vertex * sizeof(int*));
	for (int i = 0; i < count_vertex; i++)
		adjacency_matrix[i] = malloc(count_vertex * sizeof(int));
	//ввод матрицы смежности
	adjacency_matrix = input(count_vertex, adjacency_matrix);
	// удаление лишних ребер
	adjacency_matrix = algorithm_prim(count_vertex, adjacency_matrix);
	//вывод матрицы смежности
	output(count_vertex, adjacency_matrix);

	for (int i = 0; i < count_vertex; i++)
	{
		free(adjacency_matrix[i]);
	}
	free(adjacency_matrix);
}
// тесты
// 1) 4: 0 1 2 5 0 3 7 0 4 0 -> 1-2 1-3 3-4
// 2) 4: 0 1 2 4 0 3 7 0 5 0 -> 1-2 1-3 1-4
// 3) 6: 0 4 1 0 0 0 0 2 3 0 0 0 0 0 0 0 0 0 0 5 0 -> 1-3 2-3 2-4 5-6

