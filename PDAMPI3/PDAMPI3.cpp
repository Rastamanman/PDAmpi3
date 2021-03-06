// PDAMPI3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "mpi.h"

using namespace std;

#define INF 999999
#define MASTER 0


int main(int argc, char *argv[])
{
	int rnk,tmp;
	int matrx[4][4] = { 
		{0, 4, 7, INF},
		{INF, 0, 4, INF},
		{12, 3, 0, 1},
		{1, INF, 0, 0}};

	MPI_Init(&argc, &argv);	MPI_Comm_rank(MPI_COMM_WORLD, &rnk);		for (int k = 0; k < 4; k++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrx[rnk][j] = min(matrx[rnk][k] + matrx[k][j], matrx[rnk][j]);
		}
		MPI_Allgather(matrx[rnk], 1, MPI_INT, matrx[rnk], 1, MPI_INT, MPI_COMM_WORLD);
	}

	if (rnk == MASTER)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (matrx[i][j] == INF)
					cout<<"INF";
				else
					cout<<matrx[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	MPI_Finalize();

	cin >> tmp;
	return 0;
}

