#ifndef TASKSOLVER_H
#define TASKSOLVER_H

#include <algorithm>
#include <vector>

/*#include "spgraph.h"
#include "spgraphiterator.h"*/
#include "circuitelemdata.h"
#include "spgraphlib.h"
using namespace std;
using namespace spg;

class TaskSolver
{
	vector<vector<unsigned int>> paths;
	vector<vector<unsigned int>> back_paths;
	vector<vector<double>> res_matrix;
	vector<VertexBondType> vertex_types;
	int n;

	double det(vector<vector<double>> matrix);
	void systemSolution(SPGraph<CircuitElemData> &graph);
	void first_law_voltage(SPGraph<CircuitElemData> &graph, int &currentLine);
	void law_voltage(SPGraph<CircuitElemData> &graph, int &currentLine);
	void law_current(int &currentLine);
public:
	TaskSolver() {};
	void solve(SPGraph<CircuitElemData> &graph);
};
/*

double TaskSolver::det(vector<vector<double>> matrix)
{
	int N = matrix.size();
	int iStart = 0;
	int jStart = 0;
	int iFinish = N - 1;
	int jFinish = N - 1;
	vector<vector<double>> cur_matrix;
	cur_matrix.resize(N - 1);
	if (N == 1)
	{
		return matrix[iStart][jStart];
	}
	else if (N == 2)
	{
		return matrix[iStart][jStart] * matrix[iFinish][jFinish] - matrix[iStart][jFinish] * matrix[iFinish][jStart];
	}
	else
	{
		double ans = 0;
		for (int k = jStart; k <= jFinish; k++)
		{
			for (int i = iStart; i < iFinish; i++)
			{
				cur_matrix[i].clear();
			}
			for (int i = iStart + 1; i <= iFinish; i++)
			{
				for (int j = jStart; j <= jFinish; j++)
				{
					if (j != k)
					{
						cur_matrix[i - 1].push_back(matrix[i][j]);
					}
				}
			}
			int sign = 1;
			if (k % 2 == 1) sign = -1;
			ans += sign*matrix[iStart][k] * det(cur_matrix);
		}
		return ans;
	}
}

void TaskSolver::systemSolution(SPGraph<CircuitElemData> &graph)
{
	vector<vector<double>> resMatrix(res_matrix);
	double D = det(resMatrix);
	for (int j = 0; j < n - 1; j++)
	{
		if (j != 0)
		{
			for (int i = 0; i < n - 1; i++)
			{
				resMatrix[i][j - 1] = res_matrix[i][j - 1];
			}
		}
		resMatrix[0][j] = graph.at(0)->getData().getU();
		for (int i = 1; i < n - 1; i++)
		{
			resMatrix[i][j] = 0;
		}
		double amperance = det(resMatrix) / D;
		if (j == 0)
		{
			CircuitElemData newData(graph.at(j)->getData().getR(), graph.at(j)->getData().getU(), amperance);
			graph.at(j)->setData(newData);
		}
		else
		{
			CircuitElemData newData(graph.at(j)->getData().getR(), amperance*graph.at(j)->getData().getR(), amperance);
			graph.at(j)->setData(newData);
		}
	}
	graph.at(n-1)->setData(graph.at(0)->getData());
}

void TaskSolver::first_law_voltage(SPGraph<CircuitElemData> &graph, int &currentLine)
{
	int num = 0;
	while (num != n - 1)
	{
		res_matrix[currentLine][num] = graph.at(num)->getData().getR();
		num = *paths[num].begin();
	}
	currentLine++;
}

void TaskSolver::law_voltage(SPGraph<CircuitElemData> &graph, int &currentLine)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (vertex_types[i] == VertexStartFull || vertex_types[i] == VertexMidFull || vertex_types[i] == VertexMidRight)
		{
			for (vector<unsigned int>::iterator j = paths[i].begin(); j != paths[i].end() - 1; ++j)
			{
				int num = *j;
				int old_num = 0;
				while ((vertex_types[num] != VertexEndFull && vertex_types[num] != VertexMidFull && vertex_types[num] != VertexMidLeft) || *(back_paths[num].end() - 1) == old_num)
				{
					old_num = num;
					res_matrix[currentLine][num] = graph.at(num)->getData().getR();
					num = *(paths[num].end() - 1);
				}
				int num_end = num;
				num = *(j + 1);
				while (num != num_end)
				{
					res_matrix[currentLine][num] = -graph.at(num)->getData().getR();
					num = *paths[num].begin();
				}
				currentLine++;
			}

		}
	}
}

void TaskSolver::law_current(int &currentLine)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (vertex_types[i] == VertexStartSingle || vertex_types[i] == VertexMidSingle)
		{
			if (vertex_types[paths[i][0]] == VertexMidSingle || vertex_types[paths[i][0]] == VertexMidRight)
			{
				res_matrix[currentLine][i] = 1;
				res_matrix[currentLine][paths[i][0]] = -1;
				currentLine++;
			}
		}
		else if (vertex_types[i] == VertexMidRight || vertex_types[i] == VertexStartFull)
		{
			res_matrix[currentLine][i] = 1;
			for (vector<unsigned int>::iterator j = paths[i].begin(); j != paths[i].end(); ++j)
			{
				res_matrix[currentLine][*j] = -1;
			}
			currentLine++;
		}
		else if (vertex_types[i] == VertexMidLeft)
		{
			res_matrix[currentLine][i] = -1;
			for (vector<unsigned int>::iterator j = back_paths[i].begin(); j != back_paths[i].end(); ++j)
			{
				res_matrix[currentLine][*j] = 1;
			}
			currentLine++;
		}
		else if (vertex_types[i] == VertexMidFull)
		{
			res_matrix[currentLine][i] = -1;
			for (vector<unsigned int>::iterator j = back_paths[i].begin(); j != back_paths[i].end(); ++j)
			{
				res_matrix[currentLine][*j] = 1;
			}
			currentLine++;
			res_matrix[currentLine][i] = 1;
			for (vector<unsigned int>::iterator j = paths[i].begin(); j != paths[i].end(); ++j)
			{
				res_matrix[currentLine][*j] = -1;
			}
			currentLine++;
		}
	}
}

void TaskSolver::solve(SPGraph<CircuitElemData> &graph)
{
	n = graph.size();
	paths.resize(n);
	back_paths.resize(n);
	vertex_types.resize(n);
	res_matrix.resize(n - 1);
	for (int i = 0; i < n - 1; i++)
	{
		res_matrix[i].resize(n - 1);
	}
	for (int i = 0; i < n; i++)
	{
		paths[i] = graph.getVertexDestination(graph.at(i), true);
		back_paths[i] = graph.getVertexDestination(graph.at(i), false);
		vertex_types[i] = graph.at(i)->BondType();
	}
	int currentLine = 0;
	first_law_voltage(graph, currentLine);
	law_current(currentLine);
	law_voltage(graph, currentLine);
	systemSolution(graph);
}
*/
#endif //TASKSOLVER_H
