#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* malloc() */ 

#define UNUSED(x) (void)(x);
#define RED "\x1b[31m"
#define RESET "\x1b[0m" 
typedef void (*vfunc_t)(void *);

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
void objectHashCode		(void *ptr);
void objectNotify		(void *ptr);
void objectNotifyAll	(void *ptr);
void objectToString		(void *ptr);
void objectWait			(void *ptr);
void animalSayHello		(void *ptr);
void animalGetNumMasters(void *ptr);
void animalToString		(void *ptr);
void animalFinalize		(void *ptr);
void dogSayHello		(void *ptr);
void dogFinalize		(void *ptr);
void dogToString		(void *ptr);
void catFinalize		(void *ptr);
void catToString		(void *ptr);
void catSayHello		(void *ptr);
void legendaryToString	(void *ptr);
void legendaryFinalize	(void *ptr);
void legenderySayHello	(void *ptr);

/***********************Initializations***********************/

vfunc_t object_Vtable[] = 		{objectClone,
	 		         			objectEquals,
					         	objectGetClass,
		            			objectHashCode,
		            			objectNotify,
		            			objectNotifyAll,
		            			objectWait,
		            			objectToString,
					            objectFinalize,
		            			};

vfunc_t animal_Vtable[] = 		{objectClone,
	 		                	objectEquals,
					         	objectGetClass,
		            			objectHashCode,
		            			objectNotify,
		            			objectNotifyAll,
		            			objectWait,
								animalToString,
								animalFinalize,
								animalGetNumMasters,
								animalSayHello,
								};
							
vfunc_t dog_Vtable[] = 			{objectClone,
		 		                objectEquals,
							    objectGetClass,
				        		objectHashCode,
				        		objectNotify,
				        		objectNotifyAll,
				        		objectWait,
								dogToString,
								dogFinalize,
				        		animalGetNumMasters,
								dogSayHello,
								};
						
vfunc_t cat_Vtable[] = 			{objectClone,
		 		                objectEquals,
							    objectGetClass,
				        		objectHashCode,
				        		objectNotify,
				        		objectNotifyAll,
				        		objectWait,
								catToString,
								catFinalize,
				        		animalGetNumMasters,
								animalSayHello
								};

vfunc_t legendary_Vtable[] = 	{objectClone,
 		                		objectEquals,
			           			objectGetClass,
						    	objectHashCode,
						    	objectNotify,
						    	objectNotifyAll,
						    	objectWait,
						    	legendaryToString,
						    	legendaryFinalize,
						    	animalGetNumMasters,
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

typedef struct Wrapper {
	object_t *this;
	int num_masters;
	char *string_result;
	size_t hash_code;
} wrapper_t;

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

void java2cFoo(animal_t *animal, wrapper_t param)
{
	(*animal->obj.metadata->class_Vtable)[TO_STRING](&param);
	printf("%s\n", param.string_result);
	free(param.string_result);
}

void systemGC()
{

}

/****************Instance functions implementatin******************/
void objectClone		(void *ptr) {UNUSED(ptr);}
void objectEquals		(void *ptr) {UNUSED(ptr);}
void objectGetClass		(void *ptr) {UNUSED(ptr);}
void objectNotify		(void *ptr) {UNUSED(ptr);}
void objectNotifyAll	(void *ptr) {UNUSED(ptr);}
void objectWait			(void *ptr) {UNUSED(ptr);}

void objectFinalize(void *wrapper) 
{
	free(((wrapper_t *)wrapper)->this);
}

void animalFinalize(void *wrapper) 
{
	printf(RED "finalize Animal with ID: %d\n" RESET, 
			((animal_t *)((wrapper_t *)wrapper)->this)->ID);
	free(((wrapper_t *)wrapper)->this);
}

void dogFinalize(void *wrapper) 
{
	printf(RED "finalize Dog with ID: %d\n" RESET,
			((animal_t *)((wrapper_t *)wrapper)->this)->ID);
	free(((wrapper_t *)wrapper)->this);
}

void catFinalize(void *wrapper) 
{
	printf(RED "finalize Cat with ID: %d\n" RESET,
			((animal_t *)((wrapper_t *)wrapper)->this)->ID);
	free(((wrapper_t *)wrapper)->this);
}

void legendaryFinalize(void *wrapper) 
{
	printf(RED "finalize LegendaryAnimal with ID: %d\n" RESET,
			((animal_t *)((wrapper_t *)wrapper)->this)->ID);
	free(((wrapper_t *)wrapper)->this);
}

void objectHashCode	(void *wrapper) 
{
	((wrapper_t *)wrapper)->hash_code = (size_t)(((wrapper_t *)wrapper)->this);
}

void objectToString(void *wrapper)
{
	objectHashCode(wrapper);
	sprintf(((wrapper_t *)wrapper)->string_result, "%s@%lu", 
			((object_t *)((wrapper_t *)wrapper)->this)->metadata->name, 
			((wrapper_t *)wrapper)->hash_code);
}

void animalSayHello(void *ptr)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n", ((animal_t *)((wrapper_t *)ptr)->this)->num_legs);
}

