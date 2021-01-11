all:
	g++ -pthread -g -o build/Server -I . -I ./Packets -I Entity *.cpp *.h Packets/*.cpp Packets/*.h Entity/*.cpp Entity/*.h