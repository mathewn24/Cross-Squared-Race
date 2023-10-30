/*
Name: MATHEWS, Noel
SID: 1155130840
e-mail: 1155130840@link.cuhk.edu.hk
*/

#include <iostream>
#include <random>

// Constant variables to keep track of what each player chose.
enum Sciparo { ROCK = 1, PAPER = 2, SCISSORS = 3 };

int main() {
    int seed, n;
    std::cout << "Enter seed and board size: ";
    std::cin >> seed >> n;

    std::mt19937 rps(seed), die(seed);  // random number generators
    std::uniform_int_distribution<> play(1, 3);  // random int in [1, 3]
    std::uniform_int_distribution<> roll(1, 6);  // random int in [1, 6]

   int hi, hj, ci, cj, human, computer, d;
   hi = 1, hj = 1;
   ci = n, cj = 1;
   int round = 1; // Variable to keep track of every round.
   int h_dist = 0; // Human player's distance from the start.
   int c_dist = 0; // Computer's distance from the start.
   int win = 3*n-3; // This is the minimum distance required to be travelled to win on board size n.
   bool gameOver = false; // Boolean variable to controll main game while loop.
   bool draw = false; // Boolean to check if human and computer draw at RPS.
   bool humanWins; // Boolean to determine if human has won in a round of RPS. False if computer wins.


   while (gameOver == false){
      // Run nested loop to print the grid of * with H and C,
      // at their current grid locations (hi, hj) and (ci, cj).
      std::cout << "Round " << round << ":" << std::endl;
      for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= n; j++)
            if (i == ci && j == cj)
            {
               std::cout << "C "; // Handle computer case first, so that it displays on top of H player.
            } else if (i == hi && j == hj){
               std::cout << "H ";
            } else if (i == 1 || i == n || j == 1 || j == n || i == j || i + j == n+1)
            {
               std::cout << "* ";
            } else{
               std::cout << "  ";
            }
         std::cout << std::endl;
      }
      
      // Play rock, paper, scissors
      while (true){
         std::cout << "Choose (1=R, 2=P, 3=S): ";
         std::cin >> human;
         // Random choice of R, P, or S.
         computer = play(rps);

         // Output each player's choice.
         std::cout << "Human picks ";
         if (human == ROCK){
            std::cout << "Rock." << std::endl;

         } else if (human == PAPER){
            std::cout << "Paper." << std::endl;

         } else if (human == SCISSORS){
            std::cout << "Scissors." << std::endl;
         }

         std::cout << "Computer picks ";
         if (computer == ROCK){
            std::cout << "Rock." << std::endl;

         } else if (computer == PAPER){
            std::cout << "Paper." << std::endl;

         } else if (computer == SCISSORS){
            std::cout << "Scissors." << std::endl;
         }

         // Find out who wins.
         if(
            (human == ROCK && computer == SCISSORS) || 
            (human == PAPER && computer == ROCK) || 
            (human == SCISSORS && computer == PAPER)
            ){
               humanWins = true;
               draw = false;
         } else if(
            (computer == ROCK && human == SCISSORS) || 
            (computer == PAPER && human == ROCK) || 
            (computer == SCISSORS && human == PAPER)
            ){
               humanWins = false;
               draw = false;
         } else{
            std::cout << "Draw!" << std::endl;
            draw = true;
         }

         // If there is a winner roll the die and add it to the winner's total distance from start.
         if(draw == false){
            d = roll(die);
            if (humanWins){
               h_dist += d;
               std::cout << "Human wins and moves " << d << " step(s)." << std::endl;
               
            } else {
               c_dist += d;
               std::cout << "Computer wins and moves " << d << " step(s)." << std::endl;
            }
            round += 1; // Increase the round and exit the RPS loop.
            break;
            }
      }

      // Adjust H's location (hi, hj) based on its distance away from the start.
      if (h_dist < n)
      {  
         // First direction: Top row left to right.
         hi = 1;
         hj = h_dist+1; // Simply increase the column number by the distance if the total is less than n.

      } else if (h_dist >= n && h_dist <= (2*n-2))
      {
         // Second direction: Diagonal from top-right to bottom-left.
         int diff = h_dist - n; // Find the difference from n, and add the difference to the diagonal direction.
         hi = diff + 2;
         hj = (n-1) - diff;

      } else if (h_dist > (2*n-2))
      {
         // Third direction: Bottom row left to right.
         int delta;
         delta = h_dist - (2*n-2) + 1;
         hi = n;
         hj = delta; // Set hj to the final delta.
      }
      
      // Adjust C's location (ci, cj) based on its distance away from the start.
      if (c_dist < n)
      {  
         // First direction: Bottom row from left to right.
         ci = n;
         cj = c_dist+1;

      } else if (c_dist >= n && c_dist <= (2*n-2))
      {
         // Second direction: Diagonal from bottom-right to top-left.
         int c_diff = c_dist - n;
         ci = (n-1) - c_diff;
         cj = ci;

      } else if (c_dist > (2*n-2))
      {
         // Third direction: Top row from left to right
         int c_delta;
         c_delta = c_dist - (2*n-2) + 1;
         ci = 1;
         cj = c_delta;
      }
      
      if ((h_dist >= win) || (c_dist >= win)){
         std::cout << "Game over!" << std::endl;
         if (h_dist >= win)
         {
            std::cout << "Human wins the game!" << std::endl;
         } else if (c_dist >= win){
            std::cout << "Computer wins the game!" << std::endl;
         }
         
         gameOver = true;
      }
      
   }
}