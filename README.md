# Stratego written in C++
A class project to sucessfully write a game using Object Oriented Programming
## How to play
### Pieces (Ordered by rank)
1 Marshal
1 General
2 Colonels
3 Majors
4 Captains
4 Liutenents
4 Seargents
5 Miners
8 Scouts
1 Spy

6 Bombs
1 Flag

### Movement
1. Turns alternate, first Red the Blue.
2. A piece moves from square to square, one square at a time (Exception: Scout -- see rule 7). A piece may be moved forward, backward, or sideward but not diagonally.
3. Two pieces may not ocupy the same square at the same time.
4. A piece may not move through a square occupied by a piece nor jump over a piece.
5. Only one piece may be moved in each turn.
6. The Flag and Bomb pieces cannot be moved. Once these pieces are placed at the start of the game they must remain in that square.
7. The Scout may move any number of open square forward, backward, or sideward in a straight line if the player desires. Therefore, the player may choose to move the Scout only one square in his turn, so as to keep the Scout's identity hidden. The Scout is valuable for probing the oppenent's positions. The Scout may not move and strike in the same turn.
8. Pieces cannot be moved back and forth between the same 2 squares in 3 consecutive turns.
9. A player must either move or strike in his turn.
### Combat
1. Wehn a red and blue piece occupy adjoining squares either back to back, side to side, or face to face, they are in a position to strike. No diagonal strikes can be make.
2. A okayer may move on his/her turn or strike on their turn. He/She cannot do both. The strike ends the turn. After pieces have finished the strike move, the player who was struck has his/her turn to move or strike.
3. It is not required to strike when two opposiing pieces are in position. A player may decide to strike, whenever he/she desires.
4. Either player may strike (on his/her turn); not only the one who moved their piece into position.
5. The piece with the lower rank is lost and removed from the board. The winning higher-ranking piece is then moved immediately into the empty square formerly occupied by the losing piece.
6. When equal ranks are struck, then both pieces are lost and removed from the board.
7. A Marshal removes a General, a General removes a Colonel, and A Colonel removes a Major and so on down to the Spy, which is the lowest ranking piece.
8. The Spy, however, has the special privilege of being able to remove only the Marshal provided he/she strikes first. This is, if the Spy strikes the Marshal on his/her turn, the Marshal is removed. However, if the Marshal strikes first, the Spy is removed. All other pieces remove the Spy regardless of who strikes first.
9. When any piece (except a Miner) strikes a Bomb (Bang!) that piece is lost and is removed from the board. The Bomb does not move into the empty square, but remains in its original position at all times. When a Miner strikes a Bomb, the Bomb is lost and the Miner moves into the unoccupied square.
10. A Bomb cannot strike, but rather must wait until a moveable piece strikes it.
11. Remember, the Flag also can never be moved.

### To End the Game
When a player strikes his.her opponent's Flag, the game ends and he/she is the winner.

Note: If a player cannot move a piece or strike in his/her turn, they must give up and declare their opponent the winner.