all: build

build: tema1.obj
	cl /MD tema1.obj compare.lib

tema1.obj: tema1.c
		cl /c tema1.c

obj_clean:
		del *.obj
exec_clean:
		del tema1.exe