void animalGetNumMasters(void *ptr)
{
	((wrapper_t *)ptr)->num_masters = 
							((animal_t *)((wrapper_t *)ptr)->this)->num_masters;
}

void animalToString(void *ptr)
{
	((wrapper_t *)ptr)->string_result = (char *)malloc(100);
	sprintf(((wrapper_t *)ptr)->string_result, 
			"Animal with ID: %d", ((animal_t *)((wrapper_t *)ptr)->this)->ID);
}

void dogSayHello(void *ptr)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", ((dog_t *)((wrapper_t *)ptr)->this)->num_legs);
}

void dogToString(void *ptr)
{
	((wrapper_t *)ptr)->string_result = (char *)malloc(100);
	sprintf(((wrapper_t *)ptr)->string_result, "Dog with ID: %d", 
			((dog_t *)((wrapper_t *)ptr)->this)->animal.ID);
}

void catToString(void *ptr)
{
	((wrapper_t *)ptr)->string_result = (char *)malloc(100);
	sprintf(((wrapper_t *)ptr)->string_result, "Cat with ID: %d",
	 		((cat_t *)((wrapper_t *)ptr)->this)->animal.ID);
}

void legendaryToString(void *ptr)
{
	((wrapper_t *)ptr)->string_result = (char *)malloc(100);
	sprintf(((wrapper_t *)ptr)->string_result, "LegendaryAnimal with ID: %d", 
			((animal_t *)((wrapper_t *)ptr)->this)->ID);

}

void legenderySayHello(void *ptr)
{
	UNUSED(ptr);
	
	printf("Legendary Hello!\n");
}

/**************************new*********************************/
object_t *objectAlloc(class_t *class)
{
	object_t *obj = (object_t *)malloc(class->size);
	obj->metadata = class;
	
	return obj;
}

/**********************constructors****************************/
/* for default constructor insert NULL in num_masters */
void animalCtor(wrapper_t param, int *num_masters)
{
	animal_t *animal = (animal_t *)(param.this);
	static int flag = 0;
	
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
		(*animal->obj.metadata->class_Vtable)[SAY_HELLO](&param);
		animalShowCounter(NULL);
		(*animal->obj.metadata->class_Vtable)[TO_STRING](&param);
		printf("%s\n", param.string_result);
		objectToString(&param);
		printf("%s\n", param.string_result);
		free(param.string_result);
	}
	
	else 
	{
		printf("Animal Ctor int\n");
		animal->num_masters = *num_masters;
	}
}

void dogCtor(wrapper_t param)
{
	dog_t *dog = (dog_t *)(param.this);
	int i = 2;
	static int flag = 0;
	
	if(0 == flag)
	{
		printf("Static block Dog\n");
		++flag;
	}

	animalCtor(param, &i);
	
	{
		printf("Instance initialization block Dog\n");
	}

	printf("Dog Ctor\n");
	
	dog->num_legs = 4;
}

