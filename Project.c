#include<stdio.h>
#include<conio.h>
#include<string.h>
FILE *f;
int j=0;
struct stock
{
	char name[50];
	int quantity;
};
struct stock stocklist[50];
void buy()
{
	char name[50],date[50],expiry_date[50],seller_name[50];
	int price,quantity,ino,total,k,flag=0,i,total1=0,zero=0;
	float input=0,t,p;
	printf("Enter Seller name\n");
	fflush(stdin);
	gets(seller_name);
	printf("Enter invoice number\n");
	scanf("%d",&ino);
	printf("Enter date\n");
	fflush(stdin);
	gets(date);
	do{
		flag=0;
		printf("Enter commodity name\n");
		fflush(stdin);
		gets(name);
		printf("Enter price\n");
		scanf("%d",&price);
		printf("Enter Quantity\n");
		scanf("%d",&quantity);
		total=price*quantity;
		t=total;
		printf("Enter GST tax percentage\n");
		scanf("%f",&p);
		input=input+t*(p/100)/(1+p/100);
		total1=total1+total;
		printf("Enter expiry date\n");
		fflush(stdin);
		gets(expiry_date);
		f=fopen("purchase_record.dat","a");
		if(f==NULL)
		{
			puts("Cannot open file");
			//exit(0);
		}
		fprintf(f,"%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		fclose(f);
		printf("following record has been entered\n");
		printf("Invoice number--Date--Commodity--Customer--Price--Quantity--total--Expiry Date--gst\n");
		printf("%d %s %s %s %d %d %d %s %f\n",ino,date,name,seller_name,price,quantity,total,expiry_date,t*(p/100)/(1+p/100));
		f=fopen("ledger.dat","a");
		if(f==NULL)
		{
			puts("Cannot open file");
		}
		fprintf(f,"%s %s %d %d\n",date,seller_name,ino,-1*total);
		fclose(f);
		for(i=0;i<j;i++)
		{
			if(!strcmp(name,stocklist[i].name))
			{
				flag=1;
				stocklist[i].quantity=stocklist[i].quantity+quantity;
			}
		}
		if(flag==0)
		{
			strcpy(stocklist[j].name,name);
			stocklist[j].quantity=quantity;
			j++;
		}
		printf("Enter 1 to input another commodity, any other number to save the records and go to main menu\n");
		scanf("%d",&k);
	}while(k==1);
	printf("Total=%d\n",total1);
	printf("GST Input=%f\n",input);
	f=fopen("GST.dat","a");
	fprintf(f,"%d %d %f\n",ino,zero,input);
	fclose(f);
}
void sell()
{
	char name[50],date[50],buyer_name[50];
	int price,quantity,ino,total,k,flag=0,i,q,f1,total1=0,one=1,flag1=0;
	float output=0,t=0,p=0;
	printf("Enter buyer name\n");
	fflush(stdin);
	gets(buyer_name);
	printf("Enter invoice number\n");
	scanf("%d",&ino);
	printf("Enter date\n");
	fflush(stdin);
	gets(date);
	do
	{
		flag1=0;
		f=0;
		flag=0;
		printf("Enter commodity name\n");
		fflush(stdin);
		gets(name);
		for(i=0;i<j;i++)
		{
			if(!strcmp(name,stocklist[i].name))
			{
				flag=1;
				q=stocklist[i].quantity;
				break;
			}
		}
		if(flag==0)
		{
			printf("No commodity with this name in stock\nEnter 1 to Try again!!\nOr enter 5 to go back to main menu\n");
			scanf("%d",&f1);
			if(f1==5)
			break;
			sell();
		}
		else
		{
			printf("Enter quantity\n");
			scanf("%d",&quantity);
			if(quantity>q)
			{
				printf("Suffient quantity not available\nquantity available:%d\n",q);
				printf("Enter 1 to Try again!!\n");
				printf("Or enter 5 to go back to main menu\n");
				scanf("%d",&f1);
				if(f1==5)
				break;
				sell();
			}
			else
			{
				printf("Enter price\n");
				scanf("%d",&price);
				total=quantity*price;
				t=total;
				printf("Enter GST tax percentage\n");
				scanf("%f",&p);
				output=output+t*(p/100)/(1+p/100);
				total1=total1+total;
				f=fopen("sale_record.dat","a");
				if(f==NULL)
				{
					puts("Cannot open file");
					//exit(0);
				}
				fprintf(f,"%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
				fclose(f);
				f=fopen("ledger.dat","a");
				if(f==NULL)
				{
					puts("Cannot open file");
				}
				fprintf(f,"%s %s %d %d\n",date,buyer_name,ino,total);
				fclose(f);
				printf("following record has been entered\n");
				flag1=1;
				printf("Invoice number--Date--Commodity--Customer--Price--Quantity--total--gst\n");
				printf("%d %s %s %s %d %d %d %f\n",ino,date,name,buyer_name,price,quantity,total,t*(p/100)/(1+p/100));
				stocklist[i].quantity=stocklist[i].quantity-quantity;		
			}
		}
		printf("Enter 1 to add another item, any other number to save records and go back to main menu\n");
		scanf("%d",&k);
	}while(k==1);
	if(flag1=1)
	{
		printf("Total=%d\n",total1);
		printf("GST Output=%f\n",output);
		f=fopen("GST.dat","a");
		fprintf(f,"%d %d %f\n",ino,one,output);
		fclose(f);		
	}	
}
void stock()
{
	int i;
	printf("Commodity--Stock\n");
	for(i=0;i<j;i++)
	{
		if(stocklist[i].name!="")
		{
			printf("%s %d\n",stocklist[i].name,stocklist[i].quantity);
		}
	}
}
void make_payment()
{
	char name[50],date[50];
	int ref,amount;
	printf("Enter seller name\n");
	fflush(stdin);
	gets(name);
	printf("Enter date\n");
	fflush(stdin);
	gets(date);
	printf("Enter cheque number or net banking transaction id, Enter -1 for cash payment\n");
	scanf("%d",&ref);
	printf("Enter amount\n");
	scanf("%d",&amount);
	f=fopen("ledger.dat","a");
	if(f==NULL)
	{
		puts("Cannot open file");
	}
	fprintf(f,"%s %s %d %d\n",date,name,ref,amount);
	fclose(f);
	printf("following record has been entered\n");
	printf("%s %s %d %d\n",date,name,ref,amount);
}
void recieve_payment()
{
	char name[50],date[50];
	int ref,amount;
	printf("Enter customer name\n");
	fflush(stdin);
	gets(name);
	printf("Enter date\n");
	fflush(stdin);
	gets(date);
	printf("Enter cheque number or net banking transaction id, Enter -1 for cash payment\n");
	scanf("%d",&ref);
	printf("Enter amount\n");
	scanf("%d",&amount);
	f=fopen("ledger.dat","a");
	if(f==NULL)
	{
		puts("Cannot open file");
	}
	fprintf(f,"%s %s %d %d\n",date,name,ref,-1*amount);
	fclose(f);
	printf("following record has been entered\n");
	printf("%s %s %d %d\n",date,name,ref,amount);	
}
void purchase_record()
{
	char name[50],date[50],expiry_date[50],seller_name[50],buffer[50];
	int price,quantity,ino,total;
	int m=0,ino1;
	f=fopen("purchase_record.dat","r");
	printf("Enter 1 to show all records\nEnter 2 to sort by seller\nEnter 3 to sort by date\nEnter 4 sort by commodity\nEnter 5 to sort by invoice\nNo output means record not found\n");
	scanf("%d",&m);
	printf("Invoice number--Date--Commodity--Customer--Price--Quantity--total--Expiry_date\n");
	if(m==1)
	{
		while(fscanf(f,"%d %s %s %s %d %d %d %s",&ino,date,name,seller_name,&price,&quantity,&total,expiry_date)!=EOF)
		{
			printf("%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		}		
	}
	if(m==2)
	{
		printf("Enter seller name\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d %s",&ino,date,name,seller_name,&price,&quantity,&total,expiry_date)!=EOF)
		{
			if(!strcmp(buffer,seller_name))
			printf("%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		}		
	}
	if(m==3)
	{
		printf("Enter Date\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d %s",&ino,date,name,seller_name,&price,&quantity,&total,expiry_date)!=EOF)
		{
			if(!strcmp(buffer,date))
			printf("%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		}		
	}
	if(m==4)
	{
		printf("Enter Commodity name\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d %s",&ino,date,name,seller_name,&price,&quantity,&total,expiry_date)!=EOF)
		{
			if(!strcmp(buffer,name))
			printf("%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		}		
	}
	if(m==5)
	{
		printf("Enter Invoice number\n");
		scanf("%d",&ino1);
		while(fscanf(f,"%d %s %s %s %d %d %d %s",&ino,date,name,seller_name,&price,&quantity,&total,expiry_date)!=EOF)
		{
			if(ino==ino1)
			printf("%d %s %s %s %d %d %d %s\n",ino,date,name,seller_name,price,quantity,total,expiry_date);
		}		
	}
	fclose(f);
}
void sale_record()
{
	char name[50],date[50],buyer_name[50],buffer[50];
	int price,quantity,ino,total;
	int m=0,ino1;
	f=fopen("sale_record.dat","r");
	printf("Enter 1 to show all records\nEnter 2 to sort by buyer\nEnter 3 to sort by date\nEnter 4 sort by commodity\nEnter 5 to sort by invoice\nNo output means record not found\n");
	scanf("%d",&m);
	printf("Invoice number--Date--Commodity--Customer--Price--Quantity--total\n");
	if(m==1)
	{
		while(fscanf(f,"%d %s %s %s %d %d %d",&ino,date,name,buyer_name,&price,&quantity,&total)!=EOF)
		{
			printf("%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
		}		
	}
	if(m==2)
	{
		printf("Enter buyer name\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d",&ino,date,name,buyer_name,&price,&quantity,&total)!=EOF)
		{
			if(!strcmp(buffer,buyer_name))
			printf("%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
		}		
	}
	if(m==3)
	{
		printf("Enter Date\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d",&ino,date,name,buyer_name,&price,&quantity,&total)!=EOF)
		{
			if(!strcmp(buffer,date))
			printf("%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
			
		}		
	}
	if(m==4)
	{
		printf("Enter Commodity name\n");
		fflush(stdin);
		gets(buffer);
		while(fscanf(f,"%d %s %s %s %d %d %d",&ino,date,name,buyer_name,&price,&quantity,&total)!=EOF)
		{
			if(!strcmp(buffer,name))
			printf("%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
			
		}		
	}
	if(m==5)
	{
		printf("Enter Invoice number\n");
		scanf("%d",&ino1);
		while(fscanf(f,"%d %s %s %s %d %d %d",&ino,date,name,buyer_name,&price,&quantity,&total)!=EOF)
		{
			if(ino1==ino)
			printf("%d %s %s %s %d %d %d\n",ino,date,name,buyer_name,price,quantity,total);
			
		}		
	}
	fclose(f);
}
void show_ledger()
{
	int balance=0,amount,ref;
	char buffer[50],name[50],date[50];
	printf("Positive balance indicates money is to be recieved from customer or has been paid extra to seller\n");
	printf("Negative balance indicates money is to be paid to seller or customer has paid extra money\n");
	printf("Refrence=-1 indicates cash payment\n");
	printf("Enter name of seller/Customer\n");
	fflush(stdin);
	gets(buffer);
	f=fopen("ledger.dat","r");
	printf("Date--Customer/Seller--Refrence/Invoice--Amount\n");
	while(fscanf(f,"%s %s %d %d",date,name,&ref,&amount)!=EOF)
	{
		if(!strcmp(buffer,name))
		{
			printf("%s %s %d %d\n",date,name,ref,amount);
			balance=balance+amount;
		}
	}
	printf("balance:%d\n",balance);
	fclose(f);
}
void gst()
{
	int io,ino;
	float payable=0,amt;
	f=fopen("GST.dat","r");
	printf("Type--Invoice number--Amount\n");
	while(fscanf(f,"%d %d %f",&ino,&io,&amt)!=EOF)
	{
		if(io==0)
		{
			printf("Input %d %f\n",ino,amt);
			payable=payable-amt;
		}
		if(io==1)
		{
			printf("Output %d %f\n",ino,amt);
			payable=payable+amt;
		}
	}
	fclose(f);
	printf("Total Payable=%f\n",payable);
}
int main()
{
	FILE *f;
	f=fopen("stock.dat","r");
	while(fscanf(f,"%s %d",stocklist[j].name,&stocklist[j].quantity)!=EOF)
	j++;
	fclose(f);
	int i;
	do
	{
		printf("Enter 1 to enter new purchase\n");
		printf("Enter 2 to enter new sale\n");
		printf("Enter 3 to show stock\n");
		printf("Enter 4 to register payment made to seller\n");
		printf("Enter 5 to register payment recieved from customer\n");
		printf("Enter 6 to show purchase records\n");
		printf("Enter 7 to show sale records\n");
		printf("Enter 8 to show ledger\n");
		printf("Enter 9 to show GST Payable\n");
		printf("Enter 10 to exit\n");
		scanf("%d",&i);
		if(i==1)
		{
			buy();
		}
		if(i==2)
		{
			sell();
		}
		if(i==3)
		{
			stock();
		}
		if(i==4)
		{
			make_payment();
		}
		if(i==5)
		{
			recieve_payment();
		}
		if(i==6)
		{
			purchase_record();
		}
		if(i==7)
		{
			sale_record();
		}
		if(i==8)
		{
			show_ledger();
		}
		if(i==9)
		{
			gst();
		}
	}while(i!=10);
	f=fopen("stock.dat","w");
	for(i=0;i<j;i++)
	{
		fprintf(f,"%s %d\n",stocklist[i].name,stocklist[i].quantity);
	}
	fclose(f);
}
