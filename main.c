#include <stdio.h>
#include <string.h>
void loadBookData();
void viewBookInfo();
void mainmenu();
void issueBook();
void addBook();
void viewAllIssues();
void viewAllBooks();
struct date
{
    int dd;
    char mm[3];
    int yy;
};
struct issueInfo
{
    char name[20];
    struct date issueDate;
    struct date submitDate;
};
struct book
{
    char title[50];
    int ISBN;
    char author[20];
    char publication[20];
};
int books[300] = {0};
int issues[300] = {0};

int main()
{
    loadBookData();
    mainmenu();
    printf("Thanks for using have a great day");
    return 0;
}
void loadBookData()
{
    int i = 0;
    FILE *ap;
    FILE *ip;
    ip = fopen("bookData/issueData.txt", "r");
    ap = fopen("bookData/info.txt", "r");
    while (fscanf(ap, "%d", &books[i]) == 1)
    {
        i++;
        if (i == 300)
        {
            break;
        }
    }
    i = 0;
    while (fscanf(ip, "%d", &issues[i]) == 1)
    {
        i++;
        if (i == 300)
        {
            break;
        }
    }
    fclose(ip);
    fclose(ap);
}
void mainmenu()
{
    int n;
    printf("\nWELCOME !\n Select operation to perform-\n");
    printf("\n1.View Book Info\n2.Issue Book\n3.Add Book to Lib\n4.View All Issues\n5.View All Books\n6.Exit\nOperation(enter number) : ");
    scanf("%1d", &n);
    printf("\n");
    switch (n)
    {
    case 1:
    {
        viewBookInfo();
        break;
    }
    case 2:
    {
        issueBook();
        break;
    }
    case 3:
    {
        addBook();
        break;
    }
    case 4:
    {
        viewAllIssues();
        break;
    }
    case 5:
    {
        viewAllBooks();
        break;
    }
    case 6:
    {
        break;
    }
    default:
    {
        printf("\nInvalid Input\n");
        mainmenu();
    }
    }
}
void viewBookInfo()
{
    loadBookData();
    int n, ISBN, i;
    char fileName[100];
    FILE *fp;
    printf("\nEnter ISBN number : ");
    scanf("%6d", &ISBN);

    for (i = 0; i < 300; i++)
    {
        if (books[i] == ISBN)
        {
            sprintf(fileName, "bookData/%d.txt", ISBN);
            fp = fopen(fileName, "r");
            int ch;
            while (((ch = fgetc(fp)) != EOF))
            {
                printf("%c", ch);
            }
            fclose(fp);
            break;
        }
    }
    if (i == 300)
    {
        printf("\nNo such book exists in library\n");
    }
    printf("\nDo you want to continue operation or return to main menu ? (1/2) : ");
    scanf("%1d", &n);
    switch (n)
    {
    case 1:
    {
        viewBookInfo();
        break;
    }
    case 2:
    {
        mainmenu();
        break;
    }
    default:
    {
        printf("\nInvalid Input returning to main menu\n");
        mainmenu();
    }
    }
}
void issueBook()
{
    loadBookData();
    int n, ISBN, i;
    char fileName[100];
    struct book b1;
    struct issueInfo i1;
    FILE *fp;
    FILE *ap;
    printf("\nEnter ISBN number : ");
    scanf("%6d", &ISBN);
    for (i = 0; i < 300; i++)
    {
        if (issues[i] == ISBN)
        {
            printf("\nThis book is already issued\n");
            printf("\nIssues another book ? (1/2) : ");
            scanf("%1d", &n);
            switch (n)
            {
            case 1:
            {
                issueBook();
                break;
            }
            case 2:
            {
                mainmenu();
                break;
            }
            default:
            {
                printf("\nInvalid Input returning to main menu\n");
                mainmenu();
            }
            }
        }
    }
    for (i = 0; i < 300; i++)
    {
        if (books[i] == ISBN)
        {
            sprintf(fileName, "bookData/%d.txt", ISBN);
            fp = fopen(fileName, "r");
            int ch;
            while (((ch = fgetc(fp)) != EOF))
            {
                printf("%c", ch);
            }
            fclose(fp);
            printf("\nDo you want to issue this book? (1/2/3) : ");
            scanf("%1d", &n);
            switch (n)
            {
            case 1:
            {
                printf("\nEnter Name : ");
                scanf(" %[^\n]", i1.name);
                printf("\nEnter issue date : ");
                scanf("%2d %3[^\n] %4d", &i1.issueDate.dd, i1.issueDate.mm, &i1.issueDate.yy);
                printf("\nEnter submit date : ");
                scanf("%2d %3[^\n] %4d", &i1.submitDate.dd, i1.submitDate.mm, &i1.submitDate.yy);

                fp = fopen(fileName, "a");
                ap = fopen("bookData/issueData.txt", "a");
                if (fp != NULL && ap != NULL)
                {
                    fprintf(fp, "\nISSUED\nName : %s\nIssue Date : %d/%s/%d\nSubmit Date : %d/%s/%d\n", i1.name, i1.issueDate.dd, i1.issueDate.mm, i1.issueDate.yy, i1.submitDate.dd, i1.submitDate.mm, i1.submitDate.yy);
                    fprintf(ap, "%d\n", ISBN);
                    fclose(fp);
                    fclose(ap);
                    for (int i = 0; i < 300; i++)
                    {
                        if (issues[i] == 0)
                        {
                            issues[i] = ISBN;
                        }
                        break;
                    }
                    printf("\nBook issued succesfully\n");
                    printf("\nContinue or return to main menu ? (1/2) : ");
                    scanf("%1d", &n);
                    switch (n)
                    {
                    case 1:
                    {
                        issueBook();
                        break;
                    }
                    case 2:
                    {
                        mainmenu();
                        break;
                    }
                    default:
                    {
                        printf("\nInvalid Input returning to main menu\n");
                        mainmenu();
                    }
                    }
                }
                else
                {
                    printf("\nerror issuing book returning to main menu\n");
                    mainmenu();
                }

                break;
            }
            case 2:
            {
                printf("\nReloading Function\n");
                issueBook();
                break;
            }
            default:
            {
                printf("\nReturning to main menu\n");
                mainmenu();
            }
            }
            break;
        }
    }
    if (i == 300)
    {
        printf("\nNo such book exists in library\n");
        issueBook();
    }
}
void addBook()
{
    struct book b1;
    char fileName[100];
    int a, n, i;
    FILE *fp;
    FILE *ap;
    printf("\nEnter Book Details\nEnter ISBN : ");
    scanf("%6d", &b1.ISBN);
    for (i = 0; i < 300; i++)
    {
        if (books[i] == b1.ISBN)
        {
            printf("\nThis ISBN is already used.\n");
            printf("\n Add another book ? (1/2) : ");
            scanf("%1d", &n);
            switch (n)
            {
            case 1:
            {
                addBook();
                break;
            }
            case 2:
            {
                mainmenu();
                break;
            }
            default:
            {
                printf("\nInvalid Input returning to main menu\n");
                mainmenu();
            }
            }
        }
    }
    printf("\nEnter Title : ");
    scanf(" %[^\n]", b1.title);
    printf("\nEnter Author : ");
    scanf(" %[^\n]", b1.author);
    printf("\nEnter Publication : ");
    scanf(" %[^\n]", b1.publication);
    sprintf(fileName, "bookData/%d.txt", b1.ISBN);
    fp = fopen(fileName, "w");
    ap = fopen("bookData/info.txt", "a");
    if (fp != NULL && ap != NULL)
    {
        fprintf(fp, "Title : %s\nISBN : %d\nAuthor : %s\nPublication : %s\n", b1.title, b1.ISBN, b1.author, b1.publication);
        fprintf(ap, "%d\n", b1.ISBN);
        fclose(fp);
        fclose(ap);
        for (int i = 0; i < 300; i++)
        {
            if (books[i] == 0)
            {
                books[i] = b1.ISBN;
            }
            break;
        }
        printf("\nBook added succesfully\n");
    }
    else
    {
        printf("error adding book");
    }
    printf("\nDo you want to continue operation or return to main menu ? (1/2) : ");
    scanf("%1d", &a);
    switch (a)
    {
    case 1:
    {
        addBook();
        break;
    }
    case 2:
    {
        mainmenu();
        break;
    }
    default:
    {
        printf("\nInvalid Input returning to main menu\n");
        mainmenu();
    }
    }
}
void viewAllIssues()
{
    int n;
    char fileName[100];
    FILE *fp;
    if (issues[0] == 0)
    {
        printf("\nNo books to show\n");
    }
    else
    {
        for (int i = 0; i < 300; i++)
        {
            sprintf(fileName, "bookData/%d.txt", issues[i]);
            fp = fopen(fileName, "r");
            if (fp != NULL)
            {
                int ch;
                while (((ch = fgetc(fp)) != EOF))
                {
                    printf("%c", ch);
                }
                printf("\n");
                fclose(fp);
            }
        }
    }
    printf("\nReturn to main menu ? (1) : ");
    scanf("%1d", &n);
    switch (n)
    {
    case 1:
    {
        mainmenu();
        break;
    }
    default:
    {
        printf("\nInvalid Input returning to main menu\n");
        mainmenu();
    }
    }
}
void viewAllBooks()
{
    int n;
    char fileName[100];
    FILE *fp;
    if (books[0] == 0)
    {
        printf("\nNo books to show\n");
    }
    else
    {
        for (int i = 0; i < 300; i++)
        {
            sprintf(fileName, "bookData/%d.txt", books[i]);
            fp = fopen(fileName, "r");
            if (fp != NULL)
            {
                int ch;
                while (((ch = fgetc(fp)) != EOF))
                {
                    printf("%c", ch);
                }
                printf("\n");
                fclose(fp);
            }
        }
    }
    printf("\nReturn to main menu ? (1) : ");
    scanf("%1d", &n);
    switch (n)
    {
    case 1:
    {
        mainmenu();
        break;
    }
    default:
    {
        printf("\nInvalid Input returning to main menu\n");
        mainmenu();
    }
    }
}
