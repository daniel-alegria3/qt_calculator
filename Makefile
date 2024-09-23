run: build
	./build/calculator

build:
	cmake -B./build -S.
	make -C build

.PHONY: run build

