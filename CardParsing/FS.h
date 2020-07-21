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
	std::string base_file;//path to output
	std::string mask; //what files look
	std::vector<file> files;
	logg* main_log;
public:
	//build
	FS(std::string P_in, std::string B_out, std::string M) :path_in(P_in), base_file(B_out), mask(M), files(), main_log() {}
	void init(logg* L);
	void run();
	//server methods
	void delete_file();
	void collect_files();
	//server methods to separate file class elem in vector of file
	void set_state(int PTR, bool S);
	bool get_state(int PTR);
	std::string get_name(int PTR);
	bool find(file N);
	void add_to_base(file* N);
};