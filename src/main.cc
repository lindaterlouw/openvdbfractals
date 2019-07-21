//#include "pch.h"

#include <stdio.h>

#include <iostream>

#include <vector>

#include "openvdb/openvdb.h"

#include <fstream>

#include <gflags/gflags.h>

#include <boost/algorithm/string.hpp>

#include <exception>



DEFINE_string(filename, "", "The name of the ply file");

DEFINE_int32(skip, 11, "The number of lines to skip (default 11)");

DEFINE_bool(rgb, true, "Use rgb channels");

DEFINE_int32(magnification, 10000, "The factor for magnification");



using namespace openvdb;



void readPly() {

	try {

		std::cout << "Starting ply to openvdb converter. Command line options:" << std::endl;

		std::cout << "-filename" << std::endl;

		std::cout << "-skip" << std::endl;

		std::cout << "-rgb" << std::endl;

		std::cout << "-magnification" << std::endl;



		if (FLAGS_filename.empty()) {

			std::cout << "Please specify a filename in ply format (-filename)" << std::endl;

			return;

		}

		else {

			std::cout << "Reading file " << FLAGS_filename << "..." << std::endl;

		}

		openvdb::initialize();

		openvdb::GridPtrVec grids;



		openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(0.0);

		typename FloatGrid::Accessor accessor = grid->getAccessor();



		openvdb::FloatGrid::Ptr gridr = openvdb::FloatGrid::create(0.0);

		typename FloatGrid::Accessor accessorr = gridr->getAccessor();



		openvdb::FloatGrid::Ptr gridg = openvdb::FloatGrid::create(0.0);

		typename FloatGrid::Accessor accessorg = gridg->getAccessor();



		openvdb::FloatGrid::Ptr gridb = openvdb::FloatGrid::create(0.0);

		typename FloatGrid::Accessor accessorb = gridb->getAccessor();



		std::ifstream infile(FLAGS_filename);



		float x, y, z, r, g, b, a;

		int i = 0;



		for (i = 0; i <= FLAGS_skip - 1; i++) {

			std::string dummyLine;

			std::getline(infile, dummyLine);

		}



		while (infile >> x >> y >> z >> r >> g >> b >> a) {

			accessor.setValue(Coord(x * FLAGS_magnification, y * FLAGS_magnification, z * FLAGS_magnification), 1);



			if (FLAGS_rgb) {

				accessorr.setValue(Coord(x * FLAGS_magnification, y * FLAGS_magnification, z * FLAGS_magnification), r / 100);

				accessorg.setValue(Coord(x * FLAGS_magnification, y * FLAGS_magnification, z * FLAGS_magnification), g / 100);

				accessorb.setValue(Coord(x * FLAGS_magnification, y * FLAGS_magnification, z * FLAGS_magnification), b / 100);

			}

			i++;

		}

		infile.close();



		grid->setName("density");

		gridr->setName("r");

		gridg->setName("g");

		gridb->setName("b");

	

		std::vector<std::string> splitFilename{};

		boost::algorithm::split(splitFilename, FLAGS_filename, boost::is_any_of("."));



		std::string resultFilename = splitFilename[0] + ".vdb";

		std::cout << "Writing file " << resultFilename << std::endl;

		openvdb::io::File file(resultFilename);



		grids.push_back(grid);



		if (FLAGS_rgb) {

			grids.push_back(gridr);

			grids.push_back(gridg);

			grids.push_back(gridb);

		}

		file.setCompression(0);

		file.write(grids);

		file.close();

		std::cout << "Finished!" << std::endl;

	}

	catch (std::exception& e) {

		std::cout << "Exception: " << e.what() << std::endl;

	}

}



int main(int argc, char* argv[]) {

	gflags::ParseCommandLineFlags(&argc, &argv, true);

	openvdb::initialize();

	readPly();

}
