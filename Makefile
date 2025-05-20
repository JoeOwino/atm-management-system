objects = src/main.o src/system.o src/auth.o src/menu.o src/register.o src/docs.o src/validation.o src/account.o src/transaction.o

atm: $(objects)
	cc -o atm $(objects)

src/main.o: src/header.h
src/system.o: src/header.h
src/auth.o: src/header.h
src/menu.o: src/header.h
src/register.o: src/header.h
src/docs.o: src/header.h
src/validation.o: src/header.h
src/account.o: src/header.h
src/transaction.o: src/header.h

clean:
	rm -f $(objects) atm
