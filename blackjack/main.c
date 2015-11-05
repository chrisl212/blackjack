//
//  main.c
//  blackjack
//
//  Created by Christopher Loonam on 11/5/15.
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
    int i, j, val;
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
    printf("You have been dealt a %s and a %s; the dealer is showing a %s\n", player.cards[0].name, player.cards[1].name, dealer.cards[0].name);
    
    while (1) {
        puts("Hit or stay?");
        scanf("%s", buf);
        if (tolower(*buf) == 'h') {
            player.cards = realloc(player.cards, ++i);
            player.cards[i-1] = card();
            printf("You have been dealt a %s; you now have ", player.cards[i-1].name);
            
            for (j = 0, val = 0; j < i; j++) {
                val += player.cards[j].value;
                (j == i-1)?printf("and a %s.\n", player.cards[j].name):printf("a %s, ", player.cards[j].name);
                if (val > 21) {
                    puts("You have busted!");
                    return 0;
                }
                else if (val == 21) {
                    printf("Blackjack! %s wins.\n", player.name);
                }
            }
        }
        else if (tolower(*buf) == 's')
            break;
        else
            puts("Please try again");
        
    }
    
    return 0;
}