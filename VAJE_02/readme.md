# Molekularna dinamika sistema in Blender animacija

## Fizikalni opis sistema

V tej simulaciji modeliramo sistem delcev, ki se med seboj medsebojno privlačijo in odganjajo preko Lennard–Jones potenciala. Delci so inicializirani na enakomerni kubični rešetki, kjer se vsaka pozicija določi s predpisom, ki zagotavlja pravilno razporeditev. Hitrosti delcev se generirajo s pomočjo Box–Muller transformacije, kar omogoča simulacijo normalno porazdeljenih vrednosti. Sistem se termalizira s preprostim termostatom, ki redno skalira hitrosti delcev, tako da se vzdržuje želena (uporabniško določena) temperatura, pri čemer se odstrani tudi skupni (nizek) impulz.

Fizikalni model temelji na klasičnih enačbah gibanja, pri čemer se pozicije in hitrosti posodabljajo z uporabo algoritma velocity Verlet. S tem se zajame kinetična energija sistema, ki je povezana s temperaturo preko enačbe:
  
\[
T = \frac{2K}{3(N-1)}
\]

kjer \( K \) predstavlja skupno kinetično energijo, \( N \) pa število delcev. Sistem se občasno "termalizira", kar pomeni, da se hitrosti delcev enakomerno prilagodijo tako, da sistem doseže in vzdržuje ciljno temperaturo.

## Opis programčkov

### Simulacijska koda (C/C++)

- **Kaj počne:**  
  - Inicializira pozicije in hitrosti delcev.
  - Izračuna medsebojne sile z Lennard–Jones potencialom ter upošteva periodične robne pogoje.
  - Posodablja položaje in hitrosti z uporabo algoritma velocity Verlet.
  - Termalizira sistem s skaliranjem hitrosti, da ohrani določeno temperaturo.
  - Zapiše rezultate (npr. pozicije delcev) v mapo `RESULTS`.

- **Prevajanje in zagon:**  
  Kodo lahko prevedete z uporabo C/C++ prevajalnika (npr. GCC) in jo zaženete z ukazom, kjer podate ciljno temperaturo kot argument (npr. `run.exe 0.01`).

### Batch zagon s Pythonom

- **Kaj počne:**  
  Python skripta omogoča avtomatiziran zagon simulacije pri več različnih temperaturah. Skripta pobriše stare rezultate, ustvari potrebno strukturo map in za vsak parameter temperature pokliče simulacijski program.

### Blender animacija (Python skripta z `bpy`)

- **Kaj počne:**  
  - Očisti Blender sceno (odstrani vse mesh objekte, materiale in kolekcije).
  - Uvozi podatke iz izhodnih datotek simulacije (npr. pozicije delcev).
  - Ustvari žogice (sferične objekte) za vsak delec in jih doda v novo ustvarjeno kolekcijo.
  - Za vsak časovni korak nastavi keyframe-e, s čimer animira gibanje delcev skozi čas.

## Struktura repozitorija
├── main.cpp # Glavna simulacijska koda (C/C++)
├── utils.h # Pomožne funkcije (npr. generacija hitrosti, izračun sil)
├── analiza.py # Skripta za batch zagon simulacij pri različnih temperaturah 
├── aanimacija.py # Blender Python skripta za uvoz podatkov in animacijo delcev
├── RESULTS/ # Mapa, kjer se shranjujejo rezultati simulacije (ustvari se samodejno)
└── README.md # Ta dokument

## Pogoji in navodila

### Za simulacijsko kodo:
- Prevajalnik C/C++ (npr. GCC, MSVC)
- Po želji: CMake

### Za Python skripte:
- Python 3.x s knjižnico NumPy (`pip install numpy`)

### Za Blender animacijo:
- Blender 2.8 ali novejši (z vgrajenim modulom `bpy`)

## Zaključek

Projekt je namenjen izobraževalnemu pregledu osnov molekularne dinamike in animacije rezultatov v Blenderju. Fizikalni model temelji na klasičnih principih, programčka pa so zasnovana tako, da omogočajo enostavno razumevanje in vizualizacijo dinamike delcev. Veseli bomo vaših prispevkov in izboljšav!

## Licenca

Projekt je licenciran pod MIT licenco. Za več informacij glejte datoteko [LICENSE](LICENSE).
