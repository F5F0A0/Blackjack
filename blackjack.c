#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/***********************************************************
*      Blackjack Simulator: Single Player vs. Computer     *
*                                                          *
* Author:  Bridget Brinkman brb351                         *
*                                                          *
* GitHub: https://github.com/F5F0A0                        *
*                                                          *
* Purpose:  Pitt CS449 project1 Summer 2024                *
*                                                          *
* Usage:  Play blackjack for as long as you'd like!        *
***********************************************************/
int player_hand[21] = {0}; // maximum number of cards without busting is 21 (all aces)
int dealer_hand[21] = {0}; // player and dealer must stand if they are at 21, cannot hit, thus array can hold max 21 cards

int player_hand_ace[21] = {0}; // secondary array for player, first ace dealt is stored as an 11
int dealer_hand_ace[21] = {0}; // secondary array for dealer, first ace dealt is stored as an 11

int player_ace; // boolean to determine if we have converted an ace for the player in player_ace_hand
int dealer_ace; // boolean to determine if we have converted an ace for the dealer in dealer_ace_hand

// mark 0 if we don't want to print because ace hand busted
int print_player_ace; // boolean to determine whether to print/compare player_hand_ace
int print_dealer_ace; // boolean to determine whether to print/compare dealer_hand_ace

char line[100]; // reads line of user input
char user_input[100]; // user input computed
char stand[] = "stand";
char hit[] = "hit";
char quit[] = "quit";

int i = 2; // index to append new cards to the player and dealer hands (array of integers representing card value
int j = 2; // i for player, j for dealer


// function to simulate dealing a random card if the dealer has an "infinite"
// amount of standard 52 card decks to deal from
// sampling with replacement (statistics)
int deal_card() {
        // ace, 2, 3, ..., 9 all share the same probability 4/52 = 1/13
        // because J, Q, K count as 10,
        // the probability of drawing a 10 is 16/52 = 4/13
        int low = 1;
        int high = 13;
        // formula to draw a random card between 1-13
        int card = rand() % (high - low + 1) + low;
        if (card > 10) { // if J(11), Q(12), K(13) is drawn counts as a 10
                return 10;
        }
        return card; // else return card
}


// function to tally up the cards in a hand
int tally_hand(int hand[], int size) {
        int i = 0;
        int tally = 0;
        for(i; i < size; i++) {
                tally += hand[i];
        }
        return tally;
}


// function to reset an array that stores a hand of cards
// resets all cards to 0, used at the start of a new round
void reset_hand(int hand[], int size) {
        for (int i = 0; i < size; i++) {
                hand[i] = 0;
        }
}


// function to read in and compute user input, user can "hit", "stand", or "quit"
int get_input() {
        printf("Would you like to \"hit\" or \"stand\"? ");

        fgets(line, sizeof(line), stdin); // read a line of input

        int len = strlen(line); // remove newline character
        if (len > 0 && len[line - 1] == '\n') {
                line[len - 1] = '\0';
        }

        //sscanf(line, "%s", user_input); // parses line, looks for first string
        strcpy(user_input, line); // copies the input

        if(strcmp(user_input, stand) == 0) {
                return 0;
        }
        else if(strcmp(user_input, hit) == 0) {
                return 1;
        }
        else if(strcmp(user_input, quit) == 0) {
                return 2;
        }
        else {
                return 3;
        }
        return 3;
}


// function to handle printing the current cards in a hand and their total
void print_cards(int hand[], int size, int tally, int player) {
        int i;
        // this "if" block prints the dealer's cards
        if(player == 0) { // 0 since we always print dealer first
                if(((hand[0] == 1 || hand[0] == 11) && hand[1] == 10) || (hand[0] == 10 && (hand[1] == 1 || hand[1] == 11))) {
                        // dealer has natural blackjack
                        printf("%d + %d = %d\n", hand[0], hand[1], tally);
                }
                else { // dealer doesn't have natural blackjack
                        if(hand[3] == 0) { // obfuscates dealer's second card as a ? on dealer's first turn
                                printf("%d + ?\n", hand[0]);
                        }
                        else { // dealer has taken a turn, and we want to reveal all of their cards
                                for(i = 0; i < size; i++) {
                                        if(i == (size - 1) || hand[i + 1] == 0) { // last element of the array, or trailing 0's
                                                printf("%d = %d\n", hand[i], tally);
                                                break; // we are done printing
                                        }
                                        else {
                                                printf("%d + ", hand[i]);
                                        }
                                }
                        }
                }
        }
        // this "if" block prints the player's cards
        if(player == 1) { // 1 since we always print player second
                for(i = 0; i < size; i++) {
                        if(i == (size - 1) || hand[i + 1] == 0) { // last element of the array, or trailing 0's
                                printf("%d = %d\n", hand[i], tally);
                                break; // we are done printing
                        }
                        else {
                                printf("%d + ", hand[i]);
                        }
                }
        }
}


