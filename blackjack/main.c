//
//  main.c
//  blackjack
//
//  Created by Christopher Homo Loonam on 11/5/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define BLOCK 256

enum cards {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

typedef struct {
    char *name;
    int value;
} card_t;

typedef struct {
    char *name;
    card_t *cards;
} player_t;

int isvowel(char c) {
    switch (tolower(c)) {
        case 'a':
            return 1;
        case 'e':
            return 1;
        case 'i':
            return 1;
        case 'o':
            return 1;
        case 'u':
            return 1;
        default:
            return 0;
    }
    return 0;
}

card_t card() {
    enum cards type;
    card_t card;
    
    type = rand() % KING + ACE;
    
    card.value = type;
    switch (type) {
        case ACE:
            card.name = "Ace";
            break;
        case TWO:
            card.name = "Two";
            break;
            
        case THREE:
            card.name = "Three";
            break;
            
        case FOUR:
            card.name = "Four";
            break;
            
        case FIVE:
            card.name = "Five";
            break;
            
        case SIX:
            card.name = "Six";
            break;
            
        case SEVEN:
            card.name = "Seven";
            break;
            
        case EIGHT:
            card.name = "Eight";
            break;
            
        case NINE:
            card.name = "Nine";
            break;
            
        case TEN:
            card.name = "Ten";
            break;
            
        case JACK:
            card.name = "Jack";
            card.value = 10;
            break;
            
        case QUEEN:
            card.name = "Queen";
            card.value = 10;
            break;
            
        case KING:
            card.name = "King";
            card.value = 10;
            break;

        default:
            break;
    }
    return card;
}

int main(void) {
    int i, h, j, val, val2;
    char buf[BLOCK];
    player_t dealer, player;
    
    srand((unsigned int)time(NULL));
    
    dealer.name = "Dealer";
    dealer.cards = calloc(2, sizeof(card_t));
    
    puts("Enter your name");
    scanf("%s", buf);
    
    player.name = buf;
    player.cards = calloc(2, sizeof(card_t));
    
    for (i = 0; i < 2; i++) {
        dealer.cards[i] = card();
        player.cards[i] = card();
    }
    i = 2;
    
    printf("You have been dealt a%s %s and a%s %s; the dealer is showing a%s %s\n", (isvowel(*(player.cards[0].name)))?"n":"", player.cards[0].name, (isvowel(*(player.cards[1].name)))?"n":"", player.cards[1].name, (isvowel(*(dealer.cards[0].name)))?"n":"", dealer.cards[0].name);

	if(player.cards[0].value+player.cards[1].value == 21 && dealer.cards[0].value + dealer.cards[1].value != 21 ){
		printf("Blackjack! You win!");
		return 0;
			}
	else if(player.cards[0].value+player.cards[1].value == 21 && dealer.cards[0].value + dealer.cards[1].value == 21){
		printf("Blackjack! But the dealer also had a%s %s and a%s %s. Tie!\n", (isvowel(*(dealer.cards[0].name)))?"n":"", dealer.cards[0].name, (isvowel(*(dealer.cards[1].name)))?"n":"", dealer.cards[1].name);
		return 0;
		}
    while (1) {
        puts("Hit or stay?");
        scanf("%s", buf);
        if (tolower(*buf) == 'h') {
            player.cards = realloc(player.cards, ++i);
            player.cards[i-1] = card();
            printf("You have been dealt a%s %s; you now have ", (isvowel(*(player.cards[i-1].name)))?"n":"", player.cards[i-1].name);
            
            for (j = 0, val = 0; j < i; j++) {
                val += player.cards[j].value;
                (j == i-1)?printf("and a%s %s.\n", (isvowel(*(player.cards[j].name)))?"n":"", player.cards[j].name):printf("a%s %s, ", (isvowel(*(player.cards[j].name)))?"n":"", player.cards[j].name);
                if (val > 21) {
                    puts("You have busted!");
                    return 0;
                }
                else if (val == 21) {
                    puts("Blackjack! You win.");
                    return 0;
                }
            }
        }
        else if (tolower(*buf) == 's')
            break;
        else
            puts("Please try again");
        
    }
    h = 2;
    while (1) {
        for (j = 0, val2 = 0; j < h; j++) {
            val2 += dealer.cards[j].value;
            if (val2 > 21) {
                printf("The dealer has busted. %s wins!\n", player.name);
                return 0;
            }
            else if (val2 == 21) {
                puts("Blackjack! The dealer wins.");
                return 0;
            }
        }
        if (val2 < 17) {
            dealer.cards = realloc(dealer.cards, ++h);
            dealer.cards[h-1] = card();
        }
        else
            break;
    }
    for (j = 0, val = 0; j < i; j++, val += player.cards[j].value); //val contains player's, val2 contains dealer's
    for (j = 0, val2 = 0; j < h; j++, val2 += dealer.cards[j].value); //val contains player's, val2 contains dealer's
    printf("Dealer ended with %d, %s with %d.\n", val2, player.name, val);
    
    return 0;
}
