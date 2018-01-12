FLAGS += -O2
CFLAGS += -I./inc

OUTPUT = bin/mp3Metadata
SRC = scr/main.cpp
SRC += scr/MP3Metadata.cpp

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUTPUT)
