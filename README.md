# Retro Z-MD

<a href="README_es.md"> <img src="https://img.shields.io/badge/ES-Versión en Español aquí-blue?style=for-the-badge" alt="ES222"> </a>

## 📝 Description  
A console-based survival mini-game written in **C**, where the player moves through zombies, mines, and teleporters on a bounded board. The player wins when all zombies are defeated.

## 📸 Screenshots  

![Game Start](image1.png)  
*Initial setup screen asking for board dimensions and difficulty level.*

![Gameplay](image2.png)  
*In-game screenshot showing the player (S), zombies (Z), mines (*), and teleporters (@).*

## 📖 Detailed Description  
**Retro Z-MD** is a console mini-game developed in **C**, simulating survival in a grid-based environment populated with zombies, mines, and teleporters.  

### Gameplay:
- The player controls a survivor, represented by **S**, moving with `W/A/S/D` keys or arrow keys.  
- The game board is surrounded by **X** characters and dimensions are chosen at the start (height and width).  
- The game asks for a difficulty level from 1 to 10, which determines zombie movement probability (1 = 10%, 10 = 100%).  

### Game Mechanics:
- **Board population:** Based on board size, the game calculates percentages of zombies, mines (*), and teleporters (@). Larger boards have more of each element.  
- **Zombies:** Represented by **Z**, move towards the player. Zombies can move over other zombies or trigger mines.  
- **Mines:** Represented by `*`. If the player steps on a mine, they die.  
- **Teleporters:** Represented by `@`. Teleport the player to a random safe location (no zombie or mine).  
- **Combat:** Player can step on a zombie to defeat it, but if a zombie reaches the player, the player dies.  

### 🔧 Main Technologies
- **Language:** C  
- **Environment:** Console / Command Line / .EXE
