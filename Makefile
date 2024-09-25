run: build test
	./build/calculator

test: build
	ctest --test-dir build/rpn --output-on-failure


build:
	cmake . -B build -G Ninja
	cmake --build build

clean:
	rm -rf build

.PHONY: build run test clean

