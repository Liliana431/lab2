#ifndef prim
#define prim

//����
int** input(int count_vertex, int** matrix);

//����� 
void output(int count_vertex, int** matrix);

//���������� ������������ �������������� ����� �� ������� s
int minimum(int string, int count_vertex, int** adjacency_matrix, int* recorded_points);

// ���������� ������ ����� 
int step(int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree);

//�������� ����� ��� ������� ���������� ��������� 
// point - ����� � ������� ���������� �������� �����
int algorithm_from_point(int point, int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree);

//�������� ����� �� �������, ��������� �������� �����
int** algorithm_prim(int count_vertex, int** adjacency_matrix);

#endif
