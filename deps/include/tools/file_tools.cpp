#include "file_tools.h"
#include <iostream>
#include <fstream>

#include <filesystem>
#include "platform_folders.h"

using namespace std;

LAPI void file_tools::create_file(const std::string& path)
{
	if (!exist(path))
	{
		std::ofstream outfile(path);
		outfile.close();
	}
}

bool file_tools::exist(const std::string& path)
{
	return filesystem::exists(path);
}

void file_tools::create_directory(const std::string& path)
{
	if (!exist(path))
	{
		filesystem::create_directories(path);
	}
}

//std::string& file_tools::read_file(const std::string& path)
//{
//	return ;
//}
void file_tools::read_file(std::string& out, const std::string& path)
{
}

std::string file_tools::get_hack_directory()
{
	auto documents = sago::getDocumentsFolder();
	filesystem::path path(documents);
	path.append("LemiCSGO");

	if (!exist(path.generic_string()))
		create_directory(path);

	auto data_path = path;
	data_path.append("data");
	
	if (!exist(data_path.generic_string()))
		create_directory(data_path);
	
	return path.generic_string();
}

std::filesystem::path file_tools::get_hack_directory_path()
{
	auto documents = sago::getDocumentsFolder();
	filesystem::path path(documents);
	path.append("LemiCSGO");

	if (!exist(path.generic_string()))
		create_directory(path);

	auto data_path = path;
	data_path.append("data");

	if (!exist(data_path.generic_string()))
		create_directory(data_path);
	
	return path;
}
