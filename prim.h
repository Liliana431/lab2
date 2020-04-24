#ifndef prim
#define prim

//ввод
int** input(int count_vertex, int** matrix);

//вывод 
void output(int count_vertex, int** matrix);

//нахождение минимального незаписаннного ребра из вершины s
int minimum(int string, int count_vertex, int** adjacency_matrix, int* recorded_points);

// добавление одного ребра 
int step(int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree);

//алгоритм Прима для каждого компонента связности 
// point - точка с которой начинается алгоритм Прима
int algorithm_from_point(int point, int count_vertex, int* recorded_points, int** adjacency_matrix, int** spanning_tree);

//удаление ребер из матрицы, используя алгоритм Прима
int** algorithm_prim(int count_vertex, int** adjacency_matrix);

#endif
