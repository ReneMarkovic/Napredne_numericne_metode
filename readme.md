
# Osnovni opis modela

Pri predmetu napredne numerične metode, ki se izvaja na študiju fizike na Oddelku za fiziko, Fakultete za naravoslovje in matematiko, Univerze v Mariboru, smo pri vajah izdelali model peščenih plazov. Osnovna ideja modela je, da na 2D površino enakomerno pada določena količina peska. Pesek se prenaša po plošči preko plazov, ki se sprežijo, ko je naklon sipine večji od določene mejne vrednosti. V ta namen ustvarimo NxN <b>naklonsko matriko<b> naravnih števil (S). Glede na vrednost, ki jo ij-ti element te matrike zavzema, opredelimo S[i,j] kot: -> stabilen S[i,j]<4 -> nestabilen S[i,j]>=4.

Na začetku lahko elementi matrike zauzemajo vrednost 0 ali pa njihovo vrednost določimo naključno. Nato pričnemo dodajati zrna peska. Če določena celica postane nestabilna uporabimo naslednjo pravilo: 1) s[i,j]=s[i,j]-4 (celici odvzamemo 4 zrna peska in jih porazdelimo med sosednjimi štirimi celicami) s[i+1,j]=s[i+1,j]+1 s[i-1,j]=s[i-,j]+1 s[i,j+1]=s[i,j+1]+1 s[i,j-1]=s[i,j-1]+1 Ko en element matrike postane nestabilen, uporabimo pravilo (1) in usklajeno z drugimi celicami spremljamo kako velik plaz se sproži (število elementov, ki zaradi pravila (1) posatane nestabilno).

# Kako zaženemo program

Datoteka main.py vsebuje ključne parametre, s katerimi nastavljamoi:

|Spremenljivka | Nastavljena vrednost | Pomen |
|--------------|:-----:|-----------:|
|size | 0 | Spremenljivka beleži število celic, po katerih se je razširil plaz. |
|Nx | 51 | Število razdelkov na x osi |
|Ny | 51 | Število razdelkov na y osi |
|TFIN | 5000 | Skupno število |
|Sth | 4 | Mejna vrednost strmine, ki sproži plaz |
|cx | int(Nx/2) | x lega kjer se spuiščajo zrna peska |
|cy | int(Ny/2) | y lega kjer se spuiščajo zrna peska |
|pos | [cx,cy]  | seznam leg, kjer se spuščajo zrna peska |
|st_zrn | 4 | ŠTevilo zrn, ki se na vsako lokacijo spussti v vsaki iteraciji |
|START | int(0.8*TFIN) | Število iteracij, ki se zanemarijo |

# Viri
[1] http://guava.physics.uiuc.edu/~nigel/courses/563/Essays_2012/PDF/banerjee.pdf <br>
[2] http://blairgemmer.com/docs/BakTang/SandpileWriteup.pdf <br>
[3] https://www.youtube.com/watch?v=1MtEUErz7Gg <br>
