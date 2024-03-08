.PHONY: all clean external_module

BUILD_DIR=./build
INCLUDE_DIR=../lib

all: dir main

dir:
	mkdir -p ${BUILD_DIR}

default:
	g++ -shared -I${INCLUDE_DIR} -fPIC ./modules/default_lib.cpp -o ${BUILD_DIR}/libmodule1.so -DDEFAULT_MODULE 

external_module:
	g++ -shared -fPIC ./modules/external_module.cpp -o ${BUILD_DIR}/external_module.so -I${INCLUDE_DIR} 

main: default
	g++ main.cpp -I${INCLUDE_DIR} -fPIC -L${BUILD_DIR} -lmodule1 -o ${BUILD_DIR}/main -Wl,-rpath=$(PWD)/${BUILD_DIR} -DDEFAULT_MODULE

clean:
	rm -rf ${BUILD_DIR}
