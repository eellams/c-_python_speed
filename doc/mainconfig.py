from config import Configs # Contains all of the configs that are used in C++
from config import BaseClass # Classes defined in C++

class derived2(BaseClass):
    def overrideMe(self, num):
        #print("Asdf-asdf-asdf")
        #num = 657843
        #num = 10
        i = 1
        while i <= num:
            k = 0
            if num%i == 0:
                j = 1
                while j <= i:
                    if i%j == 0:
                        k += 1
                    j += 1
                if k == 2:
                    #print(str(i) + " is a prime factor")
                    pass
            i += 1

d = derived2();
#d.overrideMe()

# Default as defined in the C++ code
#Configs.ClassConfig.overrideMe()

# Overwrite with our own class [derived2]
Configs.ClassConfig = d
#Configs.ClassConfig.overrideMe() # This is the function as defined in derived2
