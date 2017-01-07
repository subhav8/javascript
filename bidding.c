#include<stdio.h>

struct bidder {

int num_of_products_brought;
int monetary_unit;
int my_bid_value;
int other_monetary_unit;
int other_bid_value;
int other_num_of_prod_brought;
};

int quantity_units = 50;

int rand_generator(int Min, int Max)
{
    return (rand() % (Max +1 - Min) + Min);
}

void bids(int own, int other) {

printf("My own bid value:%d\n", own);
printf("Competitor's bid value: %d \n",other);

}

int placeBID( struct bidder *b, int round) {

    int remaining_quantity_units = 0, diff_bid_value = 0;

    printf ("Round No: %d \n", round);
    if(round == 1) {

        /*Random value btw 1-10*/

        b->my_bid_value = (b->monetary_unit /  quantity_units) + rand_generator(1,10);
        return b->my_bid_value;

    } else {

        if(b->num_of_products_brought) {
            remaining_quantity_units = quantity_units - (b->num_of_products_brought + b->other_num_of_prod_brought);
                if(b->num_of_products_brought < ((60 * quantity_units) / 100)) {

                    diff_bid_value = abs(b->my_bid_value - b->other_bid_value);   
                    b->my_bid_value =  (b->monetary_unit /  remaining_quantity_units) + diff_bid_value + rand_generator(1,5);

                }
                else {

                    b->my_bid_value =  b->monetary_unit / remaining_quantity_units;
                }

        } else {

            /*I have more money than my previous bid value and
             * other's previous bid value */

            if ((b->monetary_unit > b->other_monetary_unit) &&
                (b->monetary_unit > b->my_bid_value) && 
                (b->monetary_unit >= b->other_bid_value)) {
                remaining_quantity_units = quantity_units - (b->num_of_products_brought + b->other_num_of_prod_brought);

                /* my_mo-u = 20, other_mo = 10,*/
                b->my_bid_value = rand_generator((b->monetary_unit /  remaining_quantity_units),
                                      (b->monetary_unit * 30)/100);
                return b->my_bid_value;
            }
            else if (b->monetary_unit < b->other_monetary_unit) {

                /*Only 20% of product is left */

                if ((quantity_units * 20) / 100) {
                    b->my_bid_value = 0;
                    return b->my_bid_value;
                } else {
                
                    remaining_quantity_units = quantity_units - (b->num_of_products_brought + b->other_num_of_prod_brought);
                    b->my_bid_value = (b->monetary_unit / remaining_quantity_units) + rand_generator(1, remaining_quantity_units);

                }
               
            }    

        }
    }

}

int main() 
{


    struct bidder b1, b2;

    b1.num_of_products_brought = 0;
    b1.monetary_unit= 100;
    b1.my_bid_value = 0;

    b2.num_of_products_brought = 0;
    b2.monetary_unit = 100;
    b2.my_bid_value = 0;

    int total_rounds = 0, round;
    total_rounds = quantity_units/2;

    for ( round = 1; round <= total_rounds; round++) {

        placeBID(&b1, round);
        placeBID(&b2, round);

        printf ("Round No:b1 %d \n", b1.my_bid_value);
        printf ("Round No:b2 %d \n", b2.my_bid_value);
        /* Bidder 1 bidded more */

        if (b1.my_bid_value > b2.my_bid_value ) {
            /* chenck whether bidder has sufficient funds*/

            b1.num_of_products_brought = b1.num_of_products_brought + 2;


        }

        /* Bidder 2 bidded more */
        if (b2.my_bid_value > b1.my_bid_value ) {
        b2.num_of_products_brought = b2.num_of_products_brought + 2;

        }

        /* Both bidded for same value */
        if (b2.my_bid_value == b1.my_bid_value) {
            b2.num_of_products_brought = b2.num_of_products_brought + 1;
            b1.num_of_products_brought = b1.num_of_products_brought + 1;

        }

      
        b1.monetary_unit = (b1.monetary_unit > b1.my_bid_value)? (b1.monetary_unit - b1.my_bid_value): (b1.monetary_unit -b1.monetary_unit);
        b2.monetary_unit = (b2.monetary_unit > b2.my_bid_value)? (b2.monetary_unit - b2.my_bid_value): (b2.monetary_unit - b2.monetary_unit);

        b1.other_bid_value = b2.my_bid_value;
        b1.other_monetary_unit = b2.monetary_unit;

        b2.other_bid_value = b1.my_bid_value;
        b2.other_monetary_unit = b1.monetary_unit;

        b1.other_num_of_prod_brought = b2.num_of_products_brought;
        b2.other_num_of_prod_brought = b1.num_of_products_brought;

        bids(b1.my_bid_value, b2.my_bid_value);
    }



    if (b1.num_of_products_brought > b2.num_of_products_brought) {

        printf ("Bidder 1 bbis winner item:%d cost:%d\n",b1.num_of_products_brought, b1.monetary_unit);

    }

    if (b2.num_of_products_brought > b1.num_of_products_brought) {

        printf ("Bidder 2 is winner item:%d, cost:%d,\n", b2.num_of_products_brought, b2.monetary_unit);

    }

    if (b2.num_of_products_brought == b1.num_of_products_brought) {

        if (b1.monetary_unit > b2.monetary_unit) 
            printf ("Bidder 1 ffwins the auction item:%d, cost:%d\n",b1.num_of_products_brought, b1.monetary_unit);
        else
            printf ("Bidder 2 eewins the acution item:%d, cost:%d\n",b2.num_of_products_brought, b2.monetary_unit);

    }
}

