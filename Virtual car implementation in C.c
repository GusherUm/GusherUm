/*Design a virtual car which switches between ‘states’ according to the inputs 
fed by a virtual driver, thereby simulating the working of an actual car.
*/
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>     

//Structure definitions//

struct hello{
    char input[20];
}s1;

struct emergency{             
	char steer[20];
};
struct emergency *cs;
void sdirection(struct emergency *);

//END//

//Function declarations//

int Autogearing(struct hello a,int *sunit);
int mode(struct hello  a, int sunit1);
int autopilot(char input1[20], int *coordinate1, int fuel1);
int fuelalert(int fuel1,char input[20]);
int trunk(char input[20]);
int roadsigns (char input[20]);
int working(char input[20], int sunit, int fuel,int coordinate[3]);
void interface();
void info(char input[],int sunit,int coordinate[],int fuel);

//END//

int main()
{
    printf("\t\t\t\t\t\t\t\tVIRTUAL CAR SIMULATOR\n");
    interface();   //interface function
    int sunit=3;
    int result,i;

    int coordinate[3],temp[3];
    printf("Enter your coordinates(x,y,z) in order:\n");
    for(int i = 0; i < 3; ++i) {
        scanf("%d", &coordinate[i]);
        temp[i]=coordinate[i];
    }
    printf("\n----------------------------------------------------------------\n");
    printf("Use the following keys to control the car:\nW : To move forward by 5 units.\nS : To move backwards by 5 units.\nA : To move left by 5 units.\nD: To move right by 5 units.");
    printf("Other functions:\nINFO COORDINATES to display coordinates.\nINFO FUEL to display fuel remaining.\nINFO MODE to display mode of vehicle.\nOPEN TRUNK and CLOSE TRUNK for trunk related functions.\nOPEN WINDOWS and CLOSE WINDOWS for window related functions.\nType PAUSE to halt the vehicle.\n");
    printf("Type ROAD MODE or TERRAIN MODE according to the state for handling vehicles in such terrain.\nType ROADSIGNS to detect any roadsigns nearby.\n");
    printf("REMEMBER TO KEEP YOUR CAPS LOCK ON\n");
    printf("\n----------------------------------------------------------------\n");

    printf("Enter your input: \n");
    gets(s1.input);
    printf("\n");
    int fuel=100;
    int p=strcmp(s1.input,"STOP");
    fuel=100;

    while (p!=0){
        fuel=autopilot(s1.input,coordinate,fuel);
        fuel= working(s1.input,sunit,fuel,coordinate);
        sunit=mode(s1,sunit);
        sunit=Autogearing(s1,&sunit);
        result=roadsigns(s1.input);                                                                                                                                                              
        trunk(s1.input);
        info(s1.input,sunit,coordinate,fuel);
        p=fuelalert(fuel,s1.input);
        int n;
	    printf("In case of emergency,press 1 to control steering:\nPress 2 if it is going smooth:\n");
	    scanf("%d",&n);
	    switch(n){
            case 1:
		    cs=(struct emergency*)malloc(sizeof(struct emergency));
            printf("Enter the direction to turn the steering(CWC-clockwise/ACWC-anticlockwise):\n");
            scanf("%s",cs->steer);
            sdirection(cs);
		    break;
		    case 2:
		    break;
		    default:
		    printf("*\n");
		    break;	
	    }   
        printf("Enter your input: \n");                                                                                    
        gets(s1.input);
        p=strcmp(s1.input,"STOP");
    }
    if (fuel <= 0)
    {
        printf("FUEL RAN OUT.\n Engine is shuting down, Car is stopping.\n");
        printf("............\n");
    }
    else {
        printf("Fuel left is %d units.\n",fuel);
    }
    printf("Your (X,Y,Z) Coordinate is:\n");
    i=0;
    for(int i = 0; i < 3; ++i) {
        printf("%d\t", coordinate[i]);
    }
    i=0;
    printf("\nYour started from: \n");
    for(int i = 0; i < 3; ++i) {
        printf("%d\t", temp[i]);
    }

    printf("\nTHANK YOU! SIGNING OUT.\n");
    printf("\n----------------------------------------------------------------\n");

        
    

}

//ASHWIN(interface)
void interface(){
    int bot,z;
    char login[10],pwd[10];
    char pool[50]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int random,i=0,a,j;
    char botcheck[6], botinput[6];
    srand(time(NULL));
    printf("WELCOME!! PLEASE LOGIN TO START\n");
    printf("USER ID: ");
    scanf("%s",login);
    printf("PASSWORD: ");
    scanf("%s",pwd);
    printf("REWRITE THE FOLLOWING STATEMENT TO VERIFY YOU ARE HUMAN AND NOT A BOT: \n");
    do{
            for (j=0; j<5; j++){
                random=rand()%35;
                botcheck[j]=pool[random];
            }
            botcheck[5]='\0';
            for (j=0; j<5; j++){
                printf("%c",botcheck[j]);
            }
            printf("\n");
            scanf("%s",botinput);
            a=strcmp(botinput,botcheck);
            if (a!=0)
            {
                printf("WRONG CREDENTIALS!!\n");
                printf("TRY AGAIN\n");
            }
             
            
        }while(a!=0);
        printf("ACCESS GRANTED\n");
        printf("AIR IN ALL 4 TYRES IS FINE FOR START!\n");
        printf("ENGINE STARTING.......\n");


}

