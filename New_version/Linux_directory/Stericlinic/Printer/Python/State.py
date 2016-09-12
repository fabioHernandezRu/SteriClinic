

from Adafruit_Thermal import *
import SteriLogo as logo
from subprocess import call


printer = Adafruit_Thermal("/dev/ttyS1", 19200, timeout=5)

call(["echo"," 1 >> /dev/ttyS1"])


status=0;
def main():
    try:            
        printer.wake();
        status=printer.hasPaper();
        printer.sleep();
        print str(status)
    except IOError:
         print "False";

if __name__ == '__main__':
  main()

