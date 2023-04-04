#include <string>
#include <map>
#include <dirent.h>
#include <iostream>
#include <vector>

#include "config.hpp"
#include "cvec.hpp"
#include "room_data.hpp"
#include "path_finder.hpp"

int main(){
	path_finder my_pf;
	
	my_pf.reset({3,3},0);
	my_pf.find_path(1,1);
	my_pf.print_walked();
	
	my_pf.reset({3,3},0);
	my_pf.find_path(6,6);
	my_pf.print_walked();
	
	my_pf.reset({3,3},0);
	my_pf.find_path(3,6);
	my_pf.print_walked();
	
	my_pf.reset({3,3},0);
	my_pf.find_path(6,3);
	my_pf.print_walked();
	return 1;
}

