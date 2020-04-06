#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc() */ 
#include <string.h> /* memset() */

#define UNUSED(x) (void)(x);
#define RED "\x1b[31m"
#define RESET "\x1b[0m" 
#define MAX_SIZE 100

typedef void (*vfunc_t)(void *);
typedef char *(*to_string_t)(void *);
typedef int (*get_num_masters_t)(void *);

typedef enum vMetods{
	HASH_CODE,
	TO_STRING,
	FINALIZE,
	NUM_MASTERS,
	SAY_HELLO
} vmethods_t;

/*******************class structs definitions********************/
typedef struct Class{
	char *name;
	size_t size;
	struct Class *super;
	vfunc_t (*class_Vtable)[];
} class_t;

typedef struct Object{
	class_t *metadata;
} object_t;

typedef struct Animal{
	object_t obj;
	int num_legs;
	int num_masters;
	int ID;
} animal_t;

typedef struct Dog {
	animal_t animal;
	int num_legs;
} dog_t;

typedef struct Cat {
	animal_t animal;
	char *colors;
	int num_masters;
} cat_t;

typedef struct LegendaryAnimal {
	cat_t cat;
} legendary_t;

/*********************functions declarations******************/
void objectFinalize		(object_t *this);
size_t objectHashCode	(object_t *this);
char *objectToString	(object_t *this);
void animalSayHello		(animal_t *this);
int animalGetNumMasters	(animal_t *this);
char *animalToString	(animal_t *this);
void animalFinalize		(animal_t *this);
void dogSayHello		(dog_t *this);
void dogFinalize		(dog_t *this);
char *dogToString		(dog_t *this);
void catFinalize		(cat_t *this);
char *catToString		(cat_t *this);
void catSayHello		(cat_t *this);
char *legendaryToString	(legendary_t *this);
void legendaryFinalize	(legendary_t *this);
void legenderySayHello	(legendary_t *this);

/***********************Initializations***********************/

vfunc_t object_Vtable[] = 		{(vfunc_t)objectHashCode,
		            			(vfunc_t)objectToString,
					            (vfunc_t)objectFinalize,
		            			};

vfunc_t animal_Vtable[] = 		{(vfunc_t)objectHashCode,
								(vfunc_t)animalToString,
								(vfunc_t)animalFinalize,
								(vfunc_t)animalGetNumMasters,
								(vfunc_t)animalSayHello,
								};
							
vfunc_t dog_Vtable[] = 			{(vfunc_t)objectHashCode,
								(vfunc_t)dogToString,
								(vfunc_t)dogFinalize,
				        		(vfunc_t)animalGetNumMasters,
								(vfunc_t)dogSayHello,
								};
						
vfunc_t cat_Vtable[] = 			{(vfunc_t)objectHashCode,
								(vfunc_t)catToString,
								(vfunc_t)catFinalize,
				        		(vfunc_t)animalGetNumMasters,
								(vfunc_t)animalSayHello
								};

vfunc_t legendary_Vtable[] = 	{(vfunc_t)objectHashCode,
						    	(vfunc_t)legendaryToString,
						    	(vfunc_t)legendaryFinalize,
						    	(vfunc_t)animalGetNumMasters,
						    	(vfunc_t)legenderySayHello,
						    	};
						    	

/************************* Globals ******************************/
int animal_counter = 0;
char str[MAX_SIZE];

/*******************metadata initialization**********************/
class_t object_meta = {"Object", sizeof(object_t), NULL, &object_Vtable};
class_t animal_meta = {"Animal", sizeof(animal_t), &object_meta, &animal_Vtable};
class_t dog_meta = {"Dog", sizeof(dog_t), &animal_meta, &dog_Vtable};
class_t cat_meta = {"Cat", sizeof(cat_t), &animal_meta, &cat_Vtable};
class_t legendary_meta = {"LegendaryAnimal", sizeof(legendary_t), &cat_meta, &legendary_Vtable};

