#ifndef _CONFIG_CLASS_H
#define _CONFIG_CLASS_H

#include <boost/python.hpp>
#include <iostream>

#define STRINGIFY(x) #x
#define WRAPPER(TYPE, CLASS, FUNCTION, ARGS...) TYPE FUNCTION(ARGS) { if (override FUNCTION = this->get_override( STRINGIFY(FUNCTION) )) FUNCTION(ARGS); \
    return CLASS::FUNCTION(ARGS); \
  } \
  TYPE default_##FUNCTION(ARGS) { return this->CLASS::FUNCTION(ARGS); }
#define WRAPPER_CLASS(CLASS) public CLASS, public boost::python::wrapper<CLASS>

namespace bpy = boost::python;

namespace config {
  class BaseClass {
  protected:
    BaseClass() {}
    ~BaseClass() {}

  public:
    virtual void overrideMe(int num) {
      //std::cout << "Base override" << std::endl;
      int i=1,j,k;

      //num = 657843;
      //num = 10;
      while(i<=num){
          k=0;
          if(num%i==0){
             j=1;
              while(j<=i){
                if(i%j==0)
                     k++;
                 j++;
              }
              if(k==2) {}//std::cout << i << " is a prime factor" << std::endl;
                 //printf("\n%d is a prime factor",i);
          }
          i++;
       }
    }
  };


  class BaseWrap : public BaseClass, public bpy::wrapper<BaseClass> {
  public:
    BaseWrap() : BaseClass() {}

    // I can't seem to ever call this function?
    //  however, it is needed?
    void overrideMe(int num) {
      if (bpy::override overrideMe = this->get_override("overrideMe"))
        overrideMe(num); // *note*
      return BaseClass::overrideMe(num);
    }

    // What is done by default?
    void default_overrideMe(int num) { return this->BaseClass::overrideMe(num); }

  };
}

#endif
