/*
 * GameSolver.h
 *
 *  Created on: 12 may. 2017
 *      Author: elver
 */

#ifndef GAMESOLVER_H_
#define GAMESOLVER_H_

#include <string>
#include <stack>
#include <vector>

using namespace std;

typedef struct coords{
	int x;
	int y;
}coords_t;

class GameSolver {
private:
	vector<coords_t> freecell {{53,157},{165,158},{273,159},{377,159}};
	vector<coords_t> foundation {{519,165},{629,159},{740,159},{845,161}};
	vector<coords_t> stacks {{56,306},{165,306},{288,306},{391,306},{508,306},{617,306},{727,306},{829,306}};
	vector<int> stacks_n {7,7,7,7,6,6,6,6};
	vector<string> steps;
	int window = 0;
public:

	GameSolver();
	virtual ~GameSolver();
	void set_window(int);
	void mouse_move_and_click(int ,int);
	void move_to_stack(int, int, int);
	void move_to_freecell(int, int);
	void move_from_freecell(int n, int to);
	void move_to_foundation(int, char);
	void make_solution();
	void solution_parser();
	void try_solve();
};

#endif /* GAMESOLVER_H_ */
