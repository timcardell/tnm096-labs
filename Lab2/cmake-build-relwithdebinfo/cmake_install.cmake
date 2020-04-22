<<<<<<< HEAD:Lab2/cmake-build-relwithdebinfo/cmake_install.cmake
# Install script for directory: /Users/timcardell/Documents/tnm096-lab2/TNM096-lab2
=======
# Install script for directory: /Users/timcardell/Documents/tnm096-labs
>>>>>>> e955c195950019d5178dbf2c1ae93e60bd9a5dd5:cmake-build-relwithdebinfo/cmake_install.cmake

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
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD:Lab2/cmake-build-relwithdebinfo/cmake_install.cmake
file(WRITE "/Users/timcardell/Documents/tnm096-lab2/TNM096-lab2/cmake-build-relwithdebinfo/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/Users/timcardell/Documents/tnm096-labs/cmake-build-relwithdebinfo/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> e955c195950019d5178dbf2c1ae93e60bd9a5dd5:cmake-build-relwithdebinfo/cmake_install.cmake
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
