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
	while (1) {
		collect_files();
		if (this->files.size() > 0) {
			std::cout << "Collected from *in*: " << std::endl;
			for (auto ptr : this->files) { std::cout << ptr.get_name() << ':' << ptr.get_state() << std::endl; }

			add_to_base(&this->files[0]);
		}
		else {
			Sleep(3000);
			std::cout << "**ALL DONE**" << std::endl;
			std::cout << "**WAITING**" << std::endl;
			Sleep(2000);
		}
		system("CLS");
	}
	
	
	
}

void FS::add_to_base(file* N) {
	//init
	this->main_log->add_log_string("ADDING START TO::" + N->get_name());
	std::cout << " **WORKING WITH ** " << N->get_name() << std::endl;
	std::ifstream textin(N->get_name(), std::ios::binary|std::ios::in);
	std::string head;
	std::string bodybuf;
	std::vector<std::string> body;
	std::string filenameout = this->path_out + '\\';
	//parsing
	//gethead
	std::getline(textin, head);
	textin.close();
	//getbody
	textin.open(N->get_name());
	std::string tmpbuf;
	while (std::getline(textin, tmpbuf)) {
		body.push_back(tmpbuf);
	}
	textin.close();
	for (int ptr = 1; ptr < body.size(); ptr++) {
		bodybuf += body[ptr] + ':';
	}
	//clean body
	replace(bodybuf.begin(), bodybuf.end(), ',', '.');
	replace(bodybuf.begin(), bodybuf.end(), '\n', ':');
	//parse number from head
	if (head.size() > 20) { //if head < 6 symbols that already a number
		for (int ptr = 0; ptr < head.size();ptr++) {
			//its clean head from restricted
			if (head[ptr] == '\\' || head[ptr] == '/' || head[ptr] == '*' || head[ptr] == ':' || head[ptr] == '?' || head[ptr] == '"' || head[ptr] == '<' || head[ptr] == '>' || head[ptr] == '|' || head[ptr] == '+') {
				head[ptr] = '_';
			}
			if ((head[ptr - 1] == '.' || head[ptr - 1] == '_') && head[ptr] == 32 && head[ptr + 1] == 32 && ptr + 1 != head.size()) {
				head = head.substr(0, ptr);
			}
		}
	}
	else {
		head.pop_back();
	}
	//add head,body to csv
	std::ofstream csvbase(this->base_file, std::ios_base::app | std::ios_base::out);
	csvbase << head + ','+ bodybuf + '\n';
	csvbase.close();
	//copy
	filenameout += head;
	filenameout += ".txt";
	std::ifstream src(N->get_name(), std::ios::binary);
	std::ofstream dest(filenameout, std::ios::binary);
	dest << src.rdbuf();
	src.close();
	dest.close();
	//delet and clean
	head.clear();
	bodybuf.clear();
	body.clear();
	N->set_state(false);
	delete_file();
	this->main_log->add_log_string("RECOGNIZING AND ADDING DONE::" + N->get_name());
	std::cout << "**write logs**" << std::endl;
	this->main_log->write_to_file();
}



