#include "FS.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <fstream>

namespace fs = std::filesystem;

void FS::set_state(int PTR, bool S) {
	this->files[PTR].set_state(S);
}
bool FS::get_state(int PTR) {
	return this->files[PTR].get_state();
}

std::string FS::get_name(int PTR) {
	return this->files[PTR].get_name();
}

void FS::delete_file() {
	std::vector<file>::iterator ptrIT;
	for (ptrIT = this->files.begin(); ptrIT != this->files.end();) {
		if (ptrIT->get_state() == 0) {
			for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
				fs::remove(ptrIT->get_name());
			}
			ptrIT = this->files.erase(ptrIT);
		}
		else {
			++ptrIT;
		}
	}
}

void FS::collect_files() {
	for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
		std::string tmpF = F.path().string();
		if (tmpF.find(this->mask) != std::string::npos) {
			file tmpFile(tmpF, 1);
			if (find(tmpFile)) {
				this->files.push_back(tmpFile);
			}
		}
	}
}

bool FS::find(file N) {
	for (auto ptrF : this->files) {
		if (ptrF.get_name() == N.get_name() && ptrF.get_state() == N.get_state()) {
			return false;
		}
	}
	return true;
}

void FS::init(logg* L) {
	this->main_log = L;
	this->main_log->add_log_string("INIT DONE");
	this->collect_files();
}

void FS::run() {
	this->main_log->add_log_string("SERVER START");
	this->main_log->write_to_file();
	for (auto ptr : this->files) {
		std::cout << ptr.get_name() << ":" << ptr.get_state() << std::endl;
	}
	add_to_base(&this->files[0]);
	
	
}

void FS::add_to_base(file* N) {
	this->main_log->add_log_string("ADDING START TO::" + N->get_name());
	std::cout << " **WORKING WITH ** " << N->get_name() << std::endl;
	std::ifstream docx(N->get_name(), std::ios::binary|std::ios::in);
	std::string tmp;

	while (getline(docx,tmp)) {
		std::cout << tmp << std::endl;
	}
	docx.close();
}



