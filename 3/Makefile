JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) -Xlint:all $*.java

CLASSES = \
        Gibaus.java \
        Gibaus_sem.java \
        Gibaus_mutex.java \
        Zwergenbaeckerei.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
