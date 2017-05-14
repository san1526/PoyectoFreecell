/*
 * GameSolver.cpp
 *
 *  Created on: 12 may. 2017
 *      Author: elver
 */

#include "GameSolver.h"
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

GameSolver::GameSolver() {
	// TODO Auto-generated constructor stub

}

GameSolver::~GameSolver() {
	// TODO Auto-generated destructor stub
}

void GameSolver::set_window(int in){
	window = in;
	return;
}

void GameSolver::mouse_move_and_click(int x, int y){

	string command = "xdotool mousemove --sync ";
	string click = "xdotool click 1";
	char buff[20] = {'\0'};
	sprintf(buff,"%d %d",x,y);
	command.append(buff);

	int pid = fork();
	if(pid == 0){
		execl("/bin/bash","sh","-c",command.c_str(),(char*)NULL);
	}
	waitpid(pid, NULL, 0);

	pid = fork();
	if(pid == 0){
		execl("/bin/bash", "sh", "-c", "xdotool search --name \"^Freecell$\" windowactivate --sync", (char*)NULL);
	}
	waitpid(pid , NULL, 0);
	usleep(1000);
	pid = fork();
	if(pid == 0){
		execl("/bin/bash", "sh", "-c", click.c_str(), (char*)NULL);
	}
	waitpid(pid , NULL, 0);
	usleep(1000);
	return;
}


void GameSolver::move_to_foundation(int card, char from){

	if (from == 'f') {
		for (int i = 0; i < 4; i++) {
			mouse_move_and_click(freecell[card].x , freecell[card].y);
			mouse_move_and_click(foundation[i].x, foundation[i].y);
		}
	}
	else if(from == 's'){
		for (int i = 0; i < 4; i++) {
			mouse_move_and_click(stacks[card].x , stacks[card].y + stacks_n[card] * 33);
			mouse_move_and_click(foundation[i].x, foundation[i].y);
		}
		stacks_n[card] =  stacks_n[card] -1;
	}

	return;
}

void GameSolver::move_to_freecell(int card, int frcl){

	mouse_move_and_click(stacks[card].x, stacks[card].y + stacks_n[card] * 33);
	mouse_move_and_click(freecell[frcl].x, freecell[frcl].y);
	stacks_n[card] = stacks_n[card] - 1;

	return;
}

void GameSolver::move_to_stack(int card, int to, int n){

	mouse_move_and_click(stacks[card].x, stacks[card].y + (stacks_n[card] - n) * 33);
	mouse_move_and_click(stacks[to].x, stacks[to].y);
	stacks_n[card] = stacks_n[card] - n;
	stacks_n[to] = stacks_n[to] + n;

	return;

}

void GameSolver::move_from_freecell(int n, int to){

	mouse_move_and_click(freecell[n].x, freecell[n].y);
	mouse_move_and_click(stacks[to].x, stacks[to].y + stacks_n[to] * 35);
	stacks_n[to] = stacks_n[to] + 1;

	return;

}

void GameSolver::make_solution(){

	string command = "fc-solve -m -o solution board";

	int pid = fork();
	if(pid == 0){
		execl("/bin/bash", "sh", "-c", command.c_str(), (char*)NULL);
	}
	waitpid(pid, NULL, 0);
	return;
}

void GameSolver::solution_parser(){

/*	  Move a card from stack 6 to the foundations
	  Move a card from stack 5 to freecell 1
	  Move a card from freecell 0 to stack 5
	  Move a card from stack 4 to freecell 2
	  Move a card from freecell 1 to stack 4	 */


	ifstream solution;
	solution.open("solution");

	string line;
	while(getline(solution,line)){

		istringstream iss(line);
		string result;

		if(getline(iss, result, '\n')){

			if(result.compare("-=-=-=-=-=-=-=-=-=-=-=-") && result.compare("====================")){

				char *pch = strtok ((char *)result.c_str()," ");
				while (pch != NULL)
				  {
				    steps.push_back(pch);
				    pch = strtok (NULL, " ");
				  }

			}

		}

	}

	return;
}

void GameSolver::try_solve(){

	int step_ctn = 0;
	int n = 0, from = 0, to_n = 0;
	char from_c = '\0', to_c = '\0';

	for(auto stp : steps){

		if(step_ctn == 9){
			n = 0, from = 0, to_n = 0;
			from_c = '\0', to_c = '\0';
			step_ctn = 0;
		}

		switch (step_ctn){

		case 1:
			if(!stp.compare("a"))
				n = 1;
			else
				n = atoi(stp.c_str());
			break;

		case 4:
			if(!stp.compare("stack"))
				from_c = 's';
			else if(!stp.compare("freecell"))
				from_c = 'f';
			break;

		case 5:
			from = atoi(stp.c_str());
			break;

		case 7:
			if(!stp.compare("the"))
				to_c = 'n';
			else if(!stp.compare("stack"))
				to_c = 's';
			else if(!stp.compare("freecell"))
				to_c = 'f';
			break;

		case 8:
			if(!stp.compare("foundations"))
				to_n = 0;
			else
				to_n = atoi(stp.c_str());
			break;

		}

		if(step_ctn == 8){
			cout << "move " << n << " => " << from_c << from << " to " << to_c << to_n <<endl;

			if(from_c == 's' && to_c == 's'){
				move_to_stack(from, to_n, n);
			}
			else if(from_c == 's' && to_c == 'f'){
				move_to_freecell(from, to_n);
			}
			else if(from_c == 'f' && to_c == 's'){
				move_from_freecell(from, to_n);
			}
			else if(from_c == 'f' && to_c == 'n'){
				move_to_foundation(from, 'f');
			}
			else if(from_c == 's' && to_c == 'n'){
				move_to_foundation(from, 's');
			}
		}
		step_ctn++;

	}

	return;
}
