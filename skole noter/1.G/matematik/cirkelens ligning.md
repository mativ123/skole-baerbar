# ligning
---
$c:(x-a)^2+(y-b)^2=r^2$
centrum: $c(a,b)$
radius: $r$
![[cirkelens ligning.png]]
## eksempel
### 1
en cirkel med centrum i $(3,4)$ og $r=5$:
$c:(x-3)^2+(y-4)^2=25$
### 2
en cirkel med centrum i $(-3,0)$ og $r=4$:
$c:(x+3)^2+y^2=16$
# punkt på cirkel
---
en cirkel med centrum $(3,2)$ og $r=5$
$p=(7,5)$ ligger på cirkelen.
$c:(x-3)^2+(y-2)^2=25$
#### udregning
$(7-3)^2+(5-2)^2=25\Downarrow$
$4^2+3^2=25\Downarrow$
$16+9=25\Downarrow$
$25=25$
# kvadrat komplettering
---
$c_1:(x-3)^2+(y-2)^2=25$
*kvadratsætning 2*
$c_2:x^2+9-6x+y^2+4-4y=25$
*fjerner $a$ og $b$*
$c_3:x^2-6x+y^2-4y=12$

## formler til løsning
$x^2+2kx=(x+k)^2-k^2$
$x^2-2kx=(x-k)^2-k^2$
## eksempel
$x^2+y^2+6x-10y+14=0$
*led*:
$x^2+6x$, $y^2-10y$, $14$
*udregning*:
*bruger [[#formler til løsning]]*
$x^2+6x=x^2\cdot 2\cdot \underline{3}\cdot x=\color{blue}(x+3)^2-3^2$  *(k=3)*
*bruger [[#formler til løsning]] igen*
$y^2-10y=y^2-2\cdot \underline{5} \cdot y=\color{green}(y-5)^2-5^2$ *(5=k)*
$\color{blue}(x+3)^2+3^2\color{white}+\color{green}(y-5)^2-5^2\color{white}+14=0$
$(x+3)^2+(y-5)^2=9+25-14=20$
$(x+3)^2+(y-5)^2=20$

$c(-3,5)$, $r=\sqrt{20}$
# skæring mellem cirkel og linje
---
1. mulighed
Tangent.
![[tangent.png]]
Kun et skærings punk mellem cirkel og linje.
Hvis [[distance formel|distancen]] mellem centrum og linje er lig med $r$. Eller:
$\text{dist}(l,c)=r$
2. mulighed
Sekant.
![[sekant.png]]
To skæringspunkter mellem cirkel og linje.
Hvis [[distance formel|distancen]] mellem centrum og linje er mindre end $r$. Eller:
$\text{dist}(l,c)<r$
3. mulighed
Linje som ligger uden for cirkel.
![[linje uden for cirkel.png]]
Ingen skæringspunkter mellem cirkel og linje.
vis [[distance formel|distancen]] mellem centrum og linje er større end $r$. Eller:
$\text{dist}(l,c)>r$

## udregning af skæringspunkt
man indsætter linjens ligning ind på $y$'s plads i cirklens ligning, og for en andengradsligning. den udregner man så.
$\text{dist}(l,c)$
$c:(x-1)^2+(y-4)^2=50$
$l:4x-2y+4=0$
*isolere y*
$2y=4x+14$
$y=2x+7$
*indsætter på y's plads*
$(x-1)^2+(2x+7-4)^2=50$
*ophæver parenteserne med den anden kvadrat sætning*
$x^2-2x+1+4x^2+9+12x=50$
$x^2-2x+1+4x^2+9+12x-50=0$
$x^2+4x^2+12x-2x+1+9-50=0$
*forkorter*
$\frac{5x^2}{5}+\frac{10x}{5}-\frac{40}{5}=0$
$x^2+2x-8=0$
*løs [[andengradsligninger|andengradligningen]]*
$d=2^2-4\cdot 1\cdot (-8)=36$
$x=\frac{-2\pm\sqrt{36}}{2\cdot1}$
$x=\frac{-2\pm6}{2}=2,-4$
skæringspunktet er $(2,-4)$

# kilde
---
[Cirklens ligning - systime](https://matstxa2.systime.dk/index.php?id=605&L=0)