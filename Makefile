ifeq ($(OS),Windows_NT)
  DEFAULT_TARGET=sensorsim-win32-debug
  CURRENT_DIR=
  EXECUTABLE_SUFFIX=.exe
  RM=del
else
  DEFAULT_TARGET=sensorsim-posix-debug
  CURRENT_DIR=./
  EXECUTABLE_SUFFIX=
  RM=rm
endif



default: $(DEFAULT_TARGET)$(EXECUTABLE_SUFFIX)

sensorsim-posix-debug: src/random_raw/random_raw.c
	gcc src/main.c -o $@ -g -DPOSIX -DDEBUG  -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Wno-unused-variable -Wno-unused-argument -Wno-unused-parameter -Wno-

sensorsim-win32-debug.exe: src/random_raw/random_raw.c
	gcc src/main.c -o $@ -g -DWIN32 -DDEBUG -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Wno-unused-variable -Wno-unused-argument -Wno-unused-parameter -Wno-unused-function

src/random_raw/random_raw.c: random_raw_gen$(EXECUTABLE_SUFFIX)
	$(CURRENT_DIR)random_raw_gen$(EXECUTABLE_SUFFIX)

random_raw_gen$(EXECUTABLE_SUFFIX):
	g++ src/random_raw/random_raw_gen.cpp -o random_raw_gen$(EXECUTABLE_SUFFIX)

clean:
	$(RM) sensorsim-posix-debug
	$(RM) sensorsim-win32-debug.exe
	$(RM) random_raw_gen$(EXECUTABLE_SUFFIX)
	$(RM) src\random_raw\random_raw.c
	$(RM) sim.log
	$(RM) data.csv

.PHONY: default clean