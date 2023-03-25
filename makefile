OBJ = rk4.o ludcmp.o top.o

fig1: fig1.o $(OBJ)
	g++ fig1.o $(OBJ)
fig2: fig2.o $(OBJ)
	g++ fig2.o $(OBJ)
fig3: fig3.o $(OBJ)
	g++ fig3.o $(OBJ)
fig4: fig4.o $(OBJ)
	g++ fig4.o $(OBJ)