//ASHWIN(working)
int working(char input[20], int sunit, int fuel,int coordinate[3]) {
    int w,a,s,d,pause,x;
    int fsensor, bsensor;
    srand(time(NULL));
    fsensor = rand() %15;
    bsensor = rand() %15;
    w=strcmp(input,"W");
    a=strcmp(input,"A");
    s=strcmp(input,"S");
    d=strcmp(input,"D");
    pause=strcmp(input,"PAUSE");
    //declarations end here
    

    
    if (w==0) {
        if (fsensor>4) {
            printf("Moving Forward......\n");
            fuel=fuel-sunit;
            coordinate[0] = (coordinate[0] + sunit);

        }
        else{
            printf("You might crash your car if you move further! Interuption %d meter ahead you.\n",fsensor);
        }

    }    
    else if (s==0) {
        if (bsensor>4) {
            printf("Moving Backwards......\n");
            fuel=fuel-sunit;
            coordinate[0] = coordinate[0] - sunit;
        }
        else{
            printf("You might crash your car if you move further! Interuption %d meter behind you.\n",bsensor);
        }
    }
    else if (a==0) {
        printf("Moving towards Left......\n");
        fuel=fuel-sunit;
        coordinate[2] = coordinate[2] - sunit;
    }
    else if (d==0) {
        printf("Moving towards Right......\n");
        fuel=fuel-sunit;
        coordinate[2] = coordinate[2] + sunit;
    }
    else if (pause==0) {
        printf("To resume your vehicle type START\nNo other commands is applicable now.\n");
        do{
            gets(input);
            x=strcmp(input,"START");
            if (x!=0){
                printf("Type START to resume.\n");
            }
            else{
                break;
            }
            
        }while(x!=0);
        printf("Vehicle resumes.\n");
        printf("Please Enter Your Command\n");
    
    

    }
return fuel;   
}

//YASHWANTH(autopilot)//

int autopilot(char input1[20], int *coordinate1, int fuel1) {
    int destination[3];
    int i;
    int count=0;
    int k=strncmp("AUTOPILOT MODE",input1,14);
    int a=fuel1;
    
    if (k == 0) {
       
        printf("Your current coordinates XYZ are:\n");
        for ( i = 0; i < 3; i++) {
            printf("%d\n",coordinate1[i]);
        }

        printf("Please input you destination coordinates XYZ:\n");
        
        for (i = 0; i < 3; i++) {
            scanf("%d",&destination[i]);
            if (destination[i] - coordinate1[i] < 0) {
                count = count + coordinate1[i] - destination[i];
            } else {
                count = count - coordinate1[i] + destination[i];
            }
        }
        fuel1 = fuel1 - count;
        if (fuel1 <= 0) {
            printf("Destination Cannot be Arrived.Since no enough fuel\n");
            fuel1 = a;
        } else {
            printf("Destination Arrived.\n");
            printf("Your current coordinates XYZ are:\n");
            for (i = 0; i <= 2; i++) {
                coordinate1[i] = destination[i];
                }
            }
             for (i = 0; i <= 2; i++) {
            printf("%d\n",coordinate1[i]);}
            printf("YOUR FUEL=%d\n",fuel1);  
    }
    return fuel1;  
}

//YASHWANTH(mode)//



int mode(struct hello a, int sunit1)
{ int *s=&sunit1;
    int k=strncmp("SPORTS MODE",a.input,11);
    int m=strncmp("ECONOMY MODE",a.input,12);
    if (k== 0)
    {
        if (*s == 5)
        {
            printf( "Already in Sports Mode.");
        }
        else
        {
            printf( "Mode Changed to Sports.");
        }
        *s = 5;  
    }
    else
    {
        if (m==0)
        {
            if (*s == 3)
            {
                printf( "Already in Economy Mode.");
            }
            else
            {
                printf( "Mode Changed to Economy.");
            }
            *s = 3;
        }
    }
    return *s;
}

//MURUGESH(Emergency steering function)//

void sdirection(struct emergency *cs)        
{
	if(strncmp(cs->steer,"CWC",3)==0 || strncmp(cs->steer,"cwc",3)==0)
	{
		strcpy(cs->steer,"Clockwise\n");
        printf("%s",cs->steer);
	}
	else if(strncmp(cs->steer,"ACWC",4)==0 || strncmp(cs->steer,"acwc",3)==0)
	{
		strcpy(cs->steer,"Anticlockwise\n");
        printf("%s",cs->steer);
	}
	else
	{
		printf("Invalid Keyword\n");
	}
}

//MURUGESH(Autogearing)//

