// 311CD Cotelin Maria-Diana
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"

Tree find(Tree tree, char *manager_name) {
    if( tree == NULL)
        return NULL;
    if (tree->name == manager_name)
        return tree;
    
    for( int i = 0; i< tree->direct_employees_no; i++ ){
        Tree employee = tree->team[i]; 
        Tree found = find(employee, manager_name);
        if( found != NULL)
            return found;
        }
    return NULL;  
}   
/* Adauga un angajat nou in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL, 
           atunci employee_name e primul om din ierarhie.
 */
Tree hire(Tree tree, char *employee_name, char *manager_name) {
    Tree employee = malloc(sizeof(TreeNode));
    employee->name = employee_name;
    employee->direct_employees_no = 0;
    employee->team = NULL;
    int nr;
    int i, j;
    Tree manager;
    if( tree==NULL && manager_name==NULL){
        employee->manager = NULL;
        tree = employee;
        return tree;
    }
    else{
        
        manager = find(tree, manager_name);
        int gasit = 0;
        employee->manager = manager;
        if(manager->direct_employees_no == 0){
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            manager->team = (Tree *)malloc(nr*sizeof(Tree));
            manager->team[0] = employee;  
        }
        else{
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
            manager->team[nr-1] = employee;
        }
        
    }
    Tree temp;
            for (i = 0; i < nr-1; i++)       
                for (j = 0; j < nr-i-1; j++) 
                    if (strcmp(manager->team[j]->name, manager->team[j+1]->name) >0) {
                        temp = manager->team[j];
                        manager->team[j] = manager->team[j+1];
                        manager->team[j+1] = temp;
                    }
    return tree;
}


/* Sterge un angajat din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire(Tree tree, char *employee_name) {
    Tree fired, manager, temp;
    
    fired = find(tree, employee_name);
    if ((fired == NULL) || (tree == fired))
        return tree;
    else{
        int i, nr, j, gasit = 0; 

        manager = fired->manager;
        
        int n=0;
        for( i = 0; i< manager->direct_employees_no && gasit==0; i++ ){
            if(manager->team[i]->name == fired->name ){
                for(j=i; j<manager->direct_employees_no-1; j++)
                    manager->team[j] = manager->team[j+1];
                manager->direct_employees_no--;
                gasit = 1;
            }
        }

        nr = manager->direct_employees_no;
        manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));

        if(fired->direct_employees_no != 0) {
            nr = manager->direct_employees_no + fired->direct_employees_no;
            manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
            for( i = 0; i< fired->direct_employees_no; i++ ) {
                manager->direct_employees_no++;
                nr =  manager->direct_employees_no;
                manager->team[nr-1] = fired->team[i];
                fired->team[i]->manager = manager;
        }
        for (i = 0; i < nr-1; i++)       
            for (j = 0; j < nr-i-1; j++) 
                if (strcmp(manager->team[j]->name, manager->team[j+1]->name) >0) {
                    temp = manager->team[j];
                    manager->team[j] = manager->team[j+1];
                    manager->team[j+1] = temp;
                }
        }
        free(fired->team);
        free(fired);
        return tree;
    }
}

/* Promoveaza un angajat in ierarhie. Verifica faptul ca angajatul e cel putin 
 * pe nivelul 2 pentru a putea efectua operatia.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 *
 * return: intoarce ierarhia modificata.
 */

int level(Tree tree){
    int lvl = 0;
    while(tree!=NULL){
        lvl++;
        tree = tree->manager;
    }
    return lvl;
}

Tree promote(Tree tree, char *employee_name) {
    int lvl, nr, i, j;
    Tree promoted, manager, manager_2, temp;
    promoted = find(tree, employee_name);
    lvl = level(promoted);
    if(lvl <= 2){
        return tree; 
    }
    else {
        manager = promoted->manager;
        manager_2 = manager->manager;
        tree = fire( tree, employee_name);
        tree = hire(tree, employee_name, manager_2->name );
        nr =  manager_2->direct_employees_no;
        for (i = 0; i < nr-1; i++)       
            for (j = 0; j < nr-i-1; j++) 
                if (strcmp(manager_2->team[j]->name, manager_2->team[j+1]->name) >= 0) {
                    temp = manager_2->team[j];
                    manager_2->team[j] = manager_2->team[j+1];
                    manager_2->team[j+1] = temp;
                }
        return tree;
    }
}

