# JNI-Howto
Quick guide to JNI

## Steps

```
1- Create Java file with JNI calls (JNICode.java)
2- Compile Java: javac JNICode.java (or use Eclipse, for instance)
3- Create C header: javah -o JNICode.h JNICode
4- Create C file (NativeCode.c)
5- Compile C: see bin/COMPILA_C
6- Create Test Java file (JNITest.java)
2- Compile Test Java: javac JNITest.java
6- Run test: java -Djava.library.path=./ JNITest
```

