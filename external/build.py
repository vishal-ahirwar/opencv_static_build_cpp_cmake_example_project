from os import system,cpu_count,path
GENERATOR:str="\"Ninja\""
conan_file_exist:bool=path.exists("conanfile.txt")
if __name__=="__main__":
    if not conan_file_exist:
        print('Building Opencv...')
        if not system(f"cd opencv && ninja -C build -j{cpu_count()-1}"):
            exit(0)
        if not system(f"cd opencv && cmake -S . -Bbuild -G {GENERATOR} -DBUILD_SHARED_LIBS=OFF"):
            system(f"cd opencv && ninja -C build -j{cpu_count()-1}")
