#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];      
    struct node* next;  
};

struct node* top = NULL, * f = NULL; 
int stack_size = 0;

void push(void), display_stack(void), del_by_name(char* name);
int is_empty(void);
void pop(void);
struct node* peek(void);
void swap_top_bottom(void);

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
    return (top == NULL);
}

void push(void)
{
    struct node* p = NULL;
    p = get_struct();

    if (p == NULL) return;

    p->next = top;
    top = p;
    stack_size++;

    printf("Element '%s' dobavlen na vershinu steka\n", p->inf);
}

void pop(void)
{
    struct node* temp;

    if (is_empty())
    {
        printf("Stek pust (Stack Underflow)\n");
        return;
    }

    temp = top;
    printf("Element '%s' udalen s vershiny steka\n", temp->inf);

    top = top->next; 
    free(temp);       
    stack_size--;
}

struct node* peek(void)
{
    if (is_empty())
    {
        printf("Stek pust\n");
        return NULL;
    }

    printf("Verkhniy element steka: %s\n", top->inf);
    return top;
}

void display_stack(void)
{
    struct node* struc = top;
    if (is_empty())
    {
        printf("Stek pust\n");
        return;
    }

    printf("Soderzhimoe steka (ot vershiny k osnovaniyu):\n");
    printf("Top -> ");
    while (struc)
    {
        printf("%s", struc->inf);
        if (struc->next != NULL)
            printf(" -> ");
        struc = struc->next;
    }
    printf(" <- Bottom\n");
    printf("Razmer steka: %d\n\n", stack_size);
}

struct node* find(char* name)
{
    struct node* struc = top;
    int position = 0;

    if (is_empty())
    {
        printf("Stek pust\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Element '%s' nayden na pozitsii %d ot vershiny\n", name, position);
            position++;
        }
        struc = struc->next;
    }
    if (!position) {
        printf("Element ne nayden\n");
        return NULL;
    }
}

void del_by_name(char* name)
{
    struct node* struc = top;
    struct node* prev = NULL;
    int flag = 0;

    if (is_empty())
    {
        printf("Stek pust\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        top = struc->next;
        free(struc);
        stack_size--;
        printf("Element '%s' udalen so steka\n", name);
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
            free(struc);            
            stack_size--;
            printf("Element '%s' udalen so steka\n", name);
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

void clear_stack(void)
{
    while (!is_empty())
    {
        pop();
    }
    printf("Stek polnost'yu ochishchen\n");
}

int get_size(void)
{
    return stack_size;
}

void swap_top_bottom(void)
{
    if (is_empty() || stack_size == 1) {
        printf("Nekzya swap\n");
        return;
    }

    struct node* current = top;
    struct node* prev = NULL;
    struct node* new_top = NULL;
    struct node* new_bottom = NULL;
    struct node* second = NULL; 

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    new_bottom = current; 

    second = top->next;

    new_top = top; 
    prev->next = NULL; 
    new_bottom->next = second; 
    new_top->next = NULL;
    top = new_bottom;

    current = top;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_top;

    printf("Done!\n");
}



int main()
{
    int choice;
    char name[256];

    while (1)
    {
        printf("\n=== STEK ===\n");
        printf("1. Dobavit' element v stek (push)\n");
        printf("2. Udalit' element so steka (pop)\n");
        printf("3. Posmotret' verkhniy element (peek)\n");
        printf("4. Pokazat' stek\n");
        printf("5. Nayti element\n");
        printf("6. Udalit' element po nazvaniyu\n");
        printf("7. Proverit' pustotu steka\n");
        printf("8. Poluchit' razmer steka\n");
        printf("9. Ochitit' stek\n");
        printf("10. Swap Top and Bottom\n");
        printf("0. Vykhod\n");
        printf("Vyberite deystvie: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            display_stack();
            break;
        case 5:
            printf("Vvedite nazvanie dlya poiska: ");
            scanf("%s", name);
            find(name);
            break;
        case 6:
            printf("Vvedite nazvanie dlya udaleniya: ");
            scanf("%s", name);
            del_by_name(name);
            break;
        case 7:
            if (is_empty())
                printf("Stek pust\n");
            else
                printf("V steke est' %d elementov\n", stack_size);
            break;
        case 8:
            printf("Razmer steka: %d\n", get_size());
            break;
        case 9:
            clear_stack();
            break;
        case 10:
            swap_top_bottom();
            break;
        case 0:
            clear_stack();
            printf("Vykhod iz programmy\n");
            return 0;
        default:
            printf("Nevernyy vybor\n");
        }
    }
}
