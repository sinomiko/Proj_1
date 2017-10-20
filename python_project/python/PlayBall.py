import  math
import random


ascore=0
bscore=0
ballscored=0
catchball=0
while True:
    aplay=random.randint(0,1)
    for i in range(1,10000):
        if aplay==1:
            ascore=ascore+2
            aplay=0
        else:
            while ballscored==0:
                bscored=random.randint(0,2)
                if bscored==0:
                    bscore=bscore+3
                    aplay=1
                    ballscored=1
                else:
                    catchball=random.randint(0,1)
                    if catchball==0:
                         ascore=ascore+2
                         ballscored=1
                         aplay=0
                    else :
                         aplay=1
            ballscored=0

    print '%s win: A score=%d,B score=%d' %("B" if ascore>bscore else "A",ascore,bscore)



