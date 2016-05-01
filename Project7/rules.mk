# Add .d to Make's recognized suffixes.
SUFFIXES += .d

#We don't need to clean up when we're making these targets
NODEPS:=clean tags svn

#Find all the C++ files in the src/ directory (but not test_.. or main_...)
SOURCES:=$(shell find src \( -regex '\([A-Za-z0-9][-._A-Za-z0-9]*/\)*[A-Za-z0-9][-._A-Za-z0-9]*' \) -and \( -name '*.cpp' -or -name '*.c' \) -and -not \( -name 'test_*' -or -name 'main_*' \) )
MAIN_SOURCES:=$(shell find src \( -name '*.cpp' -or -name '*.c' \) -and \( -name 'main_*' \) )
TEST_SOURCES:=$(shell find src \( -name '*.cpp' -or -name '*.c' \) -and \( -name 'test_*' \) )
ALL_SOURCES=$(SOURCES) $(MAIN_SOURCES) $(TEST_SOURCES)

OBJECTS=$(patsubst src/%,tmp/%.o,$(SOURCES))
MAIN_OBJECTS=$(patsubst src/%,tmp/%.o,$(MAIN_SOURCES))
TEST_OBJECTS=$(patsubst src/%,tmp/%.o,$(TEST_SOURCES))
ALL_OBJECTS=$(OBJECTS) $(MAIN_OBJECTS) $(TEST_OBJECTS)

#These are the dependency files, which make will clean up after it creates them
DEPFILES:=$(patsubst src/%,tmp/%.d,$(ALL_SOURCES))

#Don't create dependencies when we're cleaning, for instance
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    #Chances are, these files don't exist.  GMake will create them and
    #clean up automatically afterwards
    -include $(DEPFILES)
endif

#This is the rule for creating the cpp dependency files
tmp/%.cpp.d: src/%.cpp
	g++ $(GXXFLAGS) -MM -MT '$(patsubst src/%.cpp,tmp/%.cpp.o,$<)' $< -MF $@

#This is the rule for creating the c dependency files
tmp/%.c.d: src/%.c
	mkdir -p `dirname $@`
	gcc $(CFLAGS) -MM -MT '$(patsubst src/%.c,tmp/%.c.o,$<)' $< -MF $@

#This rule does the compilation to object files
tmp/%.cpp.o: src/%.cpp tmp/%.cpp.d
	mkdir -p `dirname $@`
	$(CXX) $(CXXFLAGS) -o $@ -c $<

tmp/%.c.o: src/%.c tmp/%.c.d
	$(CC) $(CFLAGS) -o $@ -c $<

lib/lib$(TARGET).a : $(OBJECTS)
	ar crv $@ $^

lib/lib$(TARGET).so : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -shared  -o $@ $^ $(LDFLAGS)

clean : 
	/bin/rm -rf tmp/* bin/* lib/*

bin/test_% : tmp/test_%.cpp.o lib/lib$(TARGET).so lib/lib$(TARGET).a
	$(CXX) $(CXXFLAGS) -o $@ $< -Llib -l$(TARGET) $(LDFLAGS)

bin/test_% : tmp/test_%.c.o lib/lib$(TARGET).so lib/lib$(TARGET).a
	$(CC) $(CFLAGS) -o $@ $< -Llib -l$(TARGET) $(LDFLAGS)

bin/% : tmp/main_%.cpp.o lib/lib$(TARGET).so lib/lib$(TARGET).a
	$(CXX) $(CXXFLAGS) -o $@ $< -Llib -l$(TARGET) $(LDFLAGS)

bin/% : tmp/main_%.c.o lib/lib$(TARGET).so lib/lib$(TARGET).a
	$(CC) $(CFLAGS) -o $@ $< -Llib -l$(TARGET) $(LDFLAGS)

q :
	echo "SOURCES = $(SOURCES)"
	echo "MAIN_SOURCES = $(MAIN_SOURCES)"
	echo "TEST_SOURCES = $(TEST_SOURCES)"
	echo "ALL_SOURCES = $(ALL_SOURCES)"

