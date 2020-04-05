#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc() */ 

#define UNUSED(x) (void)(x);
#define RED "\x1b[31m"
#define RESET "\x1b[0m" 

typedef void (*vfunc_t)(void *);
typedef char *(*to_string_t)(void *);
typedef int (*get_num_masters_t)(void *);

typedef enum vMetods{
	CLONE,
	EQUALS,
	GET_CLASS,
	HASH_CODE,
	NOTIFY,
	NOTIFY_ALL,
	WAIT,
	TO_STRING,
	FINALIZE,
	NUM_MASTERS,
	SAY_HELLO
} vmethods_t;

/*********************functions declarations******************/
void objectClone		(void *ptr);
void objectEquals		(void *ptr);
void objectFinalize		(void *ptr);
void objectGetClass		(void *ptr);
size_t objectHashCode	(void *ptr);
void objectNotify		(void *ptr);
void objectNotifyAll	(void *ptr);
char *objectToString	(void *ptr);
void objectWait			(void *ptr);
void animalSayHello		(void *ptr);
int animalGetNumMasters	(void *ptr);
char *animalToString	(void *ptr);
void animalFinalize		(void *ptr);
void dogSayHello		(void *ptr);
void dogFinalize		(void *ptr);
char *dogToString		(void *ptr);
void catFinalize		(void *ptr);
char *catToString		(void *ptr);
void catSayHello		(void *ptr);
char *legendaryToString	(void *ptr);
void legendaryFinalize	(void *ptr);
void legenderySayHello	(void *ptr);

/***********************Initializations***********************/

vfunc_t object_Vtable[] = 		{objectClone,
	 		         			objectEquals,
					         	objectGetClass,
		            			(void(*)(void *))objectHashCode,
		            			objectNotify,
		            			objectNotifyAll,
		            			objectWait,
		            			(void(*)(void *))objectToString,
					            objectFinalize,
		            			};

vfunc_t animal_Vtable[] = 		{objectClone,
	 		                	objectEquals,
					         	objectGetClass,
		            			(void(*)(void *))objectHashCode,
		            			objectNotify,
		            			objectNotifyAll,
		            			objectWait,
								(void(*)(void *))animalToString,
								animalFinalize,
								(void(*)(void *))animalGetNumMasters,
								animalSayHello,
								};
							
vfunc_t dog_Vtable[] = 			{objectClone,
		 		                objectEquals,
							    objectGetClass,
				        		(void(*)(void *))objectHashCode,
				        		objectNotify,
				        		objectNotifyAll,
				        		objectWait,
								(void(*)(void *))dogToString,
								dogFinalize,
				        		(void(*)(void *))animalGetNumMasters,
								dogSayHello,
								};
						
vfunc_t cat_Vtable[] = 			{objectClone,
		 		                objectEquals,
							    objectGetClass,
				        		(void(*)(void *))objectHashCode,
				        		objectNotify,
				        		objectNotifyAll,
				        		objectWait,
								(void(*)(void *))catToString,
								catFinalize,
				        		(void(*)(void *))animalGetNumMasters,
								animalSayHello
								};

vfunc_t legendary_Vtable[] = 	{objectClone,
 		                		objectEquals,
			           			objectGetClass,
						    	(void(*)(void *))objectHashCode,
						    	objectNotify,
						    	objectNotifyAll,
						    	objectWait,
						    	(void(*)(void *))legendaryToString,
						    	legendaryFinalize,
						    	(void(*)(void *))animalGetNumMasters,
						    	legenderySayHello,
						    	};
						    	
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

int g_animal_counter = 0;

/*******************metadata initialization**********************/
class_t object_meta = {"Object", sizeof(object_t), NULL, &object_Vtable};
class_t animal_meta = {"Animal", sizeof(animal_t), &object_meta, &animal_Vtable};
class_t dog_meta = {"Dog", sizeof(dog_t), &animal_meta, &dog_Vtable};
class_t cat_meta = {"Cat", sizeof(cat_t), &animal_meta, &cat_Vtable};
class_t legendary_meta = {"LegendaryAnimal", sizeof(legendary_t), &cat_meta, &legendary_Vtable};

