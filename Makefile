all: project_file.exe

project_file.exe: src/decimal_viewer.c
	gcc src/decimal_viewer.c -o project_file.exe -lm


clean:
	rm project_file.exe
