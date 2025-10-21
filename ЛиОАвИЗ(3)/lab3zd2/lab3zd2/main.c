#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    char inf[256];
    struct node* next;
};

struct node* front = NULL, * rear = NULL, * f = NULL;
int queue_size = 0;

void enqueue(void), display_queue(void), dequeue_by_name(char* name);
int is_empty(void);
void dequeue(void);
struct node* peek(void);

char find_el[256];
struct node* find(char* name);
struct node* get_struct(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Oshibka pri raspredelenii pamyati\n");
        exit(1);
    }

    printf("Vvedite nazvanie ob'ekta: \n");
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Zapis' ne byla proizvedena\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p;
}

int is_empty(void)
{
    return (front == NULL);
}

void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct();

    if (p == NULL) return;

    if (is_empty())
    {
        front = p;
        rear = p;
    }
    else
    {
        rear->next = p;
        rear = p;
    }
    queue_size++;
    printf("Element '%s' dobavlen v ochered'\n", p->inf);
}

void dequeue(void)
{
    struct node* temp;

    if (is_empty())
    {
        printf("Ochered' pusta\n");
        return;
    }

    temp = front;
    printf("Element '%s' udalen iz ocheredi\n", temp->inf);

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);
    queue_size--;
}

struct node* peek(void)
{
    if (is_empty())
    {
        printf("Ochered' pusta\n");
        return NULL;
    }

    printf("Pervyy element v ocheredi: %s\n", front->inf);
    return front;
}

void display_queue(void)
{
    struct node* struc = front;
    if (is_empty())
    {
        printf("Ochred' pusta\n");
        return;
    }

    printf("Soderzhimoe ocheredi (ot nachala k kontsu):\n");
    printf("Front -> ");
    while (struc)
    {
        printf("%s", struc->inf);
        if (struc->next != NULL)
            printf(" -> ");
        struc = struc->next;
    }
    printf(" <- Rear\n");
    printf("Razmer ocheredi: %d\n\n", queue_size);
}

struct node* find(char* name)
{
    struct node* struc = front;
    int position = 0;

    if (is_empty())
    {
        printf("Ochered' pusta\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Element '%s' nayden na pozitsii %d\n", name, position + 1);
            position++;
        }
        struc = struc->next;

    }

    

    
}

void dequeue_by_name(char* name)
{
    struct node* struc = front;
    struct node* prev = NULL;
    int flag = 0;

    if (is_empty())
    {
        printf("Ochered' pusta\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        front = struc->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        free(struc);
        queue_size--;
        printf("Element '%s' udalen iz ocheredi\n", name);
        return;
    }

    prev = struc;
    struc = struc->next;

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            prev->next = struc->next;

            if (struc == rear)
            {
                rear = prev;
            }

            free(struc);
            queue_size--;
            printf("Element '%s' udalen iz ocheredi\n", name);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Element ne nayden\n");
    }
}

void clear_queue(void)
{
    while (!is_empty())
    {
        dequeue();
    }
    printf("Ochered' polnost'yu ochishchena\n");
}

int main()
{
    int choice;
    char name[256];

    while (1)
    {
        printf("\n=== OCHERED' ===\n");
        printf("1. Dobavit' element v ochered' (enqueue)\n");
        printf("2. Udalit' element iz ocheredi (dequeue)\n");
        printf("3. Posmotret' pervyy element (peek)\n");
        printf("4. Pokazat' ochered'\n");
        printf("5. Nayti element\n");
        printf("6. Udalit' element po nazvaniyu\n");
        printf("7. Proverit' pustotu ocheredi\n");
        printf("8. Ochitit' ochered'\n");
        printf("0. Vykhod\n");
        printf("Vyberite deystvie: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            peek();
            break;
        case 4:
            display_queue();
            break;
        case 5:
            printf("Vvedite nazvanie dlya poiska: ");
            scanf("%s", name);
            find(name);
            break;
        case 6:
            printf("Vvedite nazvanie dlya udaleniya: ");
            scanf("%s", name);
            dequeue_by_name(name);
            break;
        case 7:
            if (is_empty())
                printf("Ochered' pusta\n");
            else
                printf("V ocheredi est' %d elementov\n", queue_size);
            break;
        case 8:
            clear_queue();
            break;
        case 0:
            clear_queue();
            printf("Vykhod iz programmy\n");
            return 0;
        default:
            printf("Nevernyy vybor\n");
        }
    }
}
