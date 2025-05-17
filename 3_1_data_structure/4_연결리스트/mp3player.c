#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char title[100];
    struct Node *prev_node;
    struct Node *next_node;
} Node;

typedef struct PlayList {
    struct Node *head;
    struct Node *tail;
    struct Node *current;
    int size;
} PlayList;

PlayList *create_playlist() {
    PlayList *pl = (PlayList *)malloc(sizeof(PlayList));
    pl->head = pl->tail = pl->current = NULL;
    pl->size = 0;
    return pl;
}

void add_song(PlayList *pl, char *title) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->title, title);
    new_node->next_node = NULL;

    if (!pl->head) {
        pl->head = new_node;
        pl->current = new_node;
    } else {
        pl->tail->next_node = new_node;
        new_node->prev_node = pl->tail;
    }
    pl->tail = new_node;
    pl->size++;
}

void move_next(PlayList *pl) {
    if (pl->current && pl->current->next_node)
        pl->current = pl->current->next_node;
};
void move_prev(PlayList *pl) {
    if (pl->current && pl->current->prev_node)
        pl->current = pl->current->prev_node;
};

void print_playlist(PlayList *pl) {
    printf("PlayList(%d) [\n", pl->size);
    Node *cur = pl->head;
    while (cur) {
        if (cur == pl->current)
            printf(" * %s,\n", cur->title); // 실행중인거 읽음
        else
            printf("   %s,\n", cur->title); // 실행중아닌거 읽음
        cur = cur->next_node;
    }
    printf("]\n");
}

int main() {
    PlayList *pl = create_playlist();

    add_song(pl, "Mamamia");
    add_song(pl, "Dancing Queen");
    add_song(pl, "song3");
    add_song(pl, "song4");

    char cmd[10];

    do {
        print_playlist(pl);
        printf("Command (<, >, q): ");

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break;

        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, ">") == 0)
            move_next(pl);
        else if (strcmp(cmd, "<") == 0)
            move_prev(pl);
        else if (strcmp(cmd, "q") == 0)
            break;
        else
            printf("잘못된 명령어.\n");

    } while (1);

    return 0;
}