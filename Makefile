PY_INCLUDES := $(shell python3-config --includes)
OUTPUT = pync
SOURCES = pync.c pync_module.c

b:
	$(CC) -o $(OUTPUT).so -shared -fPIC $(PY_INCLUDES) $(SOURCES)

c:
	rm $(OUTPUT).so

.PHONY: b c
