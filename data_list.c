#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_DATA_SIZE 64

typedef struct data_list
{
    int dc;
    int data_size;
    uint16_t *bytes;
} data_list;


data_list *dl_create() {
    data_list *dl = malloc(sizeof(data_list));
    dl ->data_size = INITIAL_DATA_SIZE;
    dl->dc = 0;
    dl->bytes = malloc(sizeof(uint16_t) * INITIAL_DATA_SIZE);
    return dl;
}

void dl_resize(data_list *dl, int new_data_size) {
    while((dl->dc + new_data_size) > dl->data_size) {
        dl->data_size *= 2;
        dl->bytes = realloc(dl->bytes,dl->data_size);
    }
}

void dl_append_num(data_list *dl, int16_t num) {
    dl_resize(dl, sizeof(int16_t));
    dl->bytes[dl->dc++] = num;
}

void dl_append_string(data_list *dl, char *s) {
    int len = strlen(s);
    int i;
    dl_resize(dl,len);
    for (i = 0; i < len+1; i++) /* include \0 */
    {
        dl->bytes[dl->dc++] = s[i];
    }
}

uint16_t dl_get_val(data_list *dl, int i) {
    return dl->bytes[i]; 
}

int dl_get_dc(data_list *dl) {
    return dl->dc;
}

void dl_destroy(data_list *dl) {
    free(dl->bytes);
    free(dl);
}

int main(int argc, char const *argv[])
{
    data_list *dl = dl_create();
    char *s = "abcd";

    dl_append_string(dl,s);
    dl_append_num(dl,(int16_t) 6);
    dl_append_num(dl,(int16_t) -9);
    dl_append_num(dl,(int16_t) -100);
    dl_append_num(dl,(int16_t) 31);

    dl_destroy(dl);
    return 0;
}

