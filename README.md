# Mikros-Hex-Viewer

View and analyze files in various formats (hexadecimal, binary, decimal, and character) at once with this small command-line hex viewer.

![Mikros in action](readme-assets/showcase.png)

## Download and Compilation
### Prerequisites:
- git
- gcc
- make

Clone the repository and run the makefile:
```shell
git clone https://github.com/ThomasWaytec/Mikros-Hex-Viewer.git
cd ./Mikros-Hex-Viewer
make
```

## Usage
Type in ```./mikros``` followed by the name of the file you'd like to analyze.  
Add any optional arguments after.
### Output Format:
 - ```-x``` for hexadecimal (default)
 - ```-d``` for decimal
 - ```-b``` for binary
 - ```-c``` for character
You may use more than one format at once.  
The arguments can also be combined: ```-xdbc```
### Examples:
``` shell
./mikros username.txt
./mikros file.bin -b
./mikros images/photo.jpg -hxb
./mikros README.md -hc
```
Enhance your usage of Mikros-Hex-Viewer by adding its folder path to your Bash or PowerShell path environment variable. This will enable you to conveniently use mikros from any location in your command-line.