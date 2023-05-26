#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct FriendNode {
    char name[MAX_NAME_LENGTH];
    struct FriendNode* next;
} FriendNode, *friendPointer;

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    friendPointer friends;
} Person, *personPointer;

personPointer createPerson(char* name) {
    personPointer newPerson = (personPointer)malloc(sizeof(Person));
    if (!newPerson) {
        fprintf(stderr, "Memory Allocation error. Program terminates.\n");
        exit(1);
    }
    strcpy(newPerson->name, name);
    newPerson->friends = NULL;
    return newPerson;
}

personPointer findPerson(personPointer* people, int numPeople, char* name) {
    for (int i = 0; i < numPeople; i++) {
        if (strcmp(people[i]->name, name) == 0) {
            return people[i];
        }
    }
    return NULL;
}

void pushFriend(personPointer person, char* name) {
    friendPointer newFriend = (friendPointer)malloc(sizeof(FriendNode));
    if (!newFriend) {
        fprintf(stderr, "Memory Allocation error. Program terminates.\n");
        exit(1);
    }
    strcpy(newFriend->name, name);
    newFriend->next = NULL;

    /*push new friend into the friend list of that person*/
    if (person->friends == NULL) {
        person->friends = newFriend;
        return;
    }
    friendPointer currentFriend = person->friends;
    while (currentFriend->next != NULL) {
        currentFriend = currentFriend->next;
    }
    currentFriend->next = newFriend;
}

void popFriend(personPointer person, char* name) {
    if (person->friends == NULL) {
        return;
    }

    if (strcmp(person->friends->name, name) == 0) {
        friendPointer temp = person->friends;
        person->friends = person->friends->next;
        free(temp);
        return;
    }

    friendPointer prevFriend = person->friends;
    friendPointer currentFriend = person->friends->next;

    while (currentFriend != NULL && strcmp(currentFriend->name, name) != 0) {
        prevFriend = currentFriend;
        currentFriend = currentFriend->next;
    }

    if (currentFriend != NULL) {
        prevFriend->next = currentFriend->next;
        free(currentFriend);
    }
}

void printFriends(personPointer person, FILE* outputFile) {
    friendPointer currentFriend = person->friends;
    if (!currentFriend) {
        fprintf(outputFile, "There is no friend...");
    }
    while (currentFriend != NULL) {
        fprintf(outputFile, "%s ", currentFriend->name);
        currentFriend = currentFriend->next;
    }
    fprintf(outputFile, "\n");
}

int areFriends(personPointer person1, personPointer person2) {
    friendPointer currentFriend = person1->friends;
    while (currentFriend != NULL) {
        if (strcmp(currentFriend->name, person2->name) == 0) {
            return 1;
        }
        currentFriend = currentFriend->next;
    }
    return 0;
}

int main() {
    FILE* input = fopen("input_3.txt", "r");
    FILE* output = fopen("output_3.txt", "w");

    if (input == NULL) {
        fprintf(stderr, "Failed to open input file. Program terminates.\n");
        exit(1);
    }
    if (output == NULL) {
        fprintf(stderr, "Failed to open output file. Program terminates.\n");
        exit(1);
    }

    int numPeople = 0;
    personPointer people[100000], person1, person2, person;
    char command;
    char name1[MAX_NAME_LENGTH];
    char name2[MAX_NAME_LENGTH];

    while (fscanf(input, "%c", &command) == 1) {
        if (command == 'P') {
            fscanf(input, " %s", name1);
            /*Check if there is a same name*/
            if (findPerson(people, numPeople, name1) != NULL) {
                fprintf(output, "A person with the same name already exists.\n");
                continue;
            }
            people[numPeople] = createPerson(name1);
            numPeople++;
        }
        else if (command == 'F') {
            fscanf(input, " %s %s", name1, name2);
            person1 = findPerson(people, numPeople, name1);
            person2 = findPerson(people, numPeople, name2);
            /*Get two people to add their friendship. If there is no such person notice and continue*/
            if (person1 == NULL || person2 == NULL) {
                fprintf(output, "One or both people do not exist.\n");
                continue;
            }
            /*push their friendship onto both friendlists*/
            if (!(areFriends(person1, person2))) {
                pushFriend(person1, name2);
                pushFriend(person2, name1);
            }
        }
        else if (command == 'U') {
            fscanf(input, " %s %s", name1, name2);
            person1 = findPerson(people, numPeople, name1);
            person2 = findPerson(people, numPeople, name2);
            /*if there is no such person to unfriend, program tells explicity.
            When two people are not friend, nothing happens in the popFriend process because they are not friend!*/
            if (person1 == NULL || person2 == NULL) {
                fprintf(output, "One or both people do not exist.\n");
                continue;
            }
            popFriend(person1, name2);
            popFriend(person2, name1);
        }
        else if (command == 'L') {
            fscanf(input, " %s", name1);
            person = findPerson(people, numPeople, name1);
            if (person == NULL) {
                fprintf(output, "Person does not exist.\n");
                continue;
            }
            printFriends(person, output);
        }
        else if (command == 'Q') {
            fscanf(input, " %s %s", name1, name2);
            person1 = findPerson(people, numPeople, name1);
            person2 = findPerson(people, numPeople, name2);
            if (person1 == NULL || person2 == NULL) {
                fprintf(output, "One or both people do not exist.\n");
                continue;
            }
            /*check their friendship and output the result*/
            if (areFriends(person1, person2)) {
                fprintf(output, "Yes\n");
            }
            else {
                fprintf(output, "No\n");
            }
        }
        else if (command == 'X') {
            break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}

