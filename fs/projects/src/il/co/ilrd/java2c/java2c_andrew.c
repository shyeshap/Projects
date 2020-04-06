#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /*strcmp*/

/*global var*/
/******************************************************************************/
int animal_counter = 0;
char global_buffer[50];
/******************************************************************************/
enum{EQUALS, 
	 FINALIZE, 
	 GETCLASS, 
	 TOSTRING, 

	 GETNUMMASTERS,
	 SAYHELLO};

#define TRUE (1)
#define FALSE (0)

typedef void (*vFucn_t)(void*);
typedef char* (*to_string)(void*);
typedef int (*to_get_mastesrs)(void*);
typedef struct Class class_t;

struct Class{
	char *name;
	size_t size;
	class_t *super;
	vFucn_t (*vFucn_table)[];
};

typedef struct Obj{
	class_t* metadata;
}obj_t;

typedef struct Animal{
	obj_t Obj;
	int num_legs;
	int num_masters;
	int ID;
}animal_t;

typedef struct Dog{
	animal_t Animal;
	int num_legs;
}dog_t;

typedef struct Cat{
	animal_t Animal;
	int num_masters;
	char* colors;
}cat_t;

typedef struct LegendaryAnimal{
	cat_t Cat;
}legendaryAnimal_t;

/******************************************************************************/
/******************************************************************************/
static void animalStaticBlock()
{
	static int animal_static_block_flag = 0;

	if(0 == animal_static_block_flag)
	{
		++animal_static_block_flag;
		printf("Static block Animal 1\nStatic block Animal 2\n");
	}
}

static void catStaticBlock(){
	static int flag = 0;
	if(0 == flag)
	{
		++flag;
		puts("Static block Cat");
	}
}

static void dogStaticBlock()
{
	static int flag = 0;

	if(0 == flag)
	{	
		++flag;
		printf("Static block Dog\n");
	}
}

static void legendaryStaticBlock(){
	static int flag = 0;
	if(0 == flag)
	{
		++flag;
		puts("Static block Legendary Animal");
	}
}
/******************************************************************************/
void showCounter()
{
	animalStaticBlock();
	
	printf("%d\n", animal_counter);
}

obj_t* ObjectAlloc(class_t *class){

    obj_t *object = (obj_t*)calloc(class->size,1);
    object->metadata = class;
	
	return object;
}
/******************************************************************************/
void foo(obj_t *animal)
{
	printf("%s\n", 
	((to_string)((*((obj_t*)animal)->metadata->vFucn_table)[TOSTRING]))(animal));
}
/******************************************************************************/
int objectEquals(obj_t* this, obj_t* other)
{
	
}

void objectFinalize(obj_t* this)
{
	free(this);
}

class_t *objectGetClass(obj_t* this)
{
	return (this)->metadata;
}

char *objectToString(obj_t *this)
{
	memset(global_buffer, ' ', 50);
	sprintf(global_buffer,"il.co.ilrd.java2c.%s@%p", this->metadata->name, (void*)this);

	return global_buffer;
}

vFucn_t objectVTable[] = {(vFucn_t)&objectEquals,
		 				  (vFucn_t)&objectFinalize,
		 				  (vFucn_t)&objectGetClass,
						  (vFucn_t)&objectToString};
/******************************************************************************/
/*animal funcs*/
int animalGetNumMasters(animal_t* this){
	return this->num_masters;
}

void animalFinalize(animal_t* this){
	printf("finalize Animal with ID: %d\n", ((animal_t*)this)->ID);
	objectFinalize((obj_t*)this);
}

void animalSayHello(animal_t* this){
	puts("Animal Hello!");
	printf("I have %d legs\n", this->num_legs);
}

char *animalToString(animal_t* this){
	
	sprintf(global_buffer,"Animal with ID: %d", ((animal_t*)this)->ID);
	
	return global_buffer;
}	