/******************Class functions implementation****************/
void animalShowCounter(){
	printf("%d\n", g_animal_counter);
}

void java2cFoo(animal_t *animal)
{
	char *string_result = NULL;
	
	string_result = ((to_string_t)((*animal->obj.metadata->class_Vtable)[TO_STRING]))(animal);
	printf("%s\n", string_result);
	free(string_result);
}

/****************Instance functions implementatin******************/
/* object funcs */
void objectClone		(void *ptr) {UNUSED(ptr);}
void objectEquals		(void *ptr) {UNUSED(ptr);}
void objectGetClass		(void *ptr) {UNUSED(ptr);}
void objectNotify		(void *ptr) {UNUSED(ptr);}
void objectNotifyAll	(void *ptr) {UNUSED(ptr);}
void objectWait			(void *ptr) {UNUSED(ptr);}

size_t objectHashCode(void *object) 
{
	return (size_t)(object);
}

char *objectToString(void *object)
{
	char *string_result = (char *)malloc(100);
	
	sprintf(string_result, "%s@%lu", 
			((object_t *)object)->metadata->name, 
			(size_t)objectHashCode(object));
	
	return string_result;
}

void objectFinalize(void *object) 
{
	free(object);
}

/*************************Animal*****************************/
/* CONSTRUCTOR: for default constructor insert NULL in num_masters */
void animalCtor(object_t *object, int *num_masters)
{
	animal_t *animal = (animal_t *)object;
	static int flag = 0;
	char *string_result = NULL;
	
	if (0 == flag)
	{
		printf("Static block Animal 1\n");
		printf("Static block Animal 2\n");
		++flag;
	}
	
	{
		printf("Instance initialization block Animal\n");
	}
	
	animal->ID = ++g_animal_counter;
	animal->num_legs = 5;
	
	if (num_masters == NULL)
	{
		printf("Animal Ctor\n");
		animal->num_masters = 1;
		(*animal->obj.metadata->class_Vtable)[SAY_HELLO](animal);
		animalShowCounter(NULL);
		string_result = ((to_string_t)
					((*animal->obj.metadata->class_Vtable)[TO_STRING]))(animal);
		printf ("%s\n", string_result);
		free(string_result);
		string_result = objectToString(animal);
		printf("%s\n", string_result);
		free(string_result);
	}
	
	else 
	{
		printf("Animal Ctor int\n");
		animal->num_masters = *num_masters;
	}
}

/* funcs */
void animalSayHello(void *object)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n", ((animal_t *)(object))->num_legs);
}

int animalGetNumMasters(void *object)
{
	return ((animal_t *)object)->num_masters;
}

char *animalToString(void *object)
{
	char *string_result = (char *)malloc(100);
	
	sprintf(string_result, "Animal with ID: %d", 
			((animal_t *)object)->ID);
	
	return string_result;
}

void animalFinalize(void *object) 
{
	printf(RED "finalize Animal with ID: %d\n" RESET, 
			((animal_t *)object)->ID);
	object_Vtable[FINALIZE](object);
}

/***************************Dog******************************/
/* CONSTRUCTOR */
void dogCtor(object_t *object)
{
	dog_t *dog = (dog_t *)object;
	int i = 2;
	static int flag = 0;
	
	if(0 == flag)
	{
		printf("Static block Dog\n");
		++flag;
	}

	animalCtor(object, &i);
	
	{
		printf("Instance initialization block Dog\n");
	}

	printf("Dog Ctor\n");
	
	dog->num_legs = 4;
}

/* funcs */
void dogSayHello(void *object)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", ((dog_t *)object)->num_legs);
}

