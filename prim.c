#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "prim.h"

// ���� ������� ��������� ��� �����
int** input(int count_vertex, int** matrix)
{
	printf("���� ����� ��� ����� ����� 0\n������� ����� ����� ����� �������:\n");
	for (int i = 0; i < count_vertex; i++)
		for (int j = i; j < count_vertex; j++)
		{
			printf("%d � %d: ", i + 1, j + 1);
			scanf_s("%d", &matrix[i][j]);
			matrix[j][i] = matrix[i][j];
		}
	return matrix;
}
// ����� ������� ��������� ��� �����
void output(int count_vertex, int** matrix)
{
	printf("����� ������� ���������:\n");
	for (int i = 0; i < count_vertex; i++)
	{
		for (int j = 0; j < count_vertex; j++)
			printf("%4d", matrix[i][j]);
		printf("\n");
	}
}

//���������� ������������ �������������� ����� �� ������� (����������� ��������� �������� � ������)
int minimum(int string, int count_vertex, int** adjacency_matrix, int* recorded_points)
{
	int min = 0, num = -1;
	for (int i = 0; i < count_vertex; i++)
		//����������� ��������� �������� �� ���������� ������� � ������������
		if (((min == 0 && adjacency_matrix[string][i] != 0) || (adjacency_matrix[string][i] < min && adjacency_matrix[string][i] != 0)) && recorded_points[string] == 1 && recorded_points[i] == 0)
		{
			min = adjacency_matrix[string][i];
			num = i;
		}
	//���������� ����� � ������
	return num;
}

// ������ ����������� ����� � ����� ������� ���������
int step(int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree)
{
	int  min = 0, min_from, min_to, num;
	for (int i = 0; i < count_vertex; i++)
		if (recorded_points[i] == 1)
		{
			//���������� ������������ �������������� ����� �� ������ ���������� �������
			num = minimum(i, count_vertex, adjacency_matrix, recorded_points);
			// ���������� ������������ ������������� ����� ����� ���� ���������� ������ �����
			if ((adjacency_matrix[i][num] < min && num != -1) || (min == 0 && num != -1))
			{
				min = adjacency_matrix[i][num];
				min_to = num;
				min_from = i;
			}
		}
	// ���� ����� ����� ����
	if (min != 0)
	{
		// �������� � ����� ������� ���������
		spanning_tree[min_to][min_from] = min;
		spanning_tree[min_from][min_to] = min;
		//�������� � ������ ���������� ����� ��� �������
		recorded_points[min_to] = 1;
		recorded_points[min_from] = 1;
		return 1;
	}
	// ���� ��������� ����� ���
	else return 0;
}

// �������� ����� ��� ������� ���������� ���������
int algorithm_from_point(int point, int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree)
{
	//�������� � ������ ���������� ����� ������ �������
	recorded_points[point] = 1;
	//a - ������� �� ����� ����������� �����, count - ���������� ������������ ����� 
	int a = 1, count = 0;
	// ���� ���� ���������� �����
	while (a == 1)
		//����� ���, �������� � ����� ������� ���������
		a = step(count_vertex, recorded_points, adjacency_matrix, spanning_tree);

	//���� ������������ �����
	for (int i = 0; i < count_vertex; i++)
		if (recorded_points[i] == 0)
			count++;
	return count;
}

int** algorithm_prim(int count_vertex, int** adjacency_matrix)
{
	// count - ���������� ������������ ������ , point - ����� � �������  ������ ��������
	int* recorded_points, count = count_vertex, point = 0, ** spanning_tree;
	//�������� ������ ���������� ������ (������ ������� �.�. ������ �� ��������)
	recorded_points = calloc(count_vertex, sizeof(int));
	//�������� ������� ��������� ��� ������ �����
	spanning_tree = calloc(count_vertex, sizeof(int*));
	for (int i = 0; i < count_vertex; i++)
		spanning_tree[i] = calloc(count_vertex, sizeof(int));
	//���� ���� ������������ �����
	while (count != 0)
	{
		// ������ �������� ����� ��� ���������� ���������
		count = algorithm_from_point(point, count_vertex, recorded_points, adjacency_matrix, spanning_tree);
		// ����� ������ ���������� ��������� (������ ������������ �������)
		for (point = 0; point < count_vertex; point++)
			if (recorded_points[point] == 0)
				break;
	}
	// �������� ������ ��� ���������� �����
	free(recorded_points);
	//�������� ������ �������
	for (int i = 0; i < count_vertex; i++)
		free(adjacency_matrix[i]);
	free(adjacency_matrix);
	return spanning_tree;
}
