<<<<<<< HEAD
# Install script for directory: /home/uauser/CLionProjects/Tram
=======
# Install script for directory: /home/uauser/CLionProjects/untitled
>>>>>>> 2ad297e0d0b6785587fecdd642a64c0a0bfaf1c3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< HEAD
  include("/home/uauser/CLionProjects/Tram/gtest/lib/googletest-master/cmake_install.cmake")
=======
  include("/home/uauser/CLionProjects/untitled/gtest/lib/googletest-master/cmake_install.cmake")
>>>>>>> 2ad297e0d0b6785587fecdd642a64c0a0bfaf1c3

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/home/uauser/CLionProjects/Tram/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/home/uauser/CLionProjects/untitled/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 2ad297e0d0b6785587fecdd642a64c0a0bfaf1c3
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
