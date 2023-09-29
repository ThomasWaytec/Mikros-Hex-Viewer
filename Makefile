all: project_file.exe

project_file.exe: src/mikros_hex_viewer.c
	gcc src/mikros_hex_viewer.c -o mikros_hex_viewer.exe -lm

clean:
	rm project_file.exe
