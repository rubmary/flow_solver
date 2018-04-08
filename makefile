solve:      solve.cpp
			g++ -O3 -Wall -o solve solve.cpp -std=c++11

codifier:	codifier.cpp
			g++ -O3 -Wall -o codifier codifier.cpp -std=c++11

decodifier: decodifier.cpp
			g++ -O3 -Wall -o decodifier decodifier.cpp -std=c++11	

clean:
		rm -f *.sol *.txt *.clauses codifier decodifier solve

cleanData:
		rm -f *.txt