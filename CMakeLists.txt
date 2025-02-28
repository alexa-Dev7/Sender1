cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-luWS -lssl -lcrypto")

add_executable(chat_server main.cpp storage.cpp encryption.cpp)
