FLAGS = -std=c++17 -masm=intel -fconcepts -pthread -fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override


main :  main.cpp Cont.hpp Vect.hpp BST.hpp MyWChar.hpp MyChar.hpp
	g++ $(FLAGS) main.cpp -o main

run:
	clear && make main && ./main

clean:
	rm main
