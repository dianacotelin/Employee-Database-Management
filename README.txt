311CD COTELIN DIANA

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-preorder_traversal - folosesc o variabila statica pentru a putea
adauga endline. Daca nodul la care am ajuns are managerul NULL, atunci
e root si il afisez doar pe el, altfel afisez nodul si managerul si reapelez
functia pentru toti angajatii sai.
-destroy_tree - Daca angajatul la care am ajuns nu e NULL, apelez recursiv
functia pentru angajatii sai, iar apoi ii dau free de team si free simplu.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cerinta 1
- find - functie care cauta recursiv un nod intr-un arbore, daca nodul curent
este cel cautat, se returneaza nodul, altfel se verifica si copiii nodului curent.

-hire - aloc spatiu pentru angajatul pe care vreau sa il adaug. Verific daca 
 arborele e null sau managerul e null, in acest caz angajatul devine primul 
 nod din arbore. Altfel, caut cu find nodul manager, ii dau ca manager nodului
angajat nodul manager. Daca managerul nu are alti angajati, ii aloc spatiu 
pentru un angajat si il pun, altfel il pun la final. La final de tot sortez lexico-
grafic toti angajatii.

-fire - verific intai daca nodul pe care vreau sa il sterg exista in arbore sau 
daca este root-ul, daca nu, ii retin managerul. Intai il sterg din vectorul de
angajati ai managerului, apoi ii mut toti angajatii la manager si la final 
sortez lexico-grafic angajatii managerului.

-promote - am facut o functie care numara nivelul unui angajat. Daca nivelul
e mai mic decat 2 returnez arborele initial, altfel retin managerul celui 
promovat si managerul managerului (manager_2). Concediez angajatul care
trebuie promovat si il reangajez la manager_2, iar apoi sortez lexico-grafic 
angajatii lui manager_2.

-move_employee - daca angajatul este root-ul sau noul manager coincide cu cel
vechi, returnez arborele asa cum e, altfel ii dau fire de la angajatorul curent si
hire la cel nou.

-move_team - caut intai angajatul pe care il mut (m_emp) si managerul la care
il mut (n_manager). Il scot pe m_emp din echipa managerului sau nou si il mut
la noul manager. Realoc vectorul de team pentru noul manager si pentru 
vechiul manager. Sortez angajatii noului manager.

-fire_team - gasesc managerul echipei pe care vreau sa o concediez si il scot
 din echipa managerului sau, apoi dau destroy_tree managerului (si implicit
echipei sale).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cerinta 2
-get_employees_by_manager - am folosit o noua functie asemanatoare lui
preorder cu ajutorul careia adaug toti angajatii lui tree intr-un arbore nou, toti
angajatii avandu-l ca manager pe root. In functia get_employees_by_manager
il caut pe manager si apoi daca acesta exista il pun ca nod principal in tree2, 
iar apoi apelez preorder2 pentru a pune in tree2 restul angajatiilor care 
urmeaza dupa el. Afisez apoi toti angajatii lui tree2 si ii dau destroy_tree 
pentru a elibera memoria.

-get_employees_by_level - folosesc o noua functie pentru determinarea nivelului
unui nod si o functie care parcurge toate nodurile (asemanatoare preorder2) si 
pune in tree2 nodurile care au nivelul specificat de functie (l). In functia 
principala creez iar un arbore nou avandu-l ca root pe primul nod din tree. 
Folosesc preorder3 pentru a pune toti angajatii de pe nivelul specificat in noul
arbore, iar apoi ii afisez si distrug arborele.

-get_best_manager - folosesc doua functii preorder, una pentru a determina
numarul maxim de angajatu si cealalta pentru a pune toti angajatii care au
 numarul maxim de subalterni in noul arbore creat. In functia principala creez
noul arbore, apelez cele doua functii si afisez nodurile sale, iar apoi il 
distrug.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cerinta 3
reorganize- gasesc nodul cerut, daca managerul lui este chiar tree le atunci
ii modific managerul in null si pe tree cu toti angajatii sai il pun la
angajatii lui employee folosind doua functii asemanatoare cu fire si hire.
Altfel, parcurg tot arborele initial si fac ca managerul nodului la care
sunt sa ii devina angajat.
