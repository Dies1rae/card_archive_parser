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

std::string FS::get_name_img(int PTR) {
	return this->files_img[PTR].get_name();
}

int FS::chk_equiv_file(file* f) {
	for (auto ptr : this->files) {
		if (f->get_name() == ptr.get_name()) {
			std::string tmpNAME = f->get_name().substr(0, f->get_name().size() - 4);
			tmpNAME += ".jpg";
			for (int ptr_jpg = 0; ptr_jpg < this->files_img.size(); ptr_jpg++) {
				if (this->files_img[ptr_jpg].get_name() == tmpNAME) {
					return ptr_jpg;
				}
			}
		}
	}
	return 9999999;
}

void FS::delete_file() {
	//txt
	this->main_log->add_log_string("::CLEAN START::");
	std::vector<file>::iterator ptrIT;
	for (ptrIT = this->files.begin(); ptrIT != this->files.end();) {
		if (ptrIT->get_state() == 0) {
			for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
				fs::remove(ptrIT->get_name());
			}
			ptrIT = this->files.erase(ptrIT);
		} else {
			++ptrIT;
		}
	}
	//jpg
	for (ptrIT = this->files_img.begin(); ptrIT != this->files_img.end();) {
		if (ptrIT->get_state() == 0) {
			for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
				fs::remove(ptrIT->get_name());
			}
			ptrIT = this->files_img.erase(ptrIT);
		} else {
			++ptrIT;
		}
	}
	this->main_log->add_log_string("::CLEAN DONE::");
	this->main_log->write_to_file();
}

void FS::collect_files() {
	//txt
	for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
		std::string tmpF = F.path().string();
		if (tmpF.find(this->mask) != std::string::npos && F.file_size() > 0) {
			file tmpFile(tmpF, 1);
			if (find_txt(tmpFile)) {
				this->files.push_back(tmpFile);
				this->main_log->add_log_string("COLLECT FILE::" + tmpFile.get_name());
				this->main_log->write_to_file();
			}
		}
	}
	//jpg
	for (auto& F : fs::recursive_directory_iterator(this->path_in)) {
		std::string tmpF = F.path().string();
		if (tmpF.find(this->mask_img) != std::string::npos && F.file_size() > 0) {
			file tmpFile(tmpF, 1);
			if (find_img(tmpFile)) {
				this->files_img.push_back(tmpFile);
			}
		}
	}
}

bool FS::find_txt(file N) {
	//txt
	for (auto ptrF : this->files) {
		if (ptrF.get_name() == N.get_name() && ptrF.get_state() == N.get_state()) {
			return false;
		}
	}
	return true;
}
bool FS::find_img(file N) {
	//txt
	for (auto ptrF : this->files_img) {
		if (ptrF.get_name() == N.get_name() && ptrF.get_state() == N.get_state()) {
			return false;
		}
	}
	return true;
}

void FS::init(logg* L) {
	this->main_log = L;
	this->main_log->add_log_string("::INIT DONE::");
	this->main_log->write_to_file();
	this->collect_files();
}

void FS::run() {
	this->main_log->add_log_string("::SERVER START::");
	this->main_log->write_to_file();
	for (auto ptr : this->files) {
		std::cout << ptr.get_name() << ":" << ptr.get_state() << std::endl;
	}
	while (1) {
		collect_files();
		if (this->files.size() > 0) {
			this->main_log->add_log_string("::WORKING::");
			this->main_log->write_to_file();
			std::cout << "Collected from *in*: " << std::endl;
			for (auto ptr : this->files) { std::cout << ptr.get_name() << ':' << ptr.get_state() << std::endl; }
			main_parser(&this->files[0]);
		} else {
			Sleep(3000);
			std::cout << "**ALL DONE**" << std::endl;
			std::cout << "**WAITING**" << std::endl;
			Sleep(2000);
		}
		system("CLS");
	}
}

void FS::main_parser(file* N) {
	//init
	//check img in files_img
	if (chk_equiv_file(N) != 9999999 && chk_equiv_file(N) > -1) {
		int img_pos = chk_equiv_file(N);
		this->main_log->add_log_string("::ADDING FILES TO BASE LIST::" + N->get_name());
		std::cout << "::WORKING WITH::" << N->get_name() << std::endl;

		int lines_in_file_ptr = 0;

		std::string tmpbuf;
		std::string headbuf;
		std::vector<std::string> head;
		std::string bodybuf;
		std::vector<std::string> body;
		std::string filenameout = this->path_out + '\\';
		std::string filenameout_img = this->path_out + '\\';
		//check number of lines in file
		std::ifstream textin;
		textin.open(N->get_name());
		while (std::getline(textin, tmpbuf)) {
			if(lines_in_file_ptr < 2){
				head.push_back(tmpbuf);
			} else {
				body.push_back(tmpbuf);
			}
			lines_in_file_ptr++;
		}
		textin.close();
		for (auto& ptr : head) {
			headbuf += ptr;
			headbuf += '_';
		}
		
		for (auto& ptr : body) {
			bodybuf += ptr;
			bodybuf += ':';
		}
		replace(headbuf.begin(), headbuf.end(), '\n', '_');
		replace(headbuf.begin(), headbuf.end(), '^', '_');
		replace(headbuf.begin(), headbuf.end(), ',', '_');
		replace(headbuf.begin(), headbuf.end(), '.', '_');
		replace(bodybuf.begin(), bodybuf.end(), '\n', ':');
		replace(bodybuf.begin(), bodybuf.end(), '^', ':');
		replace(bodybuf.begin(), bodybuf.end(), ',', ':');

		//add head,body to csv
		std::ofstream csvbase(this->base_file, std::ios_base::app | std::ios_base::out);
		csvbase << headbuf + ';' + bodybuf + '\n';
		csvbase.close();
		//copy
		filenameout += headbuf;
		filenameout += ".txt";
		filenameout_img += headbuf;
		filenameout_img += ".jpg";
		std::ifstream src_txt(N->get_name(), std::ios::binary);
		std::ofstream dest_txt(filenameout, std::ios::binary);
		dest_txt << src_txt.rdbuf();
		src_txt.close();
		dest_txt.close();
		std::ifstream src_img(this->files_img[img_pos].get_name(), std::ios::binary);
		std::ofstream dest_img(filenameout_img, std::ios::binary);
		dest_img << src_img.rdbuf();
		src_img.close();
		dest_img.close();


		//delet and clean
		headbuf.clear();
		bodybuf.clear();
		head.clear();
		body.clear();
		this->files_img[img_pos].set_state(false);
		N->set_state(false);
		delete_file();
		this->main_log->add_log_string("::RECOGNIZING AND ADDING DONE::" + N->get_name());
		std::cout << "**write logs**" << std::endl;
		this->main_log->write_to_file();
	} else {
		N->set_state(false);
		delete_file();
		std::cout << "**write logs**" << std::endl;
		this->main_log->write_to_file();
	}
}
