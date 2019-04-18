@echo off
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86
) else (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
)

set includeDirs=/I "C:\Libraries\Includes"
set dependencies= "opengl32.lib" "glfw3.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" 

set compilerflags=/Od /Zi /EHsc /MDd /std:c++latest /I include %includeDirs% 

set linkerflags=/OUT:bin\main.exe /LIBPATH:"C:\Libraries\Libs" 

cl.exe %compilerflags% src\*.cpp src\*.c %dependencies% /link %linkerflags%

del bin\*.ilk *.obj *.pdb 