// function to check if the player and/or dealer have natural blackjacks
// 0 = no naturals found
// 1 = player win
// 2 = dealer win
// 3 = tie
int check_naturals() {
        // player has natural blackjack
        if((player_hand[0] == 1 && player_hand[1] == 10) || (player_hand[0] == 10 && player_hand[1] == 1)) {
                // dealer has natural blackjack
                if((dealer_hand[0] == 1 && dealer_hand[1] == 10) || (dealer_hand[0] == 10 && dealer_hand[1] == 1)) {
                        // shows the current dealer cards
                        printf("The dealer:\n");
                        print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_ace, sizeof(deal>

                        // shows the player their current cards
                        printf("You:\n");
                        print_cards(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0]), tally_hand(player_hand_ace, sizeof(play>

                        printf("\nTie blackjack, wow! <<<\n");

                        return(3); // tie
                }
                else { // dealer does not have natural blackjack
                        // shows the current dealer cards
                        printf("The dealer:\n");
                        print_cards(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0]), tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(>

                        // shows the player their current cards
                        printf("You:\n");
                        print_cards(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0]), tally_hand(player_hand_ace, sizeof(play>

                        printf("\nPlayer wins with natural blackjack! <<<\n");

                        return(1); // player win
                }
        }
        else if((dealer_hand[0] == 1 && dealer_hand[1] == 10) || (dealer_hand[0] == 10 && dealer_hand[1] == 1)) {
                // shows the current dealer cards
                printf("The dealer:\n");
                print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_ace, sizeof(dealer_hand_>

                // shows the player their current cards
                printf("You:\n");
                // prints player_hand
                print_cards(player_hand, sizeof(player_hand)/sizeof(player_hand[0]), tally_hand(player_hand, sizeof(player_hand)/sizeof(player_h>
                // also prints player_hand_ace
                if(player_ace == 1) {
                        print_cards(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0]), tally_hand(player_hand_ace, sizeof(play>
                }

                printf("\nThe dealer wins with natural blackjack. <<<\n");

                return(2); // dealer win
        }
        else {
                return(0); // no naturals found
        }
}


int main() {
        srand((unsigned int)time(NULL)); // seeds RNG once per program

        // welcome message
        printf("--------------------- Welcome to ---------------------\n");
        printf("*              Bridget's Virtual Casino!             *\n"); // all your money is mine
        printf("*          Type \"quit\" to quit at any time.          *\n");
        printf("------------------------------------------------------\n");
        // game loop:
        while(1) {
                // the start of a new game
                printf("*--------------------- New Game ---------------------*\n");
                int player_ace = 0; // boolean to determine if we have converted an ace to an 11 for player
                int dealer_ace = 0; // boolean to determine if we have converted an ace to 11 for dealer
                // 0 = false, 1 = true
                // only one ace maximum is converted to an 11, if 2 aces are converted it's 22 or more and bust
                print_dealer_ace = 0; // boolean to determine if we should print player_ace_hand
                print_player_ace = 0; // boolean to determine if we should print dealer_ace_hand
                // we will cease printing if the hands bust

                int dealer_plays = 1; // boolean to determine if dealer plays, 1 = true, 0 = false
                int standoff = 1; // boolean to determine if a player vs. dealer hand comparison is done to determine winner
                int action; // integer to direct control flow regarding whether user stands, hits, quits
                int quit = 0; // allows user to quit out of program
                i = 2; // reset index for player
                j = 2; // reset index for dealer

                reset_hand(player_hand, sizeof(player_hand)/sizeof(player_hand[0])); // reset player_hand
                reset_hand(dealer_hand, sizeof(player_hand)/sizeof(player_hand[0])); // reset dealer_hand


                reset_hand(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0])); // reset player_hand_ace
                reset_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])); // reset dealer_hand_ace

                player_hand[0] = deal_card();
                player_hand[1] = deal_card();

                player_hand_ace[0] = player_hand[0]; // copies cards
                player_hand_ace[1] = player_hand[1]; // copies cards

                // from this point on, we will search for the first ace to convert
                if(player_hand_ace[0] == 1) { // searching for first ace to convert
                        player_hand_ace[0] = 11;
                        player_ace = 1;
                        print_player_ace = 1;
                }
                if(player_ace != 1 && player_hand_ace[1] == 1) { // if second card is an ace, and first card was not
                        player_hand_ace[1] = 11;
                        player_ace = 1;
                        print_player_ace = 1;
                }

                dealer_hand[0] = deal_card();
                dealer_hand[1] = deal_card();

                dealer_hand_ace[0] = dealer_hand[0]; // copies cards
                dealer_hand_ace[1] = dealer_hand[1]; // copies cards

                if(dealer_hand_ace[0] == 1) { // searching for first ace to convert
                        dealer_hand_ace[0] = 11;
                        dealer_ace = 1;
                        print_dealer_ace = 1;
                }
                if(dealer_ace != 1 && dealer_hand[1] == 1){ // if second card is an ace, and first was not
                        dealer_hand_ace[1] = 11;
                        dealer_ace = 1;
                        print_dealer_ace = 1;
                }

                // will check if player and/or dealer has natural blackjack
                // if check_naturals returns 0 (meaning no naturals), continue playing
                if(check_naturals() == 0) {

                        // shows the current dealer cards
                        printf("The dealer:\n");
                        print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_ace, sizeof(deal>

                        // shows the current player cards
                        printf("You:\n");
                        // prints player_hand
                        print_cards(player_hand, sizeof(player_hand)/sizeof(player_hand[0]), tally_hand(player_hand, sizeof(player_hand)/sizeof(>
                        // also prints player_hand_ace
                        if(player_ace == 1) {
                                print_cards(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0]), tally_hand(player_hand_ace, siz>
                        }

                        // player's turn loop
                        while(1) {
                                action = get_input(); // function to handle getting user input
                                if(action == 0) { // if stand, break
                                        break;
                                }
                                else if(action == 1) { // if hit, add another card to user's hand
                                        player_hand[i] = deal_card();
                                        player_hand_ace[i] = player_hand[i]; // copy card
                                        if(player_hand_ace[i] == 1 && player_ace != 1) { // convert first ace
                                                player_hand_ace[i] = 11;
                                                player_ace = 1;
                                        }
                                        if(tally_hand(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0])) <= 21 && (player_ace >
                                                print_player_ace = 1;
                                        }
                                        if(tally_hand(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0])) > 21 && (player_ace =>
                                                print_player_ace = 0;
                                        }
                                        i++; // increment index
                                }
                                else if(action == 2) { // if quit, break
                                        dealer_plays = 0;
                                        standoff = 0;
                                        quit = 1;
                                        break;
                                }
                                else {
                                        printf("Invalid input.\n");

                                        // shows the current dealer cards
                                        printf("The dealer:\n");
                                        print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_>

                                }

                                // shows the current dealer cards
                                //printf("The dealer:\n");
                                //print_cards(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0]), tally_hand(dealer_hand, sizeof(dealer_han>

                                // shows the player their current cards
                                printf("You:\n");
                                // also prints player_hand_ace
                                print_cards(player_hand, sizeof(player_hand)/sizeof(player_hand[0]), tally_hand(player_hand, sizeof(player_hand)>
                                if(player_ace == 1 && print_player_ace == 1) {
                                        print_cards(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0]), tally_hand(player_hand_>
                                }

                                // forces player to stand on 21
                                if(tally_hand(player_hand_ace, sizeof(player_hand_ace)/sizeof(player_hand_ace[0])) ==  21) {
                                        break;
                                }
                                if(tally_hand(player_hand, sizeof(player_hand)/sizeof(player_hand[0])) ==  21) {
                                        break;
                                }

                                if(tally_hand(player_hand, sizeof(player_hand)/sizeof(player_hand[0])) > 21) {
                                        printf("\nYou busted! Dealer wins. <<<\n");
                                        dealer_plays = 0; // dealer will not take a turn if player busts
                                        standoff = 0; // player vs. dealer hand comparison not needed
                                        break;
                                }
                        }

                        // QUITS GAME
                        if(quit == 1) {
                                break;
                        }

                        if(dealer_plays == 1) {
                                // shows the current dealer cards
                                // special case to feed print_cards function 1, since at this point we want to print the dealer's cards transpar>
                                printf("The dealer:\n");
                                print_cards(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0]), tally_hand(dealer_hand, sizeof(dealer_hand)>
                                if(dealer_ace == 1) { // also prints dealer_hand_ace
                                        print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_>
                                }
                        }

                        // dealer's turn loop
                        // dealer must stand if current hand is >= 17 and <= 21
                        // dealer must hit if current hand is <= 16
                        while(dealer_plays == 1) {
                                if(tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) > 21) {
                                        // if dealer_hand_ace busts, change boolean to 0
                                        print_dealer_ace = 0;
                                }
                                if(tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) > 21) {
                                        // dealer busts, player wins
                                        printf("\nThe dealer busts! You win! <<<\n");
                                        standoff = 0; // player vs. dealer hand comparison not needed
                                        break;
                                }
                                else if(dealer_ace == 1 && tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) >= 17>
                                        print_dealer_ace = 1;
                                        printf("Dealer stands on soft %d.\n", tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_>
                                        break; // dealer stands
                                }
                                else if(tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) >= 17) {
                                        printf("Dealer stands.\n");
                                        break; // dealer stands
                                }
                                else {
                                        // dealer must hit
                                        printf("Dealer must hit.\n");
                                        dealer_hand[j] = deal_card();
                                        dealer_hand_ace[j] = dealer_hand[j]; // copy card
                                        if(dealer_hand_ace[j] == 1 && dealer_ace != 1){ // convert first ace
                                                dealer_hand_ace[j] = 11;
                                                dealer_ace = 1;
                                        }
                                        if(dealer_ace == 1 && tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) < >
                                                print_dealer_ace = 1;
                                        }
                                        else {
                                                print_dealer_ace = 0; // if dealer_hand_ace busts, don't print
                                        }
                                        j++;
                                }

                                // shows the current dealer cards
                                // we no longer need to obfuscate dealer's hole card with a ?, we can print it as a "player" hand by feeding pri>
                                printf("The dealer:\n");
                                print_cards(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0]), tally_hand(dealer_hand, sizeof(dealer_hand)>
                                if(print_dealer_ace) { // also prints dealer_hand_ace
                                        print_cards(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0]), tally_hand(dealer_hand_>
                                }
                        }

                        while(standoff == 1) {
                                // at this point in code, the dealer and player both stand
                                // find out who wins!

                                // printf("%d, %d\n", print_player_ace, print_dealer_ace); // bug testing

                                if(print_player_ace == 1 && print_dealer_ace == 1) { // compare player_hand_ace and dealer_hand_ace
                                        if(tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) > tally_hand(player_h>
                                                printf("\nThe dealer wins, better luck next time! <<<\n");
                                                break;
                                        }
                                        else if (tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) < tally_hand(pl>
                                                printf("\nDealer loses. You win! <<<\n");
                                                break;
                                        }
                                        else {
                                                printf("\nTie game! <<<\n");
                                                break;
                                        }
                                }
                                else if(print_player_ace == 1 && print_dealer_ace == 0){ // compare player_hand_ace and dealer_hand
                                        if(tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) > tally_hand(player_hand_ace, siz>
                                                printf("\nThe dealer wins, better luck next time! <<<\n");
                                                break;
                                        }
                                        else if (tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) < tally_hand(player_hand_ac>
                                                printf("\nDealer loses. You win! <<<\n");
                                                break;
                                        }
                                        else {
                                                printf("\nTie game! <<<\n");
                                                break;
                                        }
                                }
                                else if(print_player_ace == 0 && print_dealer_ace == 1){ // compare player_hand and dealer_hand_ace
                                        if(tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) > tally_hand(player_h>
                                                printf("\nThe dealer wins, better luck next time! <<<\n");
                                                break;
                                        }
                                        else if (tally_hand(dealer_hand_ace, sizeof(dealer_hand_ace)/sizeof(dealer_hand_ace[0])) < tally_hand(pl>
                                                printf("\nDealer loses. You win! <<<\n");
                                                break;
                                        }
                                        else {
                                                printf("\nTie game! <<<\n");
                                                break;
                                        }
                                }
                                else { // compare player_hand and dealer_hand
                                        if(tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) > tally_hand(player_hand, sizeof(>
                                                printf("\nThe dealer wins, better luck next time! <<<\n");
                                                break;
                                        }
                                        else if (tally_hand(dealer_hand, sizeof(dealer_hand)/sizeof(dealer_hand[0])) < tally_hand(player_hand, s>
                                                printf("\nDealer loses. You win! <<<\n");
                                                break;
                                        }
                                        else {
                                                printf("\nTie game! <<<\n");
                                                break;
                                        }
                                }
                        }
                }
        }

        return 0; // end of main
}