/* for default constructor insert NULL in colors */
void catCtor(wrapper_t param, char *colors)
{
	cat_t *cat = (cat_t *)(param.this);
	static int flag = 0;

	cat->num_masters = 5;
	
	if (0 == flag)
	{
		printf("Static block Cat\n");
		++flag;
	}
	
	if (colors == NULL)
	{
		catCtor(param, "black");
		cat->num_masters = 2;
		printf("Cat Ctor\n");
	}
	
	else
	{
		animalCtor(param, NULL);
		
		cat->colors = colors;
		printf("Cat Ctor with color: %s\n", colors);
	}
}

void legendaryCtor(wrapper_t param)
{
	static int flag = 0;

	if (0 == flag)
	{
		printf("Static block Legendary Animal\n");
		++flag;
	}
	
	catCtor(param, NULL);
	
	printf("Legendary Ctor\n");
}

/**************************Main***************************/
int main()
{   
    animal_t *array[5] = {0};
    wrapper_t param_array[5] = {0};
    int i = 0;
    
    wrapper_t param_animal;
    wrapper_t param_dog;
    wrapper_t param_cat;
    wrapper_t param_legendary;
    wrapper_t param_cat_color;
    
    animal_t *animal;
    dog_t *dog;
    cat_t *cat;
    legendary_t *legendary;
    cat_t *cat_color;
    
    animal = (animal_t *)objectAlloc(&animal_meta);
	dog = (dog_t *)objectAlloc(&dog_meta);
	cat = (cat_t *)objectAlloc(&cat_meta);
	legendary = (legendary_t *)objectAlloc(&legendary_meta);

    param_animal.this = (object_t *)animal;
    param_dog.this = (object_t *)dog;
	param_cat.this = (object_t *)cat;
	param_legendary.this = (object_t *)legendary;
    
    animalCtor(param_animal, NULL);
   	dogCtor(param_dog);
    catCtor(param_cat, NULL);
    legendaryCtor(param_legendary);
   
   	animalShowCounter();
   	
   	printf("%d\n", animal->ID);
	printf("%d\n", dog->animal.ID);
	printf("%d\n", cat->animal.ID);
	printf("%d\n", legendary->cat.animal.ID);
	
	free(animal);
	free(dog);
	free(cat);
	free(legendary);
	
	dog = (dog_t *)objectAlloc(&dog_meta);
	cat = (cat_t *)objectAlloc(&cat_meta);
	cat_color = (cat_t *)objectAlloc(&cat_meta);
	legendary = (legendary_t *)objectAlloc(&legendary_meta);
	animal = (animal_t *)objectAlloc(&animal_meta);
	
	param_dog.this = (object_t *)dog;
	param_cat.this = (object_t *)cat;
	param_cat_color.this = (object_t *)cat_color;
	param_legendary.this = (object_t *)legendary;
	param_animal.this = (object_t *)animal;
	
    dogCtor(param_dog);
    catCtor(param_cat, NULL);
    catCtor(param_cat_color, "white");
    legendaryCtor(param_legendary);
	animalCtor(param_animal, NULL);
	
 	array[0] = (animal_t *)dog;
	array[1] = (animal_t *)cat;
	array[2] = (animal_t *)cat_color;
	array[3] = (animal_t *)legendary;
	array[4] = animal;

	param_array[0] = param_dog;
	param_array[1] = param_cat;
	param_array[2] = param_cat_color;
	param_array[3] = param_legendary;
	param_array[4] = param_animal;
	
	for (i = 0; i < 5; ++i)
	{
		(*array[i]->obj.metadata->class_Vtable)[SAY_HELLO](&param_array[i]);
		(*array[i]->obj.metadata->class_Vtable)[NUM_MASTERS](&param_array[i]);
		printf("%d\n", param_array[i].num_masters);
	}
	
	for (i = 0; i < 5; ++i)
	{
		java2cFoo(array[i], param_array[i]);
	}
	
	for (i = 0; i < 5; ++i)
	{
		(*array[i]->obj.metadata->class_Vtable)[FINALIZE](&param_array[i]);
	}
	
    return 0;
}
