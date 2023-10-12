all: project_file.exe

project_file.exe: src/mikros_hex_viewer.c src/data_formats.c src/datatype_len.c
	gcc src/mikros_hex_viewer.c src/data_formats.c src/datatype_len.c -o project_file.exe -lm

clean:
	rm project_file.exe
