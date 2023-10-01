all: project_file.exe

project_file.exe: src/binary_viewer.c
	gcc src/binary_viewer.c -o project_file.exe -lm


clean:
	rm project_file.exe
