#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "facilities.h"

string m_dir = "bin/maps/";

void load_maps()
{
	for (int i = 0; i < map_height; ++i)
	{
		map load_map;
		ifstream map_file = ifstream(m_dir + to_string(i));
		string curr_line;
		int line_counter = 0;
		while (getline(map_file, curr_line))
		{
			if (line_counter < map_dim)
			{
				for (int j = 0; j < map_dim; ++j)
					load_map.paths[j][line_counter] = stoi(curr_line.substr(j * 2, 2), 0, 16);
				line_counter++;
			}
			else
				load_map.items.push_back(tuple<item, int, int>(items_lib[stoi(curr_line.substr(2, 1), 0, 16)].instantiate(), curr_line.at(0) - '0', curr_line.at(1) - '0'));
		}
		maps.push_back(load_map);
	}
}