#include <iostream>;
#include <fstream>;
#include <string>;
#include <chrono>;

typedef std :: chrono :: time_point<std :: chrono :: high_resolution_clock> timestamp;

void printMenu ();
void load ( struct Array *&, struct LinkedList *&, int );

int * createWithPredefinedSize ( struct Array * );
int * createWithUndefinedSize ( struct Array * );
int * createFromFile ( struct Array * );

int * deleteElement (struct Array * , int );
int * deleteElementByValue ( struct Array * , int );
int * addElementToArray ( struct Array *, int );
int getElement ( int*, int );

int * doubleUpArray ( struct Array * );
int * doubleUpArray ( int *, int );
int * shiftArray ( int * , int , int );
int * shrinkArray ( int * , int );
void printArray ( struct Array * );

struct LinkedList * createList ();
void populateListPredefined ( LinkedList *& );
void populateListUndefined ( LinkedList *& );
void populateListFromFile ( LinkedList *& );

int push ( struct LinkedList *&, int );
int getAt ( struct LinkedList *& , int );
int removeAt ( struct LinkedList *&, int );
int removeByValue ( struct LinkedList *&, int );
int getNodeWithValue ( struct LinkedList *&, int );

struct Node * getByValue ( struct LinkedList *&, int );
struct Node * getNode ( struct LinkedList *&, int );
void traverseList ( struct LinkedList *& );

void printTime ( timestamp, timestamp, std :: string );

typedef struct Node {
    int value;
    struct Node * next;
    struct Node * prev;
} Node;

struct Array {
    int * data;
    int size;
    int length;
};

struct LinkedList {
    int length;
    bool isEmpty;
    struct Node * head;
    struct Node * tail;
};


int main() {

    int menuCase;
    struct Array * arr = new Array();
    struct LinkedList* list;

    while (true) {

        printMenu();

        std :: cin >> menuCase;

        std :: cout << "\n";

        switch ( menuCase ) {
        case 15:
            delete[] arr;
            return 0;
            break;
        default:
            load(arr, list, menuCase);
            break;
        }

    }

}

void printMenu () {

    std :: cout << "===Array===\n"
        << "1 - Create array automaticly\n"
        << "2 - Create array from input\n"
        << "3 - Create array from file\n"
        << "4 - Add element to array\n"
        << "5 - Delete element from array\n"
        << "6 - Get element from array\n\n"
        << "===Double Linked List===\n"
        << "7 - Create double linked list automaticly\n"
        << "8 - Create double linked list from input\n"
        << "9 - Create double linked list from file\n"
        << "10 - Add element to list\n"
        << "11 - Delete element from list\n"
        << "12 - Get element from list\n"
        << "13 - Exit\n"
        << "Select option: ";
}

void load ( struct Array *& arr, struct LinkedList *& list, int menuCase ) {
    
    switch ( menuCase ) {
        
        case 1: {
            std :: cout << "Enter array size: ";
            std :: cin >> arr->size;
            arr->length = arr->size - 1;
            arr->data = createWithPredefinedSize(arr);
            std :: cout << "Array was created: ";
            printArray(arr);
            break;
        } case 2: {
            std :: cout << "Enter elements of array: \n";
            arr->data = createWithUndefinedSize(arr);
            std::cout << "Array was created: ";
            printArray(arr);
            break;
        } case 3: {
            arr->data = createFromFile(arr);
            std :: cout << "Array was created: ";
            printArray(arr);
            break;
        } case 4: {
            int newEl;
            std :: cout << "Enter element to add to array: ";
            std :: cin >> newEl;
            arr->data = addElementToArray(arr, newEl);
            printArray(arr);
            break;
        } case 5: {
            int toDelete, type;
            std :: cout << "Select deletion type: 1 - by index; 2 - by value\n";
            std :: cin >> type;
            switch ( type ) {
                case 1:
                    std :: cout << "Enter index to delete: ";
                    std :: cin >> toDelete;
                    arr->data = deleteElement(arr, toDelete);
                    break;
                case 2:
                    std :: cout << "Enter value to delete: ";
                    std :: cin >> toDelete;
                    arr->data = deleteElementByValue(arr, toDelete);
                    break;
            }
            printArray(arr);
            break;
        } case 6: {
            int index;
            std :: cout << "Enter index to get: ";
            std :: cin >> index;
            std :: cout << "Index value is: " << getElement(arr->data, index) << "\n";
            break;
        } case 7: {
            list = createList();
            std :: cout << "Enter list size: ";
            std :: cin >> list->length;
            populateListPredefined(list);
            std :: cout << "List was created: \n";
            traverseList(list);
            break;
        } case 8: {
            list = createList();
            std :: cout << "Enter elements of list: \n";
            populateListUndefined(list);
            std :: cout << "List was created: \n";
            traverseList(list);
            break;
        } case 9: {
            list = createList();
            populateListFromFile(list);
            std :: cout << "List was created: \n";
            traverseList(list);
            break;
        } case 10: {
            int newEl;
            std :: cout << "Enter element to add to list: ";
            std :: cin >> newEl;
            timestamp startTime, endTime;
            startTime = std :: chrono :: high_resolution_clock :: now();
            push(list, newEl);
            endTime = std :: chrono :: high_resolution_clock :: now();
            printTime(startTime, endTime, "Element addition ");
            traverseList(list);
            break;
        } case 11: {
            int toDelete, type;
            timestamp startTime, endTime;
            startTime = std :: chrono :: high_resolution_clock :: now();
            std :: cout << "Select deletion type: 1 - by index; 2 - by value\n";
            std :: cin >> type;
            switch ( type ) {
                case 1: 
                    std :: cout << "Enter index to delete: ";
                    std :: cin >> toDelete;
                    removeAt(list, toDelete);
                    endTime = std :: chrono :: high_resolution_clock :: now();
                    printTime(startTime, endTime, "Element deletion ");
                    break;
                case 2:
                    std :: cout << "Enter value to delete: ";
                    std :: cin >> toDelete;
                    removeByValue(list, toDelete);
                    endTime = std :: chrono :: high_resolution_clock :: now();
                    printTime(startTime, endTime, "Element deletion ");
                    break;
            }
            traverseList(list);
            break;
        } case 12 : {
            int index;
            std :: cout << "Enter index to get: ";
            std :: cin >> index;

            if ( list->isEmpty ) {
                std :: cout << "List is empty\n";
            } else if (index > list->length) {
                std :: cout << "Index is larger then list length\n";
            } else {
                timestamp startTime, endTime;
                startTime = std :: chrono :: high_resolution_clock :: now();
                std :: cout << "Index value is: " << getAt(list, index) << "\n";
                endTime = std :: chrono :: high_resolution_clock :: now();
                printTime(startTime, endTime, "Element retrieving ");
            }
            break;
        }

    }

}