void animalCtor(animal_t* this)
{
	animalStaticBlock();
	printf("Instance initialization block Animal\n");
	++animal_counter;
	this->ID = animal_counter;
	this->num_legs = 5;
	printf("Animal Ctor\n");
	(*((obj_t*)this)->metadata->vFucn_table)[SAYHELLO](this);
	showCounter();
	printf("%s\n", 
	((to_string)((*((obj_t*)this)->metadata->vFucn_table)[TOSTRING]))(this));
	printf("%s\n", objectToString((obj_t*)this));
	this->num_masters = 1;
}

void animalCtorInt(animal_t* this, int num)
{
	animalStaticBlock();
	printf("Instance initialization block Animal\n");

	printf("Animal Ctor int\n");
	++animal_counter;
	this->ID = animal_counter;
	this->num_legs = 5;
	this->num_masters = num;
}

vFucn_t AnimalVTable[] = {(vFucn_t)&objectEquals,
		 				  (vFucn_t)&animalFinalize,
		 				  (vFucn_t)&objectGetClass,
						  (vFucn_t)&animalToString,

						  (vFucn_t)&animalGetNumMasters,
						  (vFucn_t)&animalSayHello};
/******************************************************************************/
/*dog funcs*/
void dogSayHello(dog_t *this){
	printf("Dog Hello!\n");
	printf("Ihave %d legs\n", this->num_legs);
}

void dogFinalize(dog_t *this){
	printf("finalize Dog with ID: %d\n", ((animal_t*)this)->ID);
	animalFinalize((animal_t*)this);
}

char *dogToString(dog_t *this){
	sprintf(global_buffer, "Dog with ID: %d", ((animal_t*)this)->ID);

	return global_buffer;
}

void dogCtor(dog_t *this)
{	
	dogStaticBlock();
	((dog_t*)this)->num_legs = 4;
	animalCtorInt((animal_t *)this, 2);
	puts("Instance initialization block Dog");
	puts("Dog Ctor");
}

vFucn_t DogVTable[] = {   (vFucn_t)&objectEquals,
		 				  (vFucn_t)&dogFinalize,
		 				  (vFucn_t)&objectGetClass,
						  (vFucn_t)&dogToString,

						  (vFucn_t)&animalGetNumMasters,
						  (vFucn_t)&dogSayHello};
/******************************************************************************/
/*cat funcs*/
void catFinalize(cat_t *this){
	printf("finalize Cat with ID: %d\n", ((animal_t*)this)->ID);
	animalFinalize((animal_t*)this);
}

char *catToString(cat_t *this){

	memset(global_buffer,' ', 50);
	sprintf(global_buffer,"Cat with ID: %d", ((animal_t*)this)->ID);

	return global_buffer;
}	

void catCtor(cat_t *this)
{
	catStaticBlock();
	animalCtor((animal_t*)this);
	((cat_t*)this)->colors = "black";
	((cat_t*)this)->num_masters = 2;
	printf("Cat Ctor with color: %s\n", ((cat_t*)this)->colors);
	puts("Cat Ctor");
}

void catCtorColor(cat_t *this, char* colors)
{
	catStaticBlock();
	animalCtor((animal_t*)this);
	this->colors = colors;
	this->num_masters = 5;
	printf("Cat Ctor with color: %s\n", (this)->colors);
}

vFucn_t CatVTable[] = {	  (vFucn_t)&objectEquals,
		 				  (vFucn_t)&catFinalize,
		 				  (vFucn_t)&objectGetClass,
						  (vFucn_t)&catToString,

						  (vFucn_t)&animalGetNumMasters,
						  (vFucn_t)&animalSayHello};
/******************************************************************************/
/*legendary funcs*/
void legendarySayHello(legendaryAnimal_t *this)
{
	(void)this;
	puts("Legendary Hello!");
}

void legendaryFinalize(legendaryAnimal_t *this)
{
	printf("finalize LegendaryAnimal with ID: %d\n", ((animal_t*)this)->ID);
	catFinalize((cat_t*)this);
}

