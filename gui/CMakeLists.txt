cmake_minimum_required(VERSION 3.15)
project(gui)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(gui
        src/prototype/controller/Controller.java
        src/prototype/view/MainView.fxml
        src/prototype/view/RootLayout.fxml
        src/prototype/Main.java)
