run: build
	./build/calculator

build:
	cmake . -B./build -G Ninja
	cmake --build ./build

.PHONY: run build