/*************************Static blocks*****************************/
static void animalStaticBlock()
{
	static int flag = 0;

	if(0 == flag)
	{
		printf("Static block Animal 1\n");
		printf("Static block Animal 2\n");
		++flag;
	}
}

static void dogStaticBlock()
{
	static int flag = 0;
	
	if(0 == flag)
	{
		printf("Static block Dog\n");
		++flag;
	}
}

static void catStaticBlock()
{
	static int flag = 0;
	
	if (0 == flag)
	{
		printf("Static block Cat\n");
		++flag;
	}
}
	
static void legendaryStaticBlock()
{
	static int flag = 0;

	if (0 == flag)
	{
		printf("Static block Legendary Animal\n");
		++flag;
	}
}

/**************** functions implementatin******************/

/*********************** Object ***************************/
/* funcs */
size_t objectHashCode(object_t *this) 
{
	return (size_t)this;
}

char *objectToString(object_t *this)
{
	memset(str,' ', 100);
	sprintf(str, "%s@%lu", this->metadata->name, (size_t)objectHashCode(this));
	
	return str;
}

void objectFinalize(object_t *this) 
{
	free(this);
}

/*************************Animal*****************************/
/* funcs */
void animalShowCounter(){
	animalStaticBlock();
	printf("%d\n", animal_counter);
}

void animalSayHello(animal_t *this)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

int animalGetNumMasters(animal_t *this)
{
	return this->num_masters;
}

char *animalToString(animal_t *this)
{
	memset(str,' ', 100);
	sprintf(str, "Animal with ID: %d", this->ID);

	return str;
}

void animalFinalize(animal_t *this) 
{
	printf(RED "finalize Animal with ID: %d\n" RESET, this->ID);
	objectFinalize((object_t *)this);
}


/* CONSTRUCTORS */
void animalCtor(animal_t *this)
{
	char *string_result = NULL;
	
	animalStaticBlock();
	
	{
		printf("Instance initialization block Animal\n");
	}
	
	printf("Animal Ctor\n");
	
	this->ID = ++animal_counter;
	this->num_legs = 5;	
	this->num_masters = 1;
	
	(*this->obj.metadata->class_Vtable)[SAY_HELLO](this);
	animalShowCounter(NULL);
	string_result = ((to_string_t)
				((*this->obj.metadata->class_Vtable)[TO_STRING]))(this);
	printf ("%s\n", string_result);
	string_result = objectToString((object_t *)this);
	printf("%s\n", string_result);
}

void animalIntCtor(animal_t *this, int *num_masters)
{
	animalStaticBlock();
	
	printf("Animal Ctor int\n");
	
	this->ID = ++animal_counter;
	this->num_legs = 5;	
	this->num_masters = *num_masters;
}

/***************************Dog******************************/
/* funcs */
void dogSayHello(dog_t *this)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

char *dogToString(dog_t *this)
{	
	memset(str,' ', 100);
	sprintf(str, "Dog with ID: %d", this->animal.ID);
	
	return str;
}

void dogFinalize(dog_t *this) 
{
	printf(RED "finalize Dog with ID: %d\n" RESET, ((animal_t *)this)->ID);
	objectFinalize((object_t *)this);
}

/* CONSTRUCTOR */
void dogCtor(dog_t *this)
{
	int i = 2;
	
	dogStaticBlock();
	
	animalIntCtor((animal_t *)this, &i);
	
	{
		printf("Instance initialization block Dog\n");
	}

	printf("Dog Ctor\n");
	
	this->num_legs = 4;
}

/*************************Cat***************************/
/* funcs */
char *catToString(cat_t *this)
{	
	memset(str,' ', 100);
	sprintf(str, "Cat with ID: %d", this->animal.ID);
	 
	return str;
}

void catFinalize(cat_t *this) 
{
	printf(RED "finalize Cat with ID: %d\n" RESET, ((animal_t *)this)->ID);
	objectFinalize((object_t *)this);
}

