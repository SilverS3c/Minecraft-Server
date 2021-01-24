all:
	g++ -pthread -g -o build/Server -I . -I ./Packets -I Entity -I World *.cpp *.h Packets/*.cpp Packets/*.h Entity/*.cpp Entity/*.h World/*.h World/*.cpp