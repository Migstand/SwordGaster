cmake_minimum_required(VERSION 3.20)

project(ClienteCoordenadas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
find_package(CURL REQUIRED)
find_package(pugixml CONFIG REQUIRED)

add_executable(ClienteCoordenadas
    src/main.cpp
    src/comunicacao/HttpClient.cpp
    src/soap/SoapResponseParser.cpp
    src/jogo/Personagem.cpp
    src/jogo/ControleJogo.cpp
    src/jogo/ServicoCoordenadas.cpp
)

target_link_libraries(ClienteCoordenadas
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    CURL::libcurl
    pugixml::pugixml
)

target_include_directories(ClienteCoordenadas
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)