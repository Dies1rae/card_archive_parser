#pragma once
#include "file.h"
#include "logg.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>


namespace fs = std::filesystem;

class FS {
private:
	std::string path_in; //path to look for
	std::string path_out; // path to output 
	std::string base_file;//path to DB
	std::string mask; //what files look
	std::string mask_img; //mask for second file type-img
	std::vector<file> files_img; //img files
	std::vector<file> files; //text files
	logg* main_log;
public:
	//build
	FS(std::string P_in,std::string P_out, std::string B_out, std::string M, std::string MI) :path_in(P_in), path_out(P_out), base_file(B_out), mask(M), mask_img(MI), files_img(), files(), main_log() {}
	void init(logg* L);  //all inits log and first file collect
	void run(); //main loop - get files, parse it, wait.
	//server methods
	void delete_file(); // when all parse and copy, kill orig
	void collect_files(); // main collector - get in dir and watch in for mask1 and mask2 with same names 
	//server methods to separate file class elem in vector of file
	int chk_equiv_file(file* F); // this is check file mask1 always need a file mask2
	std::string get_name_img(int PTR); //get filename mask2
	void set_state(int PTR, bool S);//state of files
	bool get_state(int PTR); //state of files
	std::string get_name(int PTR);//get filename mask1
	bool find_txt(file N); //find
	bool find_img(file N);//find
	void main_parser(file* N); //main parser...magic is here
};
