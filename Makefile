OUT_DIR = ./out
TARGET = main

${TARGET}::processes.o str.o
	cc -o ${TARGET} ${OUT_DIR}/processes.o ${OUT_DIR}/str.o main.c
processes.o::
	mkdir -p ${OUT_DIR}
	cc -c processes.c -o ${OUT_DIR}/processes.o
str.o::
	mkdir -p ${OUT_DIR}
	cc -c str.c -o ${OUT_DIR}/str.o
clean:
	rm -rf ${TARGET} ${OUT_DIR}
