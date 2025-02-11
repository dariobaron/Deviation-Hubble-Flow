# to edit:
ARMAINCPATH = extern/armadillo/include/
ENSMALLENCPATH = extern/ensmallen/include/
CXX = g++

# do not edit:
SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.hpp) $(wildcard *.hpp)
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

setup: createvenv installlibs initrepo

installlibs: createvenv
	. env/bin/activate && python -m pip install -r requirements.txt

createvenv:
	if [ ! -d env ]; then python -m venv env; fi

initrepo:
	git config filter.strip-notebook-output.clean 'jupyter nbconvert --ClearOutputPreprocessor.enabled=True --to=notebook --stdin --stdout --log-level=ERROR'; \\
	git config filter.strip-notebook-output.smudge 'cat'; \\
	git config filter.strip-notebook-output.required true

clean:
	rm -f main.x project/*$(MODULEEXTENSION)