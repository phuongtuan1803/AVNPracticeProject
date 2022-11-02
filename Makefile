
all:
	mkdir -p build-serviceb
	cd build-serviceb/ && cmake ../serviceb/ && make
	./build-serviceb/serviceb

clean:
	rm -rf $(ls -d build-*)
	rm -rf build-serviceb