/* Muta un angajat in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_employee(Tree tree, char *employee_name, char *new_manager_name) {
    Tree employee_m;
    employee_m = find(tree, employee_name);
    if(( tree->name == employee_name) ||( employee_m->manager->name == new_manager_name))
        return tree;
    else{
        tree = fire(tree, employee_name);
        tree = hire(tree, employee_name, new_manager_name);
        return tree;
    }
}

/* Muta o echipa in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei mutate
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_team(Tree tree, char *employee_name, char *new_manager_name) {
    Tree m_emp, manager, n_manager, temp;
    m_emp = find(tree, employee_name);
    manager = m_emp->manager;
    n_manager = find(tree, new_manager_name);

    int gasit=0, i, j, nr;
    for( i = 0; i< manager->direct_employees_no && gasit==0; i++ ){
        if(manager->team[i]->name == m_emp->name ){
            for(j = i; j<manager->direct_employees_no-1; j++)
                manager->team[j] = manager->team[j+1];
            manager->direct_employees_no--;
            gasit = 1;
        }
    }
    nr = manager->direct_employees_no;
    manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
    
    n_manager->direct_employees_no ++;
    nr = n_manager->direct_employees_no;
    n_manager->team = (Tree *)realloc( n_manager->team, nr*sizeof(Tree));
    n_manager->team[nr-1] = m_emp;
    m_emp->manager = n_manager;

    for (i = 0; i < nr-1; i++)       
        for (j = 0; j < nr-i-1; j++) 
            if (strcmp(n_manager->team[j]->name, n_manager->team[j+1]->name) >0) {
                temp = n_manager->team[j];
                n_manager->team[j] = n_manager->team[j+1];
                n_manager->team[j+1] = temp;
            }
    return tree;
}

/* Concediaza o echipa din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire_team(Tree tree, char *employee_name) {
    Tree fired, manager;
    fired = find(tree, employee_name);
    if(fired == tree)
        return tree;
    else{
        manager = fired->manager;
        int gasit=0, i, j, nr;
        for( i = 0; i< manager->direct_employees_no && gasit==0; i++ ){
            if(manager->team[i]->name == fired->name ){
                for(j=i; j<manager->direct_employees_no-1; j++)
                    manager->team[j] = manager->team[j+1];
                manager->direct_employees_no--;
                gasit = 1;
            }
        }
        nr = manager->direct_employees_no;
        manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
        destroy_tree(fired);
        return tree;
    }
    
}

/* Afiseaza toti angajatii sub conducerea unui angajat.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei
 */
void preorder2(Tree  tree, Tree tree1, Tree tree2){ // tree = pentru numele lui root, tree1 angajatul curent, tree2 noul arbore
    int i;
        hire(tree2, tree1->name, tree->name);
    
    for(i = 0; i<tree1->direct_employees_no; i++){
        preorder2(tree, tree1->team[i], tree2);
        }
}
void get_employees_by_manager(FILE *f, Tree tree, char *employee_name) {

    Tree manager, employee, tree2;
    
    manager = find(tree, employee_name);
    if(manager != NULL){
        tree2 = hire(NULL, manager->name, NULL);
        int i;
        preorder2( manager, manager, tree2);
        
        for(i = 0; i<tree2->direct_employees_no; i++)
            fprintf(f,"%s ", tree2->team[i]->name);
        fprintf(f,"\n");
        destroy_tree(tree2);
    }
    else 
        fprintf(f,"\n");
}

/* Afiseaza toti angajatii de pe un nivel din ierarhie.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * level: nivelul din ierarhie
 */
int level2(Tree tree){
    int lvl = -1;
    Tree aux = tree;
    while(aux != NULL){
        lvl++;
        aux = aux->manager;
    }
    return lvl;
}
void preorder3(Tree  tree, Tree tree1, Tree tree2, int l){ /// tree pentru numele lui root, tree1 angajat actual, tree2 noul arbore
    int i, lvl;
    if(tree1 != NULL){
        lvl = level2(tree1);
        if(lvl == l)
            hire(tree2, tree1->name, tree->name);
        for(i = 0; i<tree1->direct_employees_no; i++){
            preorder3(tree, tree1->team[i], tree2, l);
            }
    }
    else 
        return;
}


void get_employees_by_level(FILE *f, Tree tree, int level) {
    Tree employee = NULL;
    
    if(level >= 0){
        
        employee = hire(NULL, tree->name, NULL);
        preorder3(tree, tree, employee, level);
        int i;
        if(employee->direct_employees_no != 0)
            for(i = 0; i<employee->direct_employees_no; i++)
                fprintf(f,"%s ", employee->team[i]->name);
        fprintf(f,"\n");
        destroy_tree(employee);
    }
    else 
        fprintf(f,"\n");
    
}

