# Minimalistic VRPN Test-Client.
# Abstraction to ease access to DPZ HDF5 files, providing
# the structured information by a class framework.
cmake_minimum_required(VERSION 3.15.0)

# Needed when using statically linked libvrpn
find_package(Threads REQUIRED)


# VRPN Test client
add_executable(vrpn_test_client
    vrpn_test_client_main.cpp
    vrpn_client.h vrpn_client.cpp
)
# Directly linking threads is a workaround
# for using vrpn static libraries on the embedded targets.
target_link_libraries(vrpn_test_client
    stdc++fs
    vrpn Threads::Threads
)
