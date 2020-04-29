typedef struct History
{
    Vehicle v;
    int date;
    int time;

    struct History *next;

} History;

History *newNode(Vehicle v, int date, int time)
{
    History *qode = (History *)malloc(sizeof(History));

    qode->date = date;
    qode->v = v;
    qode->time = time;
    qode->next = NULL;

    return qode;
}

History *insertQode(History *root, History *newqode)
{
    if (root == NULL)
    {
        return newqode;
    }

    History *tmp = root;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = newqode;

    return root;
}

History *Park_Vehicle(Vehicle *root, int vehicle_number, char vehicle_type ,wing *a, wing *b, wing *c, int date, int time, History *h)
{
    Vehicle *tmp = searchVehicle(root,vehicle_number) ;
    Vehicle *v = (Vehicle*)malloc(sizeof(Vehicle)) ;
    if(tmp == NULL)
    {
        printf("Guest Vehicle\t %d\n",vehicle_number) ;
        v->vehicle_number = vehicle_number ;
        v->vehicle_type = vehicle_type ;
        Alloc_Guest_Car(v,a,b,c) ;
    }
    else
    {
        v = tmp ;
        printf("Successfully Parked the vehicle\n") ;
    }

    parking *P;
    char wing_id = v->wing_id;
    int done = 0;
    if (wing_id == 'A')
    {
        P = &(a->pl);
    }
    else if (wing_id == 'B')
    {
        P = &(b->pl);
    }
    else
    {
        P = &(c->pl);
    }

    for (int i = 0; i < MAX_SPOTS && done == 0; i++)
    {
        if (P->vehicle_number_stored_C[i] == v->vehicle_number)
        {
            P->status_compact_spots[i] = 1;
            done = 1;
        }
    }

    if (done != 1)
    {
        for (int i = 0; i < MAX_SPOTS && done == 0; i++)
        {
            if (P->vehicle_number_stored_l[i] == v->vehicle_number)
            {
                P->status_large_spots[i] = 1;
                done = 1;
            }
        }
    }

    History *newN = newNode(*v, date, time);
    //printf("\n\n New Node created\n\n");

    //printf("%d" , newN->date) ;

    h = insertQode(h, newN);

    //printf("History date%d" , h->date) ;

    return h;
}

void Display_Visitors(History *h, int date)
{
    int date_started = 0;
    printf("\n\n\n") ;
    History *temp = h;
    if (temp == NULL)
    {
        printf("no vehicle for that day\n");
    }
    else
    {
        while (temp != NULL && temp->date != date)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("no vehicle for the given day\n");
        }
        else if (temp->date == date)
        {
            date_started = 1;
        }
        if (date_started == 1)
        {
            while (temp != NULL && temp->date == date)
            {
                printf("vehicle number :%d\n", temp->v.vehicle_number);
                if (temp->v.vehicle_type == '2')
                {
                    printf("vehicle type :two-wheeler\n");
                }
                else
                {
                    printf("vehicle type :four-wheeler\n");
                }
                printf("parking Level:%c\n", temp->v.wing_id);
                printf("parking Spot:%d\n", temp->v.parkingNumber);
                printf("\n");
                temp = temp->next;
            }
        }
    }
}

void Parking_status(wing a, wing b, wing c)
{
    int i;
    printf("For wing A\n");
    printf("compact Spots:\n");
    for (i = 0; i < a.pl.no_of_compact_spots; i++)
    {
        printf("%d ", a.pl.status_compact_spots[i]);
    }
    printf("\n");
    printf("Large Spots:\n");
    for (i = 0; i < a.pl.no_of_large_spots; i++)
    {
        printf("%d ", a.pl.status_large_spots[i]);
    }
    printf("\n");
    printf("For wing B\n");
    printf("compact Spots:\n");
    for (i = 0; i < b.pl.no_of_compact_spots; i++)
    {
        printf("%d ", b.pl.status_compact_spots[i]);
    }
    printf("\n");
    printf("Large Spots:\n");
    for (i = 0; i < b.pl.no_of_large_spots; i++)
    {
        printf("%d ", b.pl.status_large_spots[i]);
    }
    printf("\n");
    printf("For wing C\n");
    printf("compact Spots:\n");
    for (i = 0; i < c.pl.no_of_compact_spots; i++)
    {
        printf("%d ", c.pl.status_compact_spots[i]);
    }
    printf("\n");
    printf("Large Spots:\n");
    for (i = 0; i < c.pl.no_of_large_spots; i++)
    {
        printf("%d ", c.pl.status_large_spots[i]);
    }
    printf("\n");
}



void PrintHistory(History *h)
{
    //printf("Inside the print function\n") ;
    History *H = h; //printf("%d",h->date) ;
    while (H != NULL)
    {
        printf("\n\nVehicle Number is %d \n Vehicle Parking lot is %d\n\ Vehicle Wing is %c\n Vehicle type is %c\n Date is %d\n Time is %d\n ",
               H->v.vehicle_number, H->v.parkingNumber, H->v.wing_id, H->v.vehicle_type , H->date, H->time);

        H = H->next;
    }
}
