all: project_file.exe

project_file.exe: src/mikros_hex_viewer.c
	gcc src/mikros_hex_viewer.c -o project_file.exe -lm

clean:
	rm project_file.exe
