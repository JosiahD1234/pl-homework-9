#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

int main(int argc, char *argv[]) {
    const int count = atoi(argv[1]);

    initVM();

    Table table;
    initTable(&table);

    ObjString** keys = malloc(sizeof(ObjString*) * count);

    if (keys == NULL) {
        fprintf(stderr, "Could not allocate keys.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        char name[32];
        snprintf(name, sizeof(name), "key-%d", i);

        keys[i] = copyString(name, (int)strlen(name));
    }

    for (int i = 0; i < count; i++) {
        tableSet(&table, keys[i], NUMBER_VAL(i));
    }

    for (int i = 0; i < count; i++) {
        Value value;

        if (!tableGet(&table, keys[i], &value)) {
        printf("Lookup failed for key %d\n", i);
        }
    }

    free(keys);
    freeTable(&table);
    freeVM();

    return 0;
}