/* CONSTRUCTOR*/
void catStringCtor(cat_t *this, char *colors)
{
	catStaticBlock();
	this->num_masters = 5;
	animalCtor((animal_t *)this);	
	this->colors = colors;
	printf("Cat Ctor with color: %s\n", colors);
}

void catCtor(cat_t *this)
{	
	catStaticBlock();
	
	catStringCtor(this, "black");
	this->num_masters = 2;
	printf("Cat Ctor\n");
}

/*************************LegendaryAnimal**********************8*/
/* funcs */
char *legendaryToString(legendary_t *this)
{	
	memset(str,' ', 100);
	sprintf(str, "LegendaryAnimal with ID: %d", ((animal_t *)this)->ID);
			
	return str;
}

void legenderySayHello(legendary_t *this)
{
	UNUSED(this);
	
	printf("Legendary Hello!\n");
}

void legendaryFinalize(legendary_t *this) 
{
	printf(RED "finalize LegendaryAnimal with ID: %d\n" RESET,
			((animal_t *)this)->ID);
	objectFinalize((object_t *)this);
}

/* CONSTRUCTOR */
void legendaryCtor(legendary_t *this)
{
	legendaryStaticBlock();
	catCtor((cat_t *)this);
	printf("Legendary Ctor\n");
}

/**************************new*********************************/
object_t *objectAlloc(class_t *class)
{
	object_t *obj = (object_t *)malloc(class->size);
	obj->metadata = class;
	
	return obj;
}

/**************************java2cFoo***************************/
void java2cFoo(animal_t *animal)
{
	char *string_result = 
	((to_string_t)((*animal->obj.metadata->class_Vtable)[TO_STRING]))(animal);
	printf("%s\n", string_result);
}

int main()
{   
    animal_t *array[5] = {0};

    int i = 0;
	
    animal_t *animal = (animal_t *)objectAlloc(&animal_meta);
	dog_t *dog = (dog_t *)objectAlloc(&dog_meta);
	cat_t *cat = (cat_t *)objectAlloc(&cat_meta);
	legendary_t *legendary = (legendary_t *)objectAlloc(&legendary_meta);
	cat_t *cat_color = NULL;
    
    animalCtor(animal);
   	dogCtor(dog);
    catCtor(cat);
    legendaryCtor(legendary);
   
   	animalShowCounter();
   	
   	printf("%d\n", ((animal_t *)animal)->ID);
	printf("%d\n", ((dog_t *)dog)->animal.ID);
	printf("%d\n", ((cat_t *)cat)->animal.ID);
	printf("%d\n", ((legendary_t *)legendary)->cat.animal.ID);
	
	free(animal);
	free(dog);
	free(cat);
	free(legendary);
	
	dog = (dog_t *)objectAlloc(&dog_meta);
	cat = (cat_t *)objectAlloc(&cat_meta);
	cat_color = (cat_t *)objectAlloc(&cat_meta);
	legendary = (legendary_t *)objectAlloc(&legendary_meta);
	animal = (animal_t *)objectAlloc(&animal_meta);
	
    dogCtor(dog);
    catCtor(cat);
    catStringCtor(cat_color, "white");
    legendaryCtor(legendary);
	animalCtor(animal);
	
 	array[0] = (animal_t *)dog;
	array[1] = (animal_t *)cat;
	array[2] = (animal_t *)cat_color;
	array[3] = (animal_t *)legendary;
	array[4] = (animal_t *)animal;
	
	for (i = 0; i < 5; ++i)
	{
		(*array[i]->obj.metadata->class_Vtable)[SAY_HELLO](array[i]);
		printf("%d\n", ((get_num_masters_t)
			((*array[i]->obj.metadata->class_Vtable)[NUM_MASTERS]))(array[i]));
	}
	
	for (i = 0; i < 5; ++i)
	{
		java2cFoo(array[i]);
	}
	
	/* GC */
	for (i = 0; i < 5; ++i)
	{
		(*array[i]->obj.metadata->class_Vtable)[FINALIZE](array[i]);
	}
	
    return 0;
}
