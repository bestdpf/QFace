##############################
#QFace
##############################
project(QFace CXX)

#Check dependencies:
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

#SDL
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

FIND_PACKAGE(Boost REQUIRED thread)

#XSmilAgent
set(XSmilAgent_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/XSmilAgent)

#XFace Library
set(XFace_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/XFace/include)


set(NET_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/net)

###############wxXFacePlayer library
set(QFace_SRC
    QFace.cpp
    QtFace.cpp
    QtView.cpp
    SDLTimer.cpp
)
set(QFace_HEADERS
    QFace.h
    QtView.h
    QtFace.h
    SDLTimer.h
)
set(QFace_MOC_HEADERS
    QtView.h
    QFace.h
)

set(CMAKE_AUTOMOC TRUE)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${QT_QTOPENGL_INCLUDE_DIRS} ${XFace_INCLUDE_DIR} ${XSmilAgent_INCLUDE_DIR} ${NET_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
#link_directories()
add_executable(QFace ${QFace_SRC})
#set_target_properties(QFace PROPERTIES AUTOMOC TRUE)
target_link_libraries(QFace XSmilAgent XFace net ${Boost_LIBRARIES} ${QT_LIBRARIES} ${SDL_LIBRARY}) 
