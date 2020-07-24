#include <iostream>
#include "FS.h"
#include "file.h"
#include<stdio.h>
#include<windows.h>

int main(int argc, char* argv[]) {
	
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	if (argc == 1) {
		std::cout << "Starting" << std::endl;
		std::cout << "**default folder and filetypes**" << std::endl;
		std::string dir_in = ".\\in";
		std::string dir_out = ".\\out";
		std::string base_file_out = ".\\out\\out.csv";
		std::string mask = "txt";
		std::string maskIM = "jpg";
		logg* Nlog = new logg("Begin");
		FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
		main_serv.init(Nlog);
		
		main_serv.run();
	}
	if (argc == 2 && (argv[1][0] == '/' && argv[1][1] == 'm')) {
		
	}
	if (argc == 2 && (argv[1][0] == '/' && argv[1][1] == '?')) {
		
	}
	if (argc == 2 && (argv[1][0] == '/' && argv[1][1] == 's')) {
		std::cout << "Starting" << std::endl;
		std::cout << "**default folder and filetypes**" << std::endl;
		std::string dir_in = ".\\in";
		std::string dir_out = ".\\out";
		std::string base_file_out = ".\\out\\out.csv";
		std::string mask = "txt";
		std::string maskIM = "jpg";
		logg* Nlog = new logg("Begin");
		FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
		main_serv.init(Nlog);
		main_serv.run();
	}
	if ((argc > 2 && argc < 6) && (argv[1][0] == '/' && argv[1][1] == 's')) {
		if (argc == 3) {
			std::string dir_in = argv[2];
			std::string dir_out = ".\\out";
			std::string base_file_out = ".\\out\\out.csv";
			std::string mask = "txt";
			std::string maskIM = "jpg";
			logg* Nlog = new logg("Begin");
			FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
			main_serv.init(Nlog);
			main_serv.run();
		}
		if (argc == 4) {
			std::string dir_in = argv[2];
			std::string dir_out = argv[3];
			std::string base_file_out = ".\\out\\out.csv";
			std::string mask = "txt";
			std::string maskIM = "jpg";
			logg* Nlog = new logg("Begin");
			FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
			main_serv.init(Nlog);
			main_serv.run();
		}
		if (argc == 5) {
			std::string dir_in = argv[2];
			std::string dir_out = argv[3];
			std::string base_file_out = argv[4];
			std::string mask = "txt";
			std::string maskIM = "jpg";
			logg* Nlog = new logg("Begin");
			FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
			main_serv.init(Nlog);
			main_serv.run();
		}
		if (argc == 5) {
			std::string dir_in = argv[2];
			std::string dir_out = argv[3];
			std::string base_file_out = argv[4];
			std::string mask = argv[5];
			std::string maskIM = "jpg";
			logg* Nlog = new logg("Begin");
			FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
			main_serv.init(Nlog);
			main_serv.run();
		}
		if (argc == 6) {
			std::string dir_in = argv[2];
			std::string dir_out = argv[3];
			std::string base_file_out = argv[4];
			std::string mask = argv[5];
			std::string maskIM = argv[6];
			logg* Nlog = new logg("Begin");
			FS main_serv(dir_in, dir_out, base_file_out, mask, maskIM);
			main_serv.init(Nlog);
			main_serv.run();
		}
	}

	return 0;
}