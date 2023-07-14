all: project_file.exe

project_file.exe: src/minimalist_hex_viewer.c
	gcc src/minimalist_hex_viewer.c -o project_file.exe

clean:
	rm project_file.exe