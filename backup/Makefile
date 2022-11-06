
all:
	mkdir -p build-appa-Desktop-Debug
	cd build-appa-Desktop-Debug/ && "/home/tuanpp/opt/Qt/5.15.2/gcc_64/bin/qmake" ../appa/appa.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make -f Makefile qmake_all && make -j4
	cd serviceb && make	
	# mkdir -p build-appc-Desktop-Debug
	# cd build-appc-Desktop-Debug/ && "/home/tuanpp/opt/Qt/5.15.2/gcc_64/bin/qmake" ../appc/appc.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make -f Makefile qmake_all && make -j4

clean:
	rm -rf build-appa-Desktop-Debug/
	rm -rf build-appa-Desktop-Debug/

runa:
	cd build-appa-Desktop-Debug/ && "/home/tuanpp/opt/Qt/5.15.2/gcc_64/bin/qmake" ../appa/appa.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make -f Makefile qmake_all && make -j4
	cd build-appa-Desktop-Debug && ./appa
runc:
	cd build-appc-Desktop-Debug && ./appc
runb:
	cd serviceb && make
	cd serviceb && ./build/serviceb
