#ifndef _CONFIG_H
#define _CONFIG_H

#include "config_class.hpp"
#include <boost/python.hpp>

namespace config {

  // configs contains all of the structures that can be changed in the config files
  struct config {
    BaseWrap ClassConfig;

  } configs;

}

#endif
