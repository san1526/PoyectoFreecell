/*
 * Gameinstance.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#include "Gameinstance.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

Game_instance::Game_instance() {
	// TODO Auto-generated constructor stub
	window = 0;
}

Game_instance::~Game_instance() {
	// TODO Auto-generated destructor stub
}

void Game_instance::launch(){

	int pid = fork();
	if(pid == 0){
		execl("/usr/games/sol","-v","Freecell",(char*)NULL);
	}
	else if (pid == -1){
		cout << "Error creating a game instance" << '\n';
		exit(1);
	}

	int get_window_timeout = 0;

	while(window == 0 && get_window_timeout <= 1000){
		FILE *pipefp = popen("xdotool search --name ^Freecell$","r");
		fscanf(pipefp,"%d",&window);
		pclose(pipefp);
		get_window_timeout++;
	}
	if(window == 0 && get_window_timeout >= 1000){
		cout << "Error obtaining window ID" << '\n';
		exit(1);
	}
	return;
}

void Game_instance::window_move(){

	char command[100] = "xdotool windowmove ",
			comand_f[] = " 0 0",
			buff[20] = {'\0'};

	sprintf(buff,"%d",window);
	strcat(command,buff);
	strcat(command,comand_f);

	int pid = fork();
	if(pid == 0){
		execl("/bin/bash","sh","-c",command,(char*)NULL);
	}
	else  if (pid == -1){
		cout << "Error triying to move window" << '\n';
		exit(1);
	}
}

int Game_instance::get_window(){
	return window;
}

void Game_instance::window_resize(int x, int y){

	char command[100] = "xdotool windowsize ",
		 window_s[20] = {'\0'},
		 x_s[5] = {'\0'},
		 y_s[5] = {'\0'};

	sprintf(window_s,"%d ",window);
	sprintf(x_s,"%d ",x);
	sprintf(y_s,"%d",y);

	strcat(command, window_s);
	strcat(command, x_s);
	strcat(command, y_s);

	int pid = fork();
	if(pid == 0){
		execl("/bin/bash","sh","-c",command,(char*)NULL);
	}
	else  if (pid == -1){
		cout << "Error triying to resize window" << '\n';
		exit(1);
	}

	return;
}