char *dogToString(void *object)
{
	char *string_result = (char *)malloc(100);
	
	sprintf(string_result, "Dog with ID: %d", 
			((dog_t *)object)->animal.ID);
	
	return string_result;
}

void dogFinalize(void *object) 
{
	printf(RED "finalize Dog with ID: %d\n" RESET,
			((animal_t *)object)->ID);
	object_Vtable[FINALIZE](object);
}

/*************************Cat***************************/
/* CONSTRUCTOR: for default constructor insert NULL in colors */
void catCtor(object_t *object, char *colors)
{
	cat_t *cat = (cat_t *)object;
	static int flag = 0;

	cat->num_masters = 5;
	
	if (0 == flag)
	{
		printf("Static block Cat\n");
		++flag;
	}
	
	if (colors == NULL)
	{
		catCtor(object, "black");
		cat->num_masters = 2;
		printf("Cat Ctor\n");
	}
	
	else
	{
		animalCtor(object, NULL);
		
		cat->colors = colors;
		printf("Cat Ctor with color: %s\n", colors);
	}
}

/* funcs */
char *catToString(void *object)
{
	char *string_result = (char *)malloc(100);
	
	sprintf(string_result, "Cat with ID: %d",
	 		((cat_t *)object)->animal.ID);
	 
	return string_result;
}

void catFinalize(void *object) 
{
	printf(RED "finalize Cat with ID: %d\n" RESET,
			((animal_t *)object)->ID);
	object_Vtable[FINALIZE](object);
}

/*************************LegendaryAnimal**********************8*/
/* CONSTRUCTOR */
void legendaryCtor(object_t *object)
{
	static int flag = 0;

	if (0 == flag)
	{
		printf("Static block Legendary Animal\n");
		++flag;
	}
	
	catCtor(object, NULL);
	
	printf("Legendary Ctor\n");
}

/* funcs */
char *legendaryToString(void *object)
{
	char *string_result = (char *)malloc(100);
	
	sprintf(string_result, "LegendaryAnimal with ID: %d", 
			((animal_t *)object)->ID);
			
	return string_result;
}

void legenderySayHello(void *object)
{
	UNUSED(object);
	
	printf("Legendary Hello!\n");
}

void legendaryFinalize(void *object) 
{
	printf(RED "finalize LegendaryAnimal with ID: %d\n" RESET,
			((animal_t *)object)->ID);
	object_Vtable[FINALIZE](object);
}

/**************************new*********************************/
object_t *objectAlloc(class_t *class)
{
	object_t *obj = (object_t *)malloc(class->size);
	obj->metadata = class;
	
	return obj;
}

/**************************Main***************************/
int main()
{   
    animal_t *array[5] = {0};

    int i = 0;
	
	object_t *cat_color = NULL;
    object_t *animal = objectAlloc(&animal_meta);
	object_t *dog = objectAlloc(&dog_meta);
	object_t *cat = objectAlloc(&cat_meta);
	object_t *legendary = objectAlloc(&legendary_meta);
    
    animalCtor(animal, NULL);
   	dogCtor(dog);
    catCtor(cat, NULL);
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
	
	dog = objectAlloc(&dog_meta);
	cat = objectAlloc(&cat_meta);
	cat_color = objectAlloc(&cat_meta);
	legendary = objectAlloc(&legendary_meta);
	animal = objectAlloc(&animal_meta);
	
    dogCtor(dog);
    catCtor(cat, NULL);
    catCtor(cat_color, "white");
    legendaryCtor(legendary);
	animalCtor(animal, NULL);
	
 	array[0] = (animal_t *)dog;
	array[1] = (animal_t *)cat;
	array[2] = (animal_t *)cat_color;
	array[3] = (animal_t *)legendary;
	array[4] = (animal_t *)animal;
	
	for (i = 0; i < 5; ++i)
	{
		(*array[i]->obj.metadata->class_Vtable)[SAY_HELLO](&array[i]);
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
