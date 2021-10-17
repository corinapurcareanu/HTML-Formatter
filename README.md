# HTML-Formatter
Pentru citirea din fisierul HTML si introducerea informatiei in arbore am facut functia Read. Ea citeste din fisier
litera cu litera, iar cu ajutorul functiei Interpret se genereaza o stare si se adauga informatia in arbore in functie
de starea generata. Nodul este creat atunci cand se citeste primul caracter din numele tag-ului si este adaugat in arbore,
in lista de copii a nodului curent. Nodul curent este adaugat intr-o stiva si apoi nodul curent devine ultimul adaugat. 
Cand se inchide un tag, se scoate ultimul element introdus in stiva si el devine nodul curent. ID-urile sunt setate la 
crearea unui nod, in functie de ID-ul parintelui, ultima cifra fiind al catalea copil este.  

Pentru formatarea corecta a codului HTML am facut functia PrintTree. Ea afiseaza recursiv informatia din arbore, respectand
formatul unui cod HTML.

Pentru adaugarea unui nou tag HTML am creat functia ADD. Ea parcurge arborele pentru a gasi nodul cu ID-ul dat ca parametru
si adauga noul nod la finalul listei sale de copii. Informatia tag-ului este adaugata in arbore la fel ca la functia Read,
folosind functia auxiliara Interpret. 

Pentru suprascris style list-ul unui tag am creat functia overrideStyle. In functie de selectorul dat ca parametru este 
apelata functia auxiliara corespunzatoare. Ele parcurg arborele pana gasesc nodurile care respecta selectorul, ii sterg
vechea lista style si se creeaza alta noua cu informatia data ca parametru acestei functii. Parcurgerea a fost facuta in 
latime cu ajutorul unei cozi.

Pentru actualizat style list-ul unui tag am creat functia appendStyle. In functie de selectorul dat ca parametru este 
apelata functia auxiliara corespunzatoare. Ele parcurg arborele pana gasesc nodurile care respecta selectorul, cauta 
atribute cu numele respectiv dat ca parametru si ii actualizeaza valoarea. Daca nu se gaseste, se adauga atributul 
la finalul listei.  Parcurgerea a fost facuta in latime cu ajutorul unei cozi.

Pentru sters un nod din arbore, am creat functia deleteRecursively. In functie de selectorul dat ca parametru este 
apelata functia auxiliara corespunzatoare. Ele parcurg arborele recursiv pana gasesc nodurile care respecta selectorul,
elimina nodul din lista, refacand legaturile. Ii sterge copiii cu functia Delete, creata pentru a distruge arborele, 
apoi il sterge si pe el.

Stivele si cozile folosite in tema sunt cele date la laborator.

Comenzile sunt primite din fisierul de input, si rezultatul este afisat in fisierul de output, date ca argument la rulare.
