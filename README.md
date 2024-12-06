# Minesweeper in a Galaxy Far, Far Away....
Built by: A JEDI (aka, Angel, Jack, Esha, Dhruv, Irfan)

### How to play Minesweeper 

Minesweeper is a single-player puzzle-solving logic game played on a grid-like board. The user attempts to figure out where within the grid there are hidden “mines” planted by the Empire to be avoided. As the user “digs up” more of the board, numbers are revealed indicating the number of adjacent mines to a given square. Using this information, the player will deduce where the hidden “mines” are, while avoiding them. 

#### The key to winning the game is to open all the safe squares without detonating a mine. 

Our version of the game offers the user two options:

1. The Command-line version. The core gameplay of our game through the Command-line version will be the player entering values representing grid coordinates, accompanied by specific flags or keywords to indicate which action (“digging”, “flagging”, etc) they wish to perform on the coordinate-specified square. This version allows users to tweak the difficulty of the board and game to their wishes.
2. The GUI version. The GUI version is limited in terms of customization however, provides a more visually engaging experience. The board is set to be 18x18 with 40 mines and although it lacks customization, it provides users the ease of playing. Players interact with the board using mouse clicks, where left-clicking on a cell reveals it, and right-clicking toggles a flag.

### How to run Minesweeper on your local computer: 

#### 1. Clone the repo in your local environment:  
----------------------------------------------------------------------
- git clone https://github.com/Sam-Scott-McMaster/the-team-assignment-team-7-a-jedi.git  
----------------------------------------------------------------------

#### 2. Navigate to the directory:  
----------------------------------------------------------------------
- cd /the-team-assignment-team-7-a-jedi.git
-----------------------------------------------------------------------

#### 3. Install library and verify: 
----------------------------------------------------------------------
-  sudo apt update
-  sudo apt install libgtk-3-dev
-  pkg-config --modversion gtk+-3.0
----------------------------------------------------------------

#### 4. Run Game: 
----------------------------------------------------------------
- make minesweeper
- ./minesweeper
---------------------------------------------------------------

#### 4. Run help flag (optional): 
----------------------------------------------------------------
- ./minesweeper --help
----------------------------------------------------------------

## How to play (Command-line version)

When you first start the game, you will be prompted with an introduction screen asking you to input your name. 

![image](https://github.com/user-attachments/assets/9e7bad4f-3781-4901-a1f6-725b652ba8af)

You will then be asked to select an option.

![image](https://github.com/user-attachments/assets/6ae5bc16-e5eb-44af-b2eb-2e2917bb1db4)

### Option 2: Begin CMD Line Game!

#### Dig

The dig (d) command is first command you need in order to dig the blocks in hopes of finding the squares without the mines. 

![image](https://github.com/user-attachments/assets/4b233210-9002-4ffe-8f4d-4b08f95c480e)

As shown above, digging the second column of the second row resulted in "1" to be revealed. This means, there exists 1 tile adjacent to the tile you digged containing a mine. 

### Flag

Flagging (f) command is the command used when you know (or have an idea) of where the mine is. Since you cant dig the mine, placing a flag is essential to win the game (as the ultimate goal is to reveal all the tiles).

![image](https://github.com/user-attachments/assets/3b6221d2-c326-405f-92e4-d338957266d9)

This is an example usage of Flag (f).

Since the tile with '1' on row 8 column 4 has an adjacent mine, the only possible area with the mine is on row 7 column 3. Thus, we've flagged that area to ensure the mine was detected. 

### Unflag

Unflagging (f) works similarly to flagging, allowing you to remove a flag from a cell if you believe it was placed incorrectly or no longer think a flag is needed there.

![image](https://github.com/user-attachments/assets/716282c0-e301-4c2c-9f90-b7c9a3958715)

Example usage is shown above.

### Help

To run the help flag, please run:
- minesweeper --help

![image](https://github.com/user-attachments/assets/5c029dc2-3a48-4b12-aa56-b87998e5fb58)


### Option 3: Select Difficulty

Our Minesweeper game stands out with its unique customization options, giving players the freedom to tailor their experience. You can choose the size of your board by specifying the number of rows and columns, as well as select your preferred difficulty level—easy, medium, or hard—ensuring a gameplay experience that suits your preference!

### Option 4: Instructions:

If you're unfamiliar with the game or need a refresher on how to play, we've got you covered! Our instructions tab provides a clear and concise guide to help you learn the rules and gameplay mechanics before you dive into your Minesweeper adventure.

![image](https://github.com/user-attachments/assets/27ca564b-7ca5-4c83-9e02-14587789cebb)

### Option 5: Exit Game:

If you would like to exit the game, you may do so.

## How to play (GUI version)

Same rules, same concept; however, using the GTK documentation, a graphical user interface version has been implemented.

When you are asked to select an option, select Option 1

![image](https://github.com/user-attachments/assets/6ae5bc16-e5eb-44af-b2eb-2e2917bb1db4)

### Option 1: Begin GUI Game!

#### How it works:

Similar to the command line version, it has the same rules except you are able to click on the tiles/blocks/cells instead of having to input the rows/columns. 

Right click to flag, left click to dig

Only downside: You are currently unable to select difficulty and change grid size.

![image](https://github.com/user-attachments/assets/8553d873-de9e-4155-8bd4-efda5d81a5b8)

Above is an example gameplay.


