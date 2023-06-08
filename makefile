



proj5: Book.o EReader.o driver.cpp
	$(CXX) $(CXXFLAGS) Book.o EReader.o driver.cpp -o proj5

make run:
	./proj5 proj5_books.txt

clean:
	rm -f *.o
	rm -f *~