int * createWithPredefinedSize ( struct Array * arr ) {
        
    int * newArr = new int[arr->size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i < arr->size; i++ ) {
        newArr[i] = std :: rand() % 100;
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array creation ");

    return newArr;

}

int * createWithUndefinedSize ( struct Array * arr ) {
    
    int size = 2;
    int * newArr = new int[size];
    int num, index = 0;
    bool end = false;

    arr->length = size - 1;
    arr->size = size;

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    while ( !end ) {

        std :: cout << "Enter " << index << " element ( or -1 to end ): ";
    
        std :: cin >> num;

        if ( num == -1 ) {
            end = true;
            break;
        } else if ( index < size ) {
            newArr[index] = num;
            index++;
        } else {
            index = size;
            int * temp = newArr;
            newArr = doubleUpArray(temp, size);
            newArr[index] = num;
            size = size * 2;
            index++;
        }
       
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array creation ");

    arr->length = index - 1;

    return newArr;

}
  
int * createFromFile ( struct Array * arr ) {

    std :: ifstream file;
    int index = 0, size = 2;
    int * newArr = new int[size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    file.open("array.txt");

    if ( file.is_open() ) {
        
        std :: string line;

        while ( std :: getline(file, line) ) {

            int num = std :: stoi(line);
            
            if (index < size) {
                newArr[index] = num;
                index++;
            } else {
                index = size;
                int* temp = newArr;
                newArr = doubleUpArray(temp, size);
                newArr[index] = num;
                size = size * 2;
                index++;
            }

        }
    
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array creation ");

    arr->length = index - 1;

    return newArr;

}

int * addElementToArray ( struct Array * arr, int el ) {

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    if ( arr->length < arr->size ) {
        arr->length++;
        arr->data[arr->length] = el;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Element addition ");

        return arr->data;
    } else {
        int * newArr = doubleUpArray(arr);
        arr->length++;
        newArr[arr->length] = el;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Element addition ");

        return newArr;
    }

}

int * deleteElement ( struct Array * arr, int index ) {
    
    if ( arr->length == -1 ) {
        std :: cout << "Array is empty\n";
        return arr->data;
    }

    if ( index == arr->length ) {
        arr->length--;
        arr->size = arr->length;
        return shrinkArray(arr->data, arr->length);
    } else {
        arr->length--;
        arr->size = arr->length;
        return shiftArray(arr->data, arr->length, index);
    }

}

int * deleteElementByValue ( struct Array * arr, int value ) {
    
    int index;

    for (int i = 0; i < arr->length; i++) {
        if ( arr->data[i] == value ) {
            return deleteElement(arr, i);
        }
    }

    std :: cout << "Element was not found\n";

    return arr->data;

}

int getElement ( int * arr, int index ) {

    std :: cout << "Element was retrived by index in 0 ms";

    return arr[index];

}

//Array helpers

int * doubleUpArray ( struct Array * arr ) {

    int newSize = arr->size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= arr->length; i++ ) {
        newArr[i] = arr->data[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Dynamic array doubling ");
    
    arr->size = newSize;

    return newArr;

}

int * doubleUpArray ( int * arr, int size ) {

    int newSize = size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= size; i++ ) {
        newArr[i] = arr[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Dynamic array doubling ");

    return newArr;

}

int * shrinkArray ( int * arr, int newSize ) {
    
    int * newArr = new int[newSize + 1];

    for ( int i = 0; i < newSize + 1; i++ ) {
        newArr[i] = arr[i];
    }

    return newArr;

}

int * shiftArray ( int * arr, int size, int startIndex ) {
    
    int * newArr = new int[size];

    for ( int i = 0; i < startIndex; i++ ) {
        newArr[i] = arr[i];
    }

    for ( int i = startIndex; i < size + 1; i++ ) {
        newArr[i] = arr[i + 1];
    }
    
    return newArr;

}

void printArray ( struct Array * arr ) {
    
    for ( int i = 0; i <= arr->length; i++ ) {
        std :: cout << arr->data[i] << " ";
    }

    std :: cout << "\n\n";

}

LinkedList * createList () {

    struct LinkedList * list = new LinkedList();
    list->isEmpty = true;
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;

}

void populateListPredefined ( LinkedList *& list ) {

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i < list->length; i++ ) {
        push(list, std::rand() % 100);
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "List creation ");

}

void populateListUndefined ( LinkedList *& list ) {
    
    int num, index = 0;
    bool end = false;

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    while ( !end ) {

        std :: cout << "Enter " << index << " element ( or -1 to end ): ";
    
        std :: cin >> num;

        if ( num == -1 ) {
            end = true;
            break;
        } else {
            index++;
            push(list, num);
        }
       
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "List creation ");

}

void populateListFromFile ( LinkedList *& list ) {
    
    std :: ifstream file;

    file.open("array.txt");

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    if ( file.is_open() ) {
        
        std :: string line;

        while ( std :: getline(file, line) ) {

            int num = std :: stoi(line);
            
            push(list, num);

        }
    
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "List creation ");

}

int push ( LinkedList *& list, int value ) {
    
    struct Node * newNode = new Node();
    newNode->value = value;

    if ( list->isEmpty ) {
        newNode->prev = NULL;
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->isEmpty = false;
        return 0;
    }

    newNode->prev = NULL;
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;

    return 0;

}

int removeAt ( LinkedList *& list, int index ) {

    if ( list->isEmpty ) {
        std :: cout << "List is empty\n";
        return 0;
    }

    struct Node * node = getNode(list, index);

    if ( index == 0 ) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    list->length--;

    if ( list->length == 0 ) {
        list->isEmpty = true;
    }

    return node->value;

}

int getAt ( LinkedList *& list, int index ) {

    if ( list->isEmpty ) {
        std :: cout << "List is empty\n";
        return 0;
    }

    return getNode(list, index)->value;

}

Node * getByValue ( LinkedList *& list, int value ) {
    
    if ( list->isEmpty ) {
        std :: cout << "List is empty\n";
        return 0;
    }

    int nodeIndex = getNodeWithValue(list, value);

    if ( nodeIndex != -1 ) {
        return getNode(list, nodeIndex);
    } else {
        std :: cout << "There is no such node";
        return 0;
    }

}

int removeByValue ( LinkedList *& list, int value ) {
    
    if ( list->isEmpty ) {
        std :: cout << "List is empty\n";
        return 0;
    }

    int nodeIndex = getNodeWithValue(list, value);
    struct Node * node = getNode(list, nodeIndex);

    if ( node->prev == NULL ) {
        return 0;
    }

    node->prev->next = node->next;

    list->length--;

    return node->value;

}

int getNodeWithValue ( struct LinkedList *& list, int value ) {
    
    struct Node * current = list->head;
    int index = 0;

    while ( current->next ) {
        
        if ( current->value == value ) {
            return index;
        }

        index++;
        current = current->next;
        
    }

    return -1;

}

//List helpers

Node * getNode ( LinkedList *& list, int index ) {
    
    int counter;
    struct Node * current;

        counter = 0;
        current = list->head;

        while ( counter < index ) {
            current = current->next;
            counter++;
        }

   
    /*else {

        counter = list->length;
        current = list->tail;
        
        while ( counter > index ) {
            current = current->prev;
            counter--;
        }

    }*/

    return current;

}

void traverseList ( struct LinkedList *& list ) {
    
    struct Node * current = list->head;

    while ( current ) {
        std :: cout << current->value << " ";
        current = current->next;
    }

    std :: cout << "\n";

}

void printTime ( timestamp startTime, timestamp endTime, std :: string type ) {

     std :: cout << type << "ended in: "
        << std :: chrono :: duration_cast <std :: chrono :: microseconds> (endTime - startTime).count()
        << " microseconds\n";

}