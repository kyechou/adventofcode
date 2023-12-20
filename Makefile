.PHONY: all clean 2023 clean-2023

all:

2023:
	cmake -B 2023/build -S 2023
	cmake --build 2023/build

clean-2023:
	rm -rf 2023/build

clean: clean-2023
