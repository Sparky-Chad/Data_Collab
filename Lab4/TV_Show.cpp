#pragma once
#include <iostream>
#include <string>
#include "Show.h"
#include "TV_Show.h"

void tvShow::play(){
	int season;
	int episode;

	cout << "Select Season(1)(2)(3):  ";
	cin >> season;
	getEpisodes(season-1);

	   	  
}



void tvShow::setEpisodes(string inSE[3][5]){

	for (int i =0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				SandE[i][j] = inSE[i][j];
			};
		};
}

void tvShow::getEpisodes(int season){
	
	for (int e =0; e < 5; e++){
		cout << "Season " << (season+1) << ", Episode " << (e+1) <<":  "<< SandE[season][e]<<endl;;
	}


}