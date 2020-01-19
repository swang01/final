# ByteType
By Vivian Huynh (5), Rachel Leong (10), Steve Wang (10)

### Description
  Welcome to ByteType, a type-racing game modeled after the game NitroType which you can find and play at nitrotype.com. To play, up to 4 players will join a game. The “race host” has the option to start when everyone is ready by pressing a button. After a short delay, users will type a paragraph of text selected randomly from a database as fast, and accurately as they can before the other players finish. Each player (not including bots) is given a boost that players can use once per game to skip a word. Statistics like words per minute and accuracy as well as positions will be displayed in real time. 

### Required Libraries
 - The ncurses library is needed in order for the game to be run.
    - In order to install ncurses, do sudo apt-get install libncurses5-dev libncursesw5-dev
    
### How to Play

### Devlog
#### Thurs, 1/2/2020 - Tues, 1/7/2020
 - Proposal got finalized after fixing the initial issues
 - Initial empty files were added
 
#### Wed, 1/8/2020
 - Rachel:
   - Completed char_check function
   - Having issues with ending the race
   - Attempted to find a library to utilize for real-time typing but didn't get it --> ask later in class
 - Steve: 
   - Added the 30 random paragraphs to paragraphs.txt
 
#### Thurs, 1/9/2020
 - Vivian:
   - Began working on displaying the paragraph as the user types and tried to figure out how to implement colors into terminal
 - Rachel:
   - Got the game to end properly
   - User inputing and typing works, but you have to press enter after every key in order to type which is very annoying *ugh*
   - Added a string to keep track of what was already typed (for display function to be implemented later)
     - Updated parameters for char_check accordingly
 - Steve:
   - Worked on functions to select a random paragraph from the file paragraphs.txt
   
#### Fri, 1/10/2020
  - Vivian:
    - Learning about ncurses and tried to start implementing
  - Rachel:
    - Reviewing pipes and networking code
  - Steve:
    - Continued working on function to select a random paragraph from paragraphs.txt
  
#### Sat, 1/11/2020
  - Vivian:
    - Continued trying to implement ncurses
  - Rachel:
    - Continued to get a better idea about pipes and networking
    
#### Sun, 1/12/2020
  - Vivian:
    - Finished implementing typing. The program should end after completely typing the paragraph.
  - Rachel:
    - Helped Vivian and Steve debug parts of their functions
  - Steve:
    - Tried something else for random_paragraph(), works better but still doesn't work.

#### Mon, 1/13/2020
  - Rachel:
    - Helped Steve fix random_paragraph()
    - More review of pipes
    - Added .gitignore for C to repo
    - "typed" variable no long is twice the size it should be (fixed!)
  - Steve:
    - Fixed random_paragraph() and integrated it into main() to select a random paragraph and run the game with it.
    
#### Tues, 1/14/2020
  - Vivian:
    - Tried to calculate statistics, however having a hard time with wpm because it's much more complicated than we originally thought :'(
    - The paragraphs had a lot of blankspaces after them that were not spaces and I tried getting rid of them because the race can't end without typing those blankspaces but I did not succeed
    
#### Thurs, 1/16/2020
  - Steve:
    - Renamed original README.md to PROPOSAL.md
    - Created and updated README.md
    
#### Sat, 1/18/2010
  - Vivian:
    - Fixed the issue with the blackspace
    - Bug: After typing a few characters, the string starts to shift and I don't know what's causing it IUADJNKFXV
    - Finally got the wpm calculator to work
