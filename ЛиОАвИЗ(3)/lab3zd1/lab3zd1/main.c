#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];
    int priority;
    struct node* next;
};

struct node* head = NULL, * last = NULL, * f = NULL;
int dlinna = 0;

void spstore(void), review(void), del(char* name);
char find_el[256];
struct node* find(char* name);
struct node* get_struct(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int prior;

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

    printf("Vvedite prioritet ob'ekta (chem bol'she chislo, tem vyshe prioritet): \n");
    scanf("%d", &prior);
    p->priority = prior;

    p->next = NULL;
    return p;
}

void spstore(void)
{
    struct node* p = NULL;
    struct node* current = NULL;
    struct node* prev = NULL;

    p = get_struct();
    if (p == NULL) return;

    if (head == NULL)
    {
        head = p;
        last = p;
        dlinna++;
        return;
    }

    if (p->priority > head->priority)
    {
        p->next = head;
        head = p;
        dlinna++;
        return;
    }

    current = head;
    prev = NULL;

    while (current != NULL && current->priority >= p->priority)
    {
        prev = current;
        current = current->next;
    }

    p->next = current;
    if (prev != NULL)
    {
        prev->next = p;
    }

    if (current == NULL)
    {
        last = p;
    }

    dlinna++;
}

void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Ochered' pusta\n");
        return;
    }

    printf("Soderzhimoe prioritetnoy ocheredi (po ubyvaniyu prioriteta):\n");
    while (struc)
    {
        printf("Imya: %s, Prioritet: %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
    printf("Vsego elementov: %d\n\n", dlinna);
}

struct node* find(char* name)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Ochered' pusta\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Element '%s' nayden s prioritetom %d\n", name, struc->priority);
            return struc;
        }
        struc = struc->next;
    }
    printf("Element ne nayden\n");
    return NULL;
}

void del(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Ochered' pusta\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head = struc->next;
        if (head == NULL)
        {
            last = NULL;
        }
        free(struc);
        dlinna--;
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

            if (struc == last)
            {
                last = prev;
            }

            free(struc);
            dlinna--;
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

struct node* pop(void)
{
    struct node* temp;
    if (head == NULL)
    {
        printf("Ochered' pusta\n");
        return NULL;
    }

    temp = head;
    head = head->next;

    if (head == NULL)
    {
        last = NULL;
    }

    dlinna--;
    return temp;
}

void peek(void)
{
    if (head == NULL)
    {
        printf("Ochered' pusta\n");
        return;
    }

    printf("Element s naivysshim prioritetom: %s (prioritet: %d)\n",
        head->inf, head->priority);
}

int main()
{
    int choice;
    char name[256];
    struct node* extracted;

    while (1)
    {
        printf("\n=== PRIORITETNAYA OCHERED' ===\n");
        printf("1. Dobavit' element\n");
        printf("2. Posmotret' ochered'\n");
        printf("3. Nayti element\n");
        printf("4. Udalit' element\n");
        printf("5. Izvlech' element s naivysshim prioritetom\n");
        printf("6. Posmotret' element s naivysshim prioritetom\n");
        printf("0. Vykhod\n");
        printf("Vyberite deystvie: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            spstore();
            break;
        case 2:
            review();
            break;
        case 3:
            printf("Vvedite nazvanie dlya poiska: ");
            scanf("%s", name);
            find(name);
            break;
        case 4:
            printf("Vvedite nazvanie dlya udaleniya: ");
            scanf("%s", name);
            del(name);
            break;
        case 5:
            extracted = pop();
            if (extracted != NULL)
            {
                printf("Izvlechen element: %s (prioritet: %d)\n",
                    extracted->inf, extracted->priority);
                free(extracted);
            }
            break;
        case 6:
            peek();
            break;
        case 0:
            printf("Vykhod iz programmy\n");
            return 0;
        default:
            printf("Nevernyy vybor\n");
        }
    }
}

