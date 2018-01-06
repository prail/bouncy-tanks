import os
flags={"l":"-Wall -I.\src\ -lm -lallegro-5.0.10-mt -lallegro_image-5.0.10-mt","c":"-std=c99 -Wall -I."}
objects=[]
os.chdir("src")
for file in os.listdir("."):
    name,extension=file.split(".")
    if extension == "c":
        objects.append(name+".o")
        os.system("gcc -c {} -o {}.o {}".format(file,name,flags["c"]))
os.system("gcc {} -o ../bin/out.exe {}".format(" ".join(objects),flags["l"]))