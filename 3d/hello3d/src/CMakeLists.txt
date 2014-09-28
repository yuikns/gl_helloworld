# src/

# include settings
#INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/lib)
#INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/lib/include)
INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include)

# lib settings
LINK_DIRECTORIES(${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib)



# all related files
AUX_SOURCE_DIRECTORY(. DIR_TARGET)
ADD_LIBRARY (relfiles ${DIR_TARGET})



# STEP I
# SET(SRC_LIST dsassign.cc)
ADD_EXECUTABLE(helloworld helloworld.c)

#  executable dependencies
ADD_DEPENDENCIES(helloworld iniparser)
ADD_DEPENDENCIES(helloworld GL)
ADD_DEPENDENCIES(helloworld glut)

#  executable target links
TARGET_LINK_LIBRARIES(helloworld relfiles)
TARGET_LINK_LIBRARIES(helloworld iniparser)
TARGET_LINK_LIBRARIES(helloworld GL) # opengl
TARGET_LINK_LIBRARIES(helloworld GLU) # opengl # for 'gluOrtho2D'
#TARGET_LINK_LIBRARIES(helloworld GLEW)# opengl
TARGET_LINK_LIBRARIES(helloworld glut) # glut
TARGET_LINK_LIBRARIES(helloworld m)
# Dependencies



#  executable properties
SET_TARGET_PROPERTIES(helloworld PROPERTIES OUTPUT_NAME "helloworld")

