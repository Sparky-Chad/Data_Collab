#pragma once
#include <iostream>
#include <string>
#include "Show.h"


class tvShow: public Show {

public:

	tvShow() : Show(){
		for (int i =0; i < 3; i++) {
			for (int j=0; j < 5; j++) {
				SandE[i][j] = "";
			};
		};
	};
	
	tvShow(string inSE[3][5] , string title, string desc ) : Show(title, desc) {

		for (int i=0; i < 3; i++) {
			for (int j=0; j < 5; j++) {
				SandE[i][j] = inSE[i][j];
			};
		};
		
	};

	void play();


	void setEpisodes(string inSE[3][5]);
	void getEpisodes(int);



	


private:
	//array of seasons and episodes seasons are rows episodes are col
	string SandE[3][5];
};
	   	  








