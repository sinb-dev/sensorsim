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
	gcc src/main.c -o $@ -g -std=c11 -DPOSIX -DDEBUG  -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Wno-unused-variable -Wno-unused-argument -Wno-unused-parameter -Wno-

sensorsim-win32-debug.exe: src/random_raw/random_raw.c
	gcc src/main.c -o $@ -g -std=c11 -DWIN32 -DDEBUG -Wall -Wextra -Werror -Wfatal-errors -Wpedantic -Wno-unused-variable -Wno-unused-argument -Wno-unused-parameter -Wno-unused-function -Wno-pedantic-ms-format

src/random_raw/random_raw.c: random_raw_gen$(EXECUTABLE_SUFFIX)
	$(CURRENT_DIR)random_raw_gen$(EXECUTABLE_SUFFIX)

random_raw_gen$(EXECUTABLE_SUFFIX):
	g++ src/random_raw/random_raw_gen.cpp -o random_raw_gen$(EXECUTABLE_SUFFIX)

perf: sensorsim-perf$(EXECUTABLE_SUFFIX)
	$(CURRENT_DIR)sensorsim-perf$(EXECUTABLE_SUFFIX)

sensorsim-perf$(EXECUTABLE_SUFFIX): src/random_raw/random_raw.c
	gcc src/perf/perf_win32.c -o $@ -O3

clean:
	$(RM) sensorsim-posix-debug
	$(RM) sensorsim-win32-debug.exe
	$(RM) sensorsim-perf
	$(RM) sensorsim-perf.exe
	$(RM) random_raw_gen$(EXECUTABLE_SUFFIX)
	$(RM) src\random_raw\random_raw.c
	$(RM) sim.log
	$(RM) data.csv

.PHONY: default clean perf