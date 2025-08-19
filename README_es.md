# Retro Z-MD

<a href="README.md"> <img src="https://img.shields.io/badge/EN-English Version here-red?style=for-the-badge" alt="EN"> </a>

## 📝 Descripción  
Minijuego de supervivencia en consola escrito en **C**, donde el jugador se mueve entre zombies, minas y teletransportadores en un tablero cerrado. El jugador gana cuando no queda ningun zombie en pie.

## 📸 Capturas  

![Inicio del Juego](image1.png)  
*Pantalla inicial pidiendo dimensiones del tablero y nivel de dificultad.*

![Juego](image2.png)  
*Pantalla del juego mostrando al jugador (S), zombies (Z), minas (*), y teletransportadores (@).*

## 📖 Descripción Detallada  
**Retro Z-MD** es un minijuego de consola desarrollado en **C**, simulando supervivencia en un tablero con zombies, minas y teletransportadores.  

### Jugabilidad:
- El jugador controla un superviviente, representado por **S**, moviéndose con las teclas `W/A/S/D` o con las flechas de dirección.  
- El tablero está rodeado por **X** y sus dimensiones se eligen al inicio (altura y anchura).  
- Se pide un nivel de dificultad del 1 al 10, que determina la probabilidad de movimiento de los zombies (1 = 10%, 10 = 100%).  

### Mecánicas del Juego:
- **Población del tablero:** según el tamaño, se calcula el porcentaje de zombies, minas (*) y teletransportadores (@). Tableros más grandes tienen más de cada elemento.  
- **Zombies:** representados por **Z**, se mueven hacia el jugador. Los zombies pueden pasar sobre otros zombies o activar minas.  
- **Minas:** representadas por `*`. Si el jugador pisa una mina, muere.  
- **Teletransportadores:** representados por `@`. Teletransportan al jugador a una ubicación aleatoria segura (sin zombies ni minas).  
- **Combate:** el jugador puede pisar un zombie para eliminarlo, pero si un zombie alcanza al jugador, este muere.  

### 🔧 Tecnologías Principales
- **Lenguaje:** C  
- **Entorno:** Consola / Línea de Comandos

  
<h2 align="center" style="margin-top: 20px;">
  <a href="<h2 align="center" style="margin-top: 20px;">
  <a href="https://github.com/TeurDev/Retro-Z-MD/releases/tag/1.0" 
     style="background-color: #0078D7; color: white; padding: 12px 24px; 
            text-decoration: none; font-weight: bold; border-radius: 8px;
            font-family: sans-serif; display: inline-block;"> 
    Descargar el juego
  </a>
</h2>
