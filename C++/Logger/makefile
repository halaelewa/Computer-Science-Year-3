all: LogGenerator.cpp LogDumper.cpp
	  g++ -g  LogGenerator.cpp Logger.cpp LogMessage.cpp Utlis.cpp -o generator -lsqlite3

          g++ -o  LogDumper.cpp Logger.cpp LogMessage.cpp Utlis.cpp -o dumper -lsqlite3
        	./generator "Hello"
		./dumper generator
