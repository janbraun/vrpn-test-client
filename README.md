# Minimal, echoing VRPN test client

The client will connect to a tracker given by the command line
and echo all messages received verbosely, parsing them according
to the general scheme used at the DPZ, i.e., as KEY,VALUE pairs.


# Usage

./vrpn_test_client Tracker0@127.0.0.1


# Compilation

We use a simple cmake system without any real configuration.
In the source directory, try:
    mkdir build
    cd build
    cmake ..
    make

afterwards, the vrpn_test_client binary should be in the build
directory. The only thing which is important is that the vrpn
library can be found. If not, please contact Jan, or set
the CPATH, LD_\*_PATH and other variables accordingly.
