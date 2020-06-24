#include <iostream>
#include <vector>


/**
* Solves Eight Queens Puzzle. The problem is about placing n non-attacking
* queens on an n×n matrix, for which solutions exist for all natural
* numbers n with the exception of n = 2 and n = 3. A queen attacks another if:
* <ul>
*	<li>They are in the same row</li>
*	<li>They are in the same column</li>
*	<li>They are in the same diagonal</li>
* </ul>
*
* You can see more here: {@link https://www.geeksforgeeks.org/8-queen-problem/}
*
* @apiNote		The soluction uses {@link https://en.wikipedia.org/wiki/Backtracking backtracking}
*/
class EightQueensPuzzle
{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	/**
	* Stores total soluctions found.
	*/
	int soluctions;


public:
	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	/**
	* Solves Eight Queens Puzzle.
	*/
	EightQueensPuzzle()
	{
		soluctions = 0;
	}


	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	/**
	* Solves Eight Queen Puzzle, displaying at the end the nxn matrix with the
	* positions of the queen (represented by 'Q').
	*
	* @param		N Matrix dimension
	*/
	void run(int N)
	{
		std::vector<std::vector<int>> tab(N);


		// Initializes matrix NxN with zeros
		for (int i = 0; i < N; i++) {
			tab[i].resize(N);

			for (int j = 0; j < N; j++) {
				tab[i][j] = 0;
			}
		}

		run(tab, N, 0);
	}

	/**
	* Gets total soluctions found.
	*
	* @return		Total soluctions found
	*/
	int getTotalSoluctions()
	{
		return soluctions;
	}
private:
	/**
	* Checks if it is safe to place a queen in a table position. It is safe if:
	* <ul>
	*	<li>There is no other queen on the same row</li>
	*	<li>There is no other queen on the same column</li>
	*	<li>There is no other queen on the same diagonal</li>
	* </ul>
	*
	* @return		If it is safe to place a queen in a table position
	*/
	bool isSafe(std::vector<std::vector<int>>& tab, int N, int line, int col)
	{
		// Checks whether it is safe horizontally
		for (int i = 0; i < N; i++)
			if (tab[line][i] == 1) return false;

		// Checks whether it is safe vertically
		for (int i = 0; i < N; i++)
			if (tab[i][col] == 1) return false;

		// Checks if it is safe on bottom right diagonal
		for (int i = 0; line + i < N && col + i < N; i++)
			if (tab[line + i][col + i] == 1) return false;
		// Checks if it is safe on bottom left diagonal
		for (int i = 0; line + i < N && col - i >= 0; i++)
			if (tab[line + i][col - i] == 1) return false;
		// Checks if it is safe on top right diagonal
		for (int i = 0; line - i >= 0 && col + i < N; i++)
			if (tab[line - i][col + i] == 1) return false;
		// Checks if it is safe on top left diagonal
		for (int i = 0; line - i >= 0 && col - i >= 0; i++)
			if (tab[line - i][col - i] == 1) return false;

		return true;
	}

	/**
	* Tries to put a queen in a table column.
	*
	* @param		tab Table that this queen will be placed
	* @param		N Table dimension
	* @param		col Column that will be placed the queen
	*/
	void run(std::vector<std::vector<int>>& tab, int N, int col)
	{
		// If all columns have at least one queen, found a soluction
		if (col == N) {
			showTable(tab, N);
			soluctions++;
		} else {
			// Tries to put the queen in a row in this column
			for (int i = 0; i < N; i++) {
				if (isSafe(tab, N, i, col)) {
					tab[i][col] = 1;			// Puts the queen in the safe position
					run(tab, N, col + 1);		// Calls recursion to put the next queen in the next column
					tab[i][col] = 0;			// Backtracking to find other soluctions
				}
			}
		}
	}

	/**
	* Displays a matrix on console.
	*
	* @param		matrix Matrix to be displayed
	* @param		N Matrix dimension
	*/
	void showTable(std::vector<std::vector<int>>& matrix, int N)
	{
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				std::cout << matrix[i][j] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};


//--------------------------------------------------------------------------
//		Main
//--------------------------------------------------------------------------
int main()
{
	EightQueensPuzzle eqp;


	eqp.run(4);
	std::cout << "Valid soluctions: " << eqp.getTotalSoluctions() << std::endl;

	system("pause");

	return 0;
}