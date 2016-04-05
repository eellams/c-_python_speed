#include "config.hpp"

namespace bpy = boost::python;

BOOST_PYTHON_MODULE(config)
{
  // The Configs class contains singleton
  bpy::class_<config::config>("Configs")
    .def_readwrite("ClassConfig", &config::configs.ClassConfig)
  ;

  bpy::class_<config::BaseWrap, boost::noncopyable>("BaseClass")
    .def("overrideMe", &config::BaseClass::overrideMe, &config::BaseWrap::default_overrideMe)
    ;
}
