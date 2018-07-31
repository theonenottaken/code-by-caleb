#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "definitions.h"
#include "Point.h"
#include "Data.h"
#include "ClusterMaker.h"


int main() {

	std::ifstream ifile("input.txt", std::ios::in);
	if (!ifile.is_open()) {
		std::cout << "ERROR: could not open input file" << std::endl;
	} else {
		std::string str;
		ifile >> str;

		int t;
		int num;
		if (str == "single")
			t = SINGLE;
		else
			t = AVERAGE;

		getline(ifile, str); // skip to next line
		ifile >> num;

		std::vector<Point> pts;
		while (!ifile.eof()) {

			getline(ifile, str, ',');
			int x = atoi(str.c_str());
			getline(ifile, str);
			int y = atoi(str.c_str());
			pts.push_back(Point(x, y));
		}

		Data data(t, num, pts);
		ClusterMaker cm(data);
		std::vector<int> nums = cm.makeClusters();
		std::ofstream ofile("output.txt", std::ios::out);
		if (!ofile.is_open()) {
			std::cout << "ERROR: could not open output file" << std::endl;
		} else {

			for (unsigned int i = 0; i < nums.size(); i++) {
				ofile << nums[i];
				if (i != nums.size() - 1)
					ofile << std::endl;
			}
			ifile.close();
		}
	}
}
