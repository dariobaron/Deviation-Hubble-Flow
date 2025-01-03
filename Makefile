# to edit:
ARMAINCPATH = /home/dario/repos/armadillo/include/
ENSMALLENCPATH = /home/dario/repos/ensmallen/include/
CXX = g++

# do not edit:
SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.hpp)
MODULEEXTENSION := $(shell python-config --extension-suffix)
COMPILEDMODULES := $(patsubst src/%.cpp,project/%$(MODULEEXTENSION),$(SOURCES))
MODULENAMES := $(patsubst src/%.cpp,%,$(SOURCES))

PYBIND11INCLUDEPATH = $(shell python -m pybind11 --includes)
NUMPYINCLUDEPATH = $(shell python -c "import numpy; print(numpy.get_include())")
PYTHONRUNTIMELIB := $(shell python-config --ldflags)

WARNINGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
INCLUDEPATH = -I$(ARMAINCPATH) -I$(ENSMALLENCPATH) $(PYBIND11INCLUDEPATH) -I$(NUMPYINCLUDEPATH)
LINKINGLIBS = -lopenblas -llapack $(PYTHONRUNTIMELIB)
COMPILATIONFLAGS = -std=c++20 -O3 -fPIC -shared -fconcepts-diagnostics-depth=2 -fvisibility=hidden

.PHONY: all $(MODULENAMES) setup clean main

all: $(COMPILEDMODULES)

main: main.cpp
	$(CXX) -o main.x main.cpp -std=c++20 -O3 $(WARNINGS) -lopenblas -llapack -I$(ARMAINCPATH) -I$(ENSMALLENCPATH)

$(MODULENAMES): % : project/%$(MODULEEXTENSION)

project/%$(MODULEEXTENSION): src/%.cpp $(HEADERS)
	$(CXX) -o $@ $< $(COMPILATIONFLAGS) $(WARNINGS) $(LINKINGLIBS) $(INCLUDEPATH)

setup: createvenv
	. env/bin/activate && python -m pip install -r requirements.txt

createvenv:
	if [ ! -d env ]; then python -m venv env; fi

clean:
	rm -f main.x project/*$(MODULEEXTENSION)