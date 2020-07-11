all: myFieldRunner.out

CC = -std=c++11
SDLFLAGS = rsdl.cpp -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
OBJSDLFLAGS = rsdl.cpp  SDL2  SDL2_image  SDL2_ttf  SDL2_mixer

myFieldRunner.out: main.o BikeRunner.o Bullet.o BulletGoo.o BulletLightning.o BulletMissle.o Enemy.o HeavyRunner.o IceRunner.o ReadTextFile.o SimpleRunner.o TowerGatling.o TowerGoo.o TowerMissle.o Towers.o TowerTesla.o Variables.o FieldRunners.o
	g++ $(CC) -o myFieldRunner.out main.o BikeRunner.o Bullet.o BulletGoo.o BulletLightning.o BulletMissle.o Enemy.o HeavyRunner.o IceRunner.o ReadTextFile.o SimpleRunner.o TowerGatling.o TowerGoo.o TowerMissle.o Towers.o TowerTesla.o Variables.o FieldRunners.o $(SDLFLAGS)

main.o: main.cpp FieldRunners.h
	g++ $(CC) -c main.cpp 

FieldRunners.o: FieldRunners.cpp FieldRunners.h Variables.h TowerGatling.h ReadTextFile.h BulletMissle.h BulletLightning.h BulletGoo.h TowerMissle.h TowerTesla.h TowerGoo.h SimpleRunner.h IceRunner.h HeavyRunner.h BikeRunner.h
	g++ $(CC) -c FieldRunners.cpp

BikeRunner.o: BikeRunner.cpp BikeRunner.h Variables.h
	g++ $(CC) -c BikeRunner.cpp

Bullet.o: Bullet.cpp Bullet.h Variables.h
	g++ $(CC) -c Bullet.cpp 

BulletGoo.o: BulletGoo.cpp BulletGoo.h
	g++ $(CC) -c BulletGoo.cpp

BulletLightning.o: BulletLightning.cpp BulletLightning.h
	g++ $(CC) -c BulletLightning.cpp

BulletMissle.o: BulletMissle.cpp BulletMissle.h
	g++ $(CC) -c BulletMissle.cpp

Enemy.o: Enemy.cpp Enemy.h Variables.h
	g++ $(CC) -c Enemy.cpp

HeavyRunner.o: HeavyRunner.cpp HeavyRunner.h Variables.h
	g++ $(CC) -c HeavyRunner.cpp

IceRunner.o: IceRunner.cpp IceRunner.h Variables.h
	g++ $(CC) -c IceRunner.cpp

ReadTextFile.o: ReadTextFile.cpp ReadTextFile.h
	g++ $(CC) -c ReadTextFile.cpp

SimpleRunner.o: SimpleRunner.cpp SimpleRunner.h Variables.h
	g++ $(CC) -c SimpleRunner.cpp

TowerGatling.o: TowerGatling.cpp TowerGatling.h Variables.h
	g++ $(CC) -c TowerGatling.cpp

TowerGoo.o: TowerGoo.cpp TowerGoo.h Variables.h
	g++ $(CC) -c TowerGoo.cpp

TowerMissle.o: TowerMissle.cpp TowerMissle.h Variables.h
	g++ $(CC) -c TowerMissle.cpp

Towers.o: Towers.cpp Towers.h Variables.h
	g++ $(CC) -c Towers.cpp

TowerTesla.o: TowerTesla.cpp TowerTesla.h Variables.h
	g++ $(CC) -c TowerTesla.cpp

Variables.o: Variables.cpp Variables.h
	g++ $(CC) -c Variables.cpp

.PHONY: clean

clean:
	rm *.o
	rm myFieldRunner.out