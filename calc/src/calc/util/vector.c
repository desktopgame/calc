#include "vector.h"
#include <assert.h>

#define SLOT_SIZE sizeof(void*)
/*
vector * vector_new() {
        vector* ret = (vector*)MEM_MALLOC(sizeof(vector));
        ret->length = 0;
        ret->capacity = 16;
        ret->memory = (vector_item*)MEM_MALLOC(SLOT_SIZE * 16);
        return ret;
}
*/

vector* vector_malloc(const char* filename, int lineno) {
        vector* ret = (vector*)malloc(sizeof(vector));
        ret->length = 0;
        ret->capacity = 16;
        ret->memory = (vector_item*)malloc(SLOT_SIZE * 16);
        return ret;
}

void vector_push(vector* self, vector_item item) {
        assert(self != NULL);
        if (self->length >= self->capacity) {
                vector_reserve(self);
                self->memory[self->length] = item;
        } else {
                self->memory[self->length] = item;
        }
        self->length++;
}

vector_item vector_top(vector* self) {
        assert(self != NULL);
        //	return self->memory[self->length];
        return *(self->memory + (self->length - 1));
}

vector_item vector_pop(vector* self) {
        assert(self != NULL);
        assert(self->length > 0);
        vector_item ret = self->memory[self->length - 1];
        //二重に開放しないように
        self->memory[self->length - 1] = NULL;
        self->length--;
        return ret;
}

void vector_insert(vector* self, int index, vector_item item) {
        assert(index >= 0 && index < (self->length + 1));
        if (self->capacity < (self->length + 1)) {
                vector_reserve(self);
        }
        vector_item t = self->memory[index];
        for (int i = index; i < self->length; i++) {
                vector_item b = self->memory[i + 1];
                self->memory[i + 1] = t;
                t = b;
        }
        self->memory[index] = item;
        self->length++;
}

vector_item vector_remove(vector* self, int index) {
        assert(index >= 0 && index < self->length);
        vector_item ret = self->memory[index];
        for (int i = index + 1; i < self->length; i++) {
                self->memory[i - 1] = self->memory[i];
        }
        self->length--;
        return ret;
}

int vector_reserve(vector* self) {
        assert(self->capacity > 0);
        int newCapacitySize = self->capacity + (self->capacity / 2);
        vector_item* temp =
            (vector_item*)realloc(self->memory, SLOT_SIZE * newCapacitySize);
        assert(temp != NULL);
        self->memory = temp;
        self->capacity = newCapacitySize;
        return newCapacitySize;
}

void vector_assign(vector* self, int index, vector_item item) {
        assert(index >= 0);
        //伸ばす必要がない
        if (index < self->length) {
                self->memory[index] = item;
        } else {
                while (self->length <= index) {
                        vector_push(self, NULL);
                }
                vector_assign(self, index, item);
        }
}

vector_item vector_at(vector* self, int index) {
        assert(index >= 0 && index < self->length);
        return self->memory[index];
        //	return *(self->memory + index);
}

bool vector_empty(vector* self) { return self->length == 0; }

int vector_find(vector* self, vector_item item) {
        int pos = -1;
        for (int i = 0; i < self->length; i++) {
                vector_item e = vector_at(self, i);
                if (e == item) {
                        pos = i;
                        break;
                }
        }
        return pos;
}

bool vector_contains(vector* self, vector_item item) {
        return vector_find(self, item);
}

void vector_clear(vector* self) {
        while (self->length > 0) {
                vector_pop(self);
        }
}

void vector_delete(vector* self, vector_element_deleter deleter) {
        if (self == NULL) {
                return;
        }
        for (int i = 0; i < self->length; i++) {
                vector_item e = self->memory[i];
                self->memory[i] = NULL;
                deleter(e);
        }
        free(self->memory);
        free(self);
}

void vector_deleter_free(vector_item item) { free(item); }

void vector_deleter_null(vector_item item) {}

#undef SLOT_SIZE