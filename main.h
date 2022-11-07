#include <stdio.h>
#include "stdlib.h"
#include <memory.h>

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 10000


typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;


typedef struct sObject {
    struct sObject* next;
    unsigned char marked;
    ObjectType type;

    union {
        /* OBJ_INT */
        int value;

        /* OBJ_PAIR */
        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;
typedef struct {
    /* The total number of currently allocated objects. */
    int numObjects;

    /* The number of objects required to trigger a GC. */
    int maxObjects;

    Object* firstObject;
    Object* stack[STACK_MAX];
    int stackSize;
} VM;
void gc(VM* vm);
struct VM * newVM();
void push(VM* vm, Object* value);
Object* pop(VM* vm);
Object* newObject(VM* vm, ObjectType type);
void mark(Object* object);
void markAll(VM* vm);
void pushInt(VM* vm, int intValue);
Object* pushPair(VM* vm);
void sweep(VM* vm);
void assert(int condition, const char* message);
