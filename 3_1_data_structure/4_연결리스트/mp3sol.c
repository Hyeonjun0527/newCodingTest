#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DListNode {
    char title[100];
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

typedef struct {
    DListNode *head, *tail, *current;
    int size;
} PlayList;

PlayList *create_playlist() {
    PlayList *pl = (PlayList *)malloc(sizeof(PlayList));
    pl->head = pl->tail = pl->current = NULL;
    pl->size = 0;
    return pl;
}

void add_song(PlayList *pl, char *title) {
    DListNode *new_node = (DListNode *)malloc(sizeof(DListNode));
    strcpy(new_node->title, title);
    new_node->next = NULL;

    if (!pl->head) {
        pl->head = new_node;
        pl->current = new_node;
    } else {
        new_node->prev = pl->tail;
        pl->tail->next = new_node;
    }
    pl->tail = new_node;
    pl->size++;
}

void move_next(PlayList *pl) {
    if (pl->current && pl->current->next)
        pl->current = pl->current->next;
}

void move_prev(PlayList *pl) {
    if (pl->current && pl->current->prev)
        pl->current = pl->current->prev;
}

void print_playlist(PlayList *pl) {
    printf("PlayList(%d) [\n", pl->size);
    DListNode *cur = pl->head;
    while (cur) {
        if (cur == pl->current)
            printf("  * %s,\n", cur->title);
        else
            printf("    %s,\n", cur->title);
        cur = cur->next;
    }
    printf("]\n");
}

void clear(PlayList *pl) {
    DListNode *cur = pl->head;
    DListNode *temp;

    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp); // 각 노드를 하나씩 삭제
    }

    pl->head = pl->tail = pl->current = NULL;
    pl->size = 0;
}

void free_list(PlayList *pl) {
    clear(pl); // 노드들을 전부 해제
    free(pl);  // 플레이리스트 자체도 해제
}

int main() {
    PlayList *pl = create_playlist();

    add_song(pl, "Mamamia");
    add_song(pl, "Dancing Queen");
    add_song(pl, "Fernando");
    add_song(pl, "Super");

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
            printf("잘못된 명령어입니다. 다시 입력하세요.\n");

    } while (1);

    free_list(pl); // 🎯 메모리 해제 호출
    return 0;
}
