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
	std::string mask_img;
	std::vector<file> files_img;
	std::vector<file> files; //text files
	logg* main_log;
public:
	//build
	FS(std::string P_in,std::string P_out, std::string B_out, std::string M, std::string MI) :path_in(P_in), path_out(P_out), base_file(B_out), mask(M), mask_img(MI), files_img(), files(), main_log() {}
	void init(logg* L);
	void run();
	//server methods
	void delete_file();
	void collect_files();
	//server methods to separate file class elem in vector of file
	int get_queals_jpg_txt(file* F);
	std::string get_name_img(int PTR);
	void set_state(int PTR, bool S);
	bool get_state(int PTR);
	std::string get_name(int PTR);
	bool find_txt(file N);
	bool find_img(file N);
	void add_to_base(file* N);
};
