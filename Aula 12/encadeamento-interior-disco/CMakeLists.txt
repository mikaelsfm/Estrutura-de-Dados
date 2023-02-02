cmake_minimum_required(VERSION 3.10)
project(encadeamento-interior-disco)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(encadeamento-interior-disco
        cliente.c
        cliente.h
        encadeamento_interior.c
        encadeamento_interior.h
        lista_clientes.c
        lista_clientes.h
        Makefile
        test_encadeamento_interior.c
        ufftest.h)
