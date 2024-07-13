#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[20];
    char date[20];
    int numOfItems;
    struct items itm[20];
};

//functions to generate bills
void generateBillHeader(char name[20],char date[10])
{
    printf("\n\n");
    printf("\t    Pal Restaurant");
    printf("\n\t  ------------------");
    printf("\nDate: %s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Items\t\t");
    printf("Price\t");
    printf("Qty\t");
    printf("Total\t");
    printf("\n-----------------------------------------");
    printf("\n\n");    
}

void generateBillBody(char item[20],float price,int qty)
{
    printf("%s\t\t",item);
    printf("%.2f\t",price);
    printf("%d\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal;
    float grandTotal = netTotal+2*cgst;
    printf("-----------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%%\t\t\t%.2f",dis);
    printf("\n\t\t\t\t---------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%%\t\t\t%.2f",cgst);
    printf("\nSGST @9%%\t\t\t%.2f",cgst);
    printf("\n-----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n-----------------------------------------\n");
}

int main()
{
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[20];
    FILE *fptr;
    while(contFlag == 'y')
    {
        //dashboard
        float total = 0;
        int invoiceFound = 0;
        system("cls");
        printf("\t======PAL RESTAURANT======");
        printf("\n\nPlease select your prefered operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour Choice:\t");
        scanf("%d",&opt);
        fgetc(stdin);
        switch(opt)
        {
            case 1:
            system("cls");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer,20,stdin);
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,__DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d",&n);
            ord.numOfItems = n;

            for(int i=0;i<n;i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                printf("Please enter the quantity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Please enter the unit price:\t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty*ord.itm[i].price;
            }

            generateBillHeader(ord.customer,ord.date);
            for(int i=0;i<ord.numOfItems;i++)
            {
                generateBillBody(ord.itm[i].item,ord.itm[i].price,ord.itm[i].qty);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s",&saveBill);

            if(saveBill == 'y')
            {
                fptr = fopen("RestaurantBill.txt","a+");
                fwrite(&ord,sizeof(struct orders),1,fptr);
                if(fwrite != 0)
                    printf("\nSuccessfully saved!");
                else
                    printf("\nError saving!!!");
                fclose(fptr);
            }
            break;

            case 2:
            system("cls");
            fptr = fopen("RestaurantBill.txt","r");
            printf("\n   ******Your Previous Invoices******\n");
            while(fread(&order,sizeof(struct orders),1,fptr))
            {
                float tot = 0;
                generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numOfItems;i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].price,order.itm[i].qty);
                    tot += order.itm[i].qty*order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fptr);
            break;

            case 3:
            printf("\nEnter the name of the customer:\t");
            fgets(name,20,stdin);
            name[strlen(name)-1] = 0; 
            system("cls");
            fptr = fopen("RestaurantBill.txt","r");
            while(fread(&order,sizeof(struct orders),1,fptr))
            {
                float tot = 0;
                if(!strcmp(order.customer,name))
                {
                    printf("\t*****Invoice of %s*****",name);
                    generateBillHeader(order.customer,order.date);
                    for(int i=0;i<order.numOfItems;i++)
                    {
                        generateBillBody(order.itm[i].item,order.itm[i].price,order.itm[i].qty);
                        tot += order.itm[i].qty*order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if(!invoiceFound)
            {
                printf("Sorry the invoice for %s doesnot exists",name);
            }
            fclose(fptr);
            break;

            case 4:
            printf("\n\tThank you for chosing Pal Restaurant!");
            exit(0);
            break;

            default:
            printf("Sorry Invalid option");
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s",&contFlag);    
    }
    printf("\n\tThank you for chosing Pal Restaurant!");

    return 0;
}