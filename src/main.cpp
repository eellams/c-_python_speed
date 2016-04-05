// based on boost python tutorial: http://www.boost.org/doc/libs/1_58_0/libs/python/doc/tutorial/doc/html/python/embedding.html
// usage: g++ -I/usr/include/boost  -I/usr/include/python3.4 main.cpp -o main -lpython3.4m -lboost_python3

#include <string>
#include <boost/python.hpp>
#include <boost/python/object.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer.hpp>
#include <iostream>
#include <fstream>

#define SIZE 1000
#define REPS 1000

#include "config.hpp"

namespace bpy = boost::python;
namespace bfs = boost::filesystem;

float timeTaken_py[SIZE];
float timeTaken_extract[SIZE];

int main(int argc, char *argv[]) {
  std::cout << "Program startup!" << std::endl;

  boost::timer boost_timer;// = new boost::timer();

  bfs::path basedir = bfs::system_complete(argv[0]).parent_path();
  bfs::path libdir = basedir / bfs::path("../lib");
  bfs::path confdir = basedir / bfs::path("../doc");

  try {
    // If you're going to use threads: PyEval_InitThreads();
    Py_Initialize();

    bpy::object main_module = bpy::import("__main__");
    bpy::object main_namespace = main_module.attr("__dict__");

    bpy::object sys = bpy::import("sys");
    bpy::object os = bpy::import("os");

    // Set up the environment variables (path and environment)
    sys.attr("path").attr("append")(libdir.string());
    sys.attr("path").attr("append")(confdir.string());

    os.attr("environ").attr("__setitem__")("LD_LIBRARY_PATH", libdir.string());

    // Now path has been set, we can import our own modules (yay!)
    bpy::object config = bpy::import("config");

    /* Put yur Python tizz 'ere */
    //bpy::object pythontest = bpy::exec("print('Hello from Python!');", main_namespace);

    // Python file
    bpy::object mainconfig = bpy::import("mainconfig");

    // The config works!
    //config::config_graphics cg = bpy::extract<config::config_graphics>(config.attr("Configs").attr("GraphicsConfig"));

    config::BaseWrap bw = bpy::extract<config::BaseWrap>(config.attr("Configs").attr("ClassConfig"));
    bpy::object x = config.attr("Configs").attr("ClassConfig");

    //bw.overrideMe();
    //bpy::call_method<void>(x.ptr(), "overrideMe");

    int i, j;

    for (i=0; i<SIZE; i++) {
      boost_timer.restart();

      for (j=0; j<REPS; j++) {
        bpy::call_method<void>(x.ptr(), "overrideMe", i);
      }

      timeTaken_py[i] = boost_timer.elapsed();
    }

    for (i=0; i<SIZE; i++) {
      boost_timer.restart();

      for (j=0; j<REPS; j++) {
        bw.overrideMe(i);
      }

      timeTaken_extract[i] = boost_timer.elapsed();
    }

    std::ofstream myfile;
    myfile.open ("example.txt");

    for (i=0; i<SIZE; i++) {
      myfile << timeTaken_py[i] << ",";
    }

    myfile << std::endl;
    for (i=0; i<SIZE; i++) {
      myfile << timeTaken_extract[i] << ",";
    }

    //myfile << "Writing this to a file.\n";
    myfile.close();
    return 0;

    // Here are 3 test units, unccoment ONE as appropriate
    //  interestingly, extracted C++ class is about 2x slower than the python object
    //
    // Python object
    //for(int i=0; i<1000000; i++) bpy::call_method<void>(x.ptr(), "overrideMe");
    //
    // C++ class extracted from Python object
    //for(int i=0; i<1000000; i++) bw.overrideMe();
    //
    // Pure C++ class (comparison)
    /*config::BaseWrap testbw;
    for(int i=0; i<1000000; i++) testbw.overrideMe();*/

    //bw.overrideMe();

    // C++ function, hidden from python 'wrapping'
    //cg.print_resolution();

    std::cout << "Program finished!" << std::endl;
  }
  catch (bpy::error_already_set const&) {
    PyErr_Print();
  }

  return 0;
}
