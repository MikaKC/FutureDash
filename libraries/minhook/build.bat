@echo off

cd build
if not exist VC19\ (
    mkdir VC19
) else (
    if "%1"=="re" (
        rmdir /s /q VC19
        mkdir VC19
    )
)

cd VC19

cmake ../.. -A Win32 -Thost=x86

msbuild minhook.sln /p:Configuration=Release /verbosity:Quiet /p:PlatformTarget=x86 /m