char* legendaryToString(legendaryAnimal_t *this)
{
	memset(global_buffer,' ', 50);
	sprintf(global_buffer,"LegendaryAnimal with ID: %d", ((animal_t*)this)->ID);
	
	return global_buffer;
}		

void legendaryAnimalCtor(legendaryAnimal_t *this)
{
	legendaryStaticBlock();

	catCtor((cat_t*)this);
	printf("Legendary Ctor\n");
}

vFucn_t LegendaryAnimalVTable[] = { (vFucn_t)&objectEquals,
				 				    (vFucn_t)&legendaryFinalize,
				 				    (vFucn_t)&objectGetClass,
								    (vFucn_t)&legendaryToString,

								    (vFucn_t)&animalGetNumMasters,
  								    (vFucn_t)&legendarySayHello};
/******************************************************************************/
class_t object_meta = {"Object", sizeof(obj_t), NULL, &objectVTable};
class_t animal_meta = {"Animal", sizeof(animal_t), &object_meta, &AnimalVTable};
class_t dog_meta = {"Dog", sizeof(dog_t), &animal_meta, &DogVTable};
class_t cat_meta = {"Cat", sizeof(cat_t), &animal_meta, &CatVTable};
class_t LegendaryAnimal_meta = {"LegendaryAnimal", sizeof(legendaryAnimal_t),
							    &cat_meta, &LegendaryAnimalVTable};
/******************************************************************************/
/******************************************************************************/

int main()
{
	int i = 0;
	obj_t* array[5];
	dog_t* dog = NULL;
	cat_t* cat = NULL;
	legendaryAnimal_t* la = NULL;


	obj_t *obj = ObjectAlloc(&object_meta);
	animal_t *animal = (animal_t *)ObjectAlloc(&animal_meta);
	animalCtor(animal);
	dog = (dog_t *)ObjectAlloc(&dog_meta);
	dogCtor(dog);
	cat = (cat_t*)ObjectAlloc(&cat_meta);
	catCtor(cat);
	la = (legendaryAnimal_t*)ObjectAlloc(&LegendaryAnimal_meta);
	legendaryAnimalCtor(la);
	showCounter();
	printf("%d\n", (animal)->ID);
	printf("%d\n", ((animal_t*)dog)->ID);
	printf("%d\n", ((animal_t*)cat)->ID);
	printf("%d\n", ((animal_t*)la)->ID);

	array[0] = ObjectAlloc(&dog_meta);
	dogCtor((dog_t*)array[0]);
	array[1] = ObjectAlloc(&cat_meta);
	catCtor((cat_t*)array[1]);
	array[2] = ObjectAlloc(&cat_meta);
	catCtorColor((cat_t*)array[2], "white");
	array[3] = ObjectAlloc(&LegendaryAnimal_meta); 
	legendaryAnimalCtor((legendaryAnimal_t*)array[3]);
	array[4] = ObjectAlloc(&animal_meta);
	animalCtor((animal_t*)array[4]);

	for(i = 0; i < 5; ++i)
	{
		(*(array[i])->metadata->vFucn_table)[SAYHELLO](array[i]);

		printf("%d\n",
		((to_get_mastesrs)((*(array[i])->metadata->vFucn_table)[GETNUMMASTERS]))(array[i]));
	}

	for(i = 0; i < 5; ++i)
	{
		foo(array[i]);
	}
	
	((*(obj)->metadata->vFucn_table)[FINALIZE])(obj);
	((*((obj_t*)animal)->metadata->vFucn_table)[FINALIZE])(animal);
	((*((obj_t*)dog)->metadata->vFucn_table)[FINALIZE])(dog);
	((*((obj_t*)cat)->metadata->vFucn_table)[FINALIZE])(cat);
	((*((obj_t*)la)->metadata->vFucn_table)[FINALIZE])(la);

	for(i = 0; i < 5; ++i)
	{
		((*(array[i])->metadata->vFucn_table)[FINALIZE])(array[i]);
	}

	return 0;
	
}
