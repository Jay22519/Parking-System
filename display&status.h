#include "Declaration.h"
#include "ParkVehicle.h"

void Display_Visitors(History *h, int date)
{
    int date_started = 0;
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
