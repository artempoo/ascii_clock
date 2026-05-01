all:
	meson compile -C build && ./build/ascii_clock

build:
	meson setup build

clean:
	rm -rf .cache && rm -rf build/

run:
	./build/ascii_clock

.PHONY: all build