/* Afiseaza angajatul cu cei mai multi oameni din echipa.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */

void preorder4(Tree tree1, Tree tree2, int max){ // tree1 angajat actual, tree2 noul arbore
    int i;
    if(tree1 != NULL){
            if(tree1->direct_employees_no == max)
                tree2 = hire(tree2, tree1->name, "manager");
            
        for(i = 0; i<tree1->direct_employees_no; i++){
                preorder4(tree1->team[i], tree2, max);
            }
    }
    else 
      return;
}
int preorder5(Tree tree1){
    int static max = 0;
    int i, max2;
    if(tree1 != NULL){
        if(tree1->direct_employees_no > max){
            max = tree1->direct_employees_no;
        }
        for(i = 0; i<tree1->direct_employees_no; i++){
                max = preorder5(tree1->team[i]);
            }
    }
    max2 = max;
    max = 0;
    return max2;
}
void get_best_manager(FILE *f, Tree tree) {
    Tree tree2;
    int max;
    max = 0;
    tree2 = hire(NULL, "manager", NULL);
    max = preorder5(tree);
    preorder4(tree, tree2, max);
    int i;
    if(tree2->direct_employees_no != 0){
        for(i=0; i<tree2->direct_employees_no; i++)
                fprintf(f, "%s ", tree2->team[i]->name);
        fprintf(f, "\n");
        destroy_tree(tree2);
    }    

    return;
}

/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */
Tree hire2(Tree manager, Tree employee){
    int nr;
        if(manager->direct_employees_no == 0){
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            manager->team = (Tree *)malloc(nr*sizeof(Tree));
            manager->team[0]=employee;  
        }
        else{
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
            manager->team[nr-1] = employee;
        }
        Tree temp;
            for (int i = 0; i < nr-1; i++)       
                for (int j = 0; j < nr-i-1; j++) 
                    if (strcmp(manager->team[j]->name, manager->team[j+1]->name) >0) {
                        temp = manager->team[j];
                        manager->team[j] = manager->team[j+1];
                        manager->team[j+1] = temp;
                    }
        employee->manager = manager;
    return manager;
}
Tree fire2( Tree manager, char* employee_name){
    if (manager->name == employee_name)
        return NULL;
    else{
        int i, j, nr, gasit = 0;
    for( i=0; i< manager->direct_employees_no; i++ ){
        if(strcmp(manager->team[i]->name,employee_name)==0){
            manager->team[i]->manager = NULL;
            for(j=i; j<manager->direct_employees_no-1; j++) {
                manager->team[j] = manager->team[j+1];
            }
            manager->direct_employees_no--;
            break;
        }
    }
    nr = manager->direct_employees_no;
    manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
    return manager;
    }
}
Tree reorganize(Tree tree, char *employee_name) {
    Tree employee, manager, aux, aux2, aux3;
    Tree whereToHire,newToHire,nextManager;
    employee = find(tree, employee_name);

    if((employee == NULL)||(employee == tree)) {
        return tree;
    }
    manager = employee->manager;
    manager = fire2(manager, employee_name);
    employee->manager = NULL;
    
    whereToHire = employee;
    newToHire = manager;        



    while(newToHire->manager != NULL) {
        nextManager = newToHire->manager;
        nextManager = fire2(nextManager,newToHire->name);
        whereToHire = hire2(whereToHire, newToHire);
        whereToHire = newToHire;
        newToHire = nextManager;

    }

    whereToHire = hire2(whereToHire,newToHire);

    return employee;
}

/* Parcurge ierarhia conform parcurgerii preordine.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */

void preorder_traversal(FILE *f, Tree tree) {
    static int n;
    n++;
    if (tree->manager == NULL)
        fprintf(f, "%s ", tree->name);
    else
        fprintf (f, "%s-%s ", tree->name, tree->manager->name);
    
    for( int i=0; i< tree->direct_employees_no; i++ ){
        preorder_traversal(f, tree->team[i]);
    }
    n--;
    if (n==0)
        fprintf(f, "\n");   
    
    //return;
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */
void destroy_tree(Tree tree) {
    int i;
    if(tree != NULL){
        for(i=0; i<tree->direct_employees_no; i++)
            destroy_tree(tree->team[i]);
        free(tree->team);
        free(tree);
    }
    
    return;
}

