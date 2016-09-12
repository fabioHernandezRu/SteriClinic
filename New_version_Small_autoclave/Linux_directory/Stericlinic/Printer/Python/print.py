
from Adafruit_Thermal import *
import SteriLogo as logo
from subprocess import call
import sys, getopt


printer = Adafruit_Thermal(str(sys.argv[1]), 19200, timeout=5)



call(["echo"," 1 >>" + str(sys.argv[1])])


try:  
    printer.wake();
    # Test inverse on & off
    printer.inverseOn()
    
    printer.inverseOff()
    
     # Test more styles
    printer.normal();
    #printer.justify('L')
    printer.boldOn()
    array = []
    with open(str(sys.argv[2]), "r") as f:
        for line in f:
            stringtoprint= line.rstrip('\n');
            printer.println(stringtoprint);
            print(stringtoprint)
    printer.boldOff()
    printer.feed(4)
    printer.sleep();
    
except IOError:
     print "False";