int Autogearing(struct hello a,int *sunit){
    int rpm=0,b,gear=0;
    int k=strcmp(s1.input,"ROAD MODE");
    int l=strcmp(s1.input,"TERRAIN MODE");
    if(k==0){
        printf("Selected mode is Road\n");
        printf("RPM:");
        for(rpm;rpm>=0 && rpm<100;rpm=rpm+50){
            printf("%d\n",rpm);
            gear=1;
            printf("You're now on gear 1\n");
        }
        for(rpm=100;rpm>=100 && rpm<=200;rpm=rpm+75){
            gear=gear+1;
            printf("%d\n",rpm);
            printf("You're now on gear 2\n");
        }
        printf("rpm between 175 and 200 gets rounded to 200 due to momentum\n");
        for(rpm=200;rpm>=200 && rpm<=600;rpm=rpm+200){

            printf("%d\n",rpm);
            gear=gear+1;
            printf("You're now on gear 3;This is the highest gear in this mode\n");
        }
        printf("You've reached the highest possible speed limit in auto gear.Keep your hands on the steering to avoid any casualty\n");
        *sunit=3;
    }
    else{
        if(l==0){
            printf("Selected mode is Terrain\n");
            printf("RPM:");
            for(rpm;rpm>=0 && rpm<=50;rpm=rpm+50){
                gear=1;
                printf("%d\n",rpm);
                printf("You're currently on sport gear 1\n");
            }
            for(rpm;rpm>=50 && rpm<=150;rpm=rpm+75){
                gear=gear+1;
                printf("%d\n",rpm);
                printf("You're on sport gear 2\n");
            }
            for(rpm;rpm>=150 && rpm<=450;rpm=rpm+150){
                gear=gear+1;
                printf("%d\n",rpm);
                printf("You're on sport gear 3\n");

            }
            for(rpm;rpm>=450 && rpm<=900;rpm=rpm+300){
                gear=gear+1;
                printf("%d\n",rpm);
                printf("You're on sport gear 4\n");

            }
            printf("You've reached the maximum possible rpm for autoshift modes\n");
            *sunit=3;
        }
    }
    return *sunit;
}

//BALAJI//

/* Program to check road signs randomly */
struct roadsigns
{
int id;
char r_sign[50];
}rs[20];

char *p_rsign[50]={"Move Forward","Turn Right","Turn Left","Speed breaker ahead, Apply Break","Accident reported. Take another route",
"School Ahead. Slow down.","Red Signal Stop", "Yellow Signal Wait","Green Signal Move Forward", "Narrow Road ahead. Slow Down"};

int rs_count=10;


void load_roadsigns ()
{
int i;
/* Module to Load Road Signs */
for (i=0;i<rs_count;i++)
{
rs[i].id=i;
strcpy(rs[i].r_sign,p_rsign[i]);
}
}

int roadsigns (char input[20])
{
    int r;
    r=strcmp(input,"ROADSIGNS");
    if (r==0){
        /* Total Roadsign Scenario managed under the pointer p_rsign */
        load_roadsigns();
        srand(time(NULL));

        int rn;
        if (r==0){
            printf( "Road Signs Detected\n");
            rn = rand() %10;

            printf("%s\n",rs[rn].r_sign);

        }

    }
    
return 0;
}


//ANWESHA(trunk)//

int trunk(char input[20]){
    int ot,ct,ow,cw;
    ot=strcmp(input,"OPEN TRUNK");
    ct=strcmp(input,"CLOSE TRUNK");
    ow=strcmp(input,"OPEN WINDOW");
    cw=strcmp(input,"CLOSE WINDOW");

    if (ot==0){
         printf("Trunk has been opened.");
    }
    else if (ct==0){
        printf("Trunk has been closed.");
    }
    else if (ow==0){
        printf("Windows has been opened");
    }
    else if (cw==0){
        printf("Windows has been closed.");
    }
    
}
//ANWESHA(info)//
void info(char input[],int sunit,int coordinate[],int fuel){
    int coord,fuelinfo,mode,i=0;
    coord=strcmp(input,"INFO COORDINATES");
    fuelinfo=strcmp(input,"INFO FUEL");
    mode=strcmp(input,"INFO MODE");
    

    if (coord==0){
        printf("Your XYZ Coordinates are:");
        for(int i = 0; i < 3; ++i) {
        printf("%d\n", coordinate[i]);
    }

    }
    else if (fuelinfo==0){
        printf("The fuel left for travelling is: %d",fuel);

    }
    else if (mode==0){
        if (sunit==3){
            printf("Vehicle is in Economy Mode.");
        }
        else{
            printf("Vehicle is in Sports Mode.");
        }
    }
}

//BALAJI//

int fuelalert(int fuel1,char input[20]){
    int p;
    if(fuel1<20){
        printf("ALERT!!! YOUR FUEL IS LOW, REFUEL TO AVOID DISCONTINUATION!");
        if(fuel1<=0){
            p=0;
        }
    }
}
