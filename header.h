#ifndef HEADER_H
#define HEADER_H
// Header file contents

struct node {
	float coef;   // coefficient
	char var;	  // variable
	float expo;   // exponential
	struct node* next; // pointer to next term
};


// BASIC UTILITIES
struct node* createNode(float, char, float);
void addNode(struct node*, float, char, float);
void removeNode(struct node*, struct node*);
void mergeSort(struct node*, int, int);
void merge(struct node*, int, int, int);
int countTerms(struct node*);

// TOKEN OR NODES PROCESS METHOD
struct node* multiply(struct node*, struct node*);
struct node* divide(struct node*, struct node*);
struct node* setExponent(struct node*, float);
struct node* add(struct node*, struct node*);
struct node* subtract(struct node*, struct node*);

// MAIN FUNCTIONS
void simplify(struct node*);
void display(struct node*);
void derivative(struct node*);
void integrate(struct node*);
void solve(struct node*);
double computeNode(struct node*, double);

//=========================_BASIC_UTILITIES_===========================//

struct node* final;

struct node* createNode(float coef, char var, float expo){
	struct node* temp = malloc(sizeof(struct node));
	temp->coef = coef;
	temp->var = var;
	temp->expo = expo;
	temp->next = NULL;
	return temp;
};

void addNode(struct node* head, float coef, char var, float expo){
	struct node* newNode = createNode(coef, var, expo);
	struct node* currNode = head;
	while(currNode->next != NULL){
		currNode = currNode->next;
	}
	currNode->next = newNode;
};

// Function to remove a node from a linked list
void removeNode(struct node* head, struct node* nodeToRemove) {
    struct node* currNode = head;

    while (currNode != NULL) {
        if (currNode->next == nodeToRemove) {
            currNode->next = nodeToRemove->next;
            free(nodeToRemove);
            break;
        }
        currNode = currNode->next;
    }
}

// To sort the linked list in descending order
void merge(struct node *head, int l, int m, int h) {
    struct node *curr = head;
    struct node *arrL = createNode(0,'x',0); // m-l+1
    struct node *arrR = createNode(0,'x',0); // h-m

	int t, a;
    for (t = 0; t < l; t++) {
        curr = curr->next;
    }
    for (a = l; a <= m; a++) {
        addNode(arrL, curr->coef, curr->var, curr->expo);
        curr = curr->next;
    }

    for (a = m + 1; a <= h; a++) {
        addNode(arrR, curr->coef, curr->var, curr->expo);
        curr = curr->next;
    }

    int i = 0, j = 0, k = l;
    curr = head;
    for (t = 0; t < l; t++) {
        curr = curr->next;
    }
    arrL = arrL->next;
    arrR = arrR->next;
    while (i < m - l + 1 && j < h - m) {
        if (arrL->expo >= arrR->expo) {
            curr->coef = arrL->coef;
            curr->var = arrL->var;
            curr->expo = arrL->expo;
            i++;
            arrL = arrL->next;
        } else {
            curr->coef = arrR->coef;
            curr->var = arrR->var;
            curr->expo = arrR->expo;
            j++;
            arrR = arrR->next;
        }
        k++;
        curr = curr->next;
    }
    while (i < m - l + 1) {
        curr->coef = arrL->coef;
        curr->var = arrL->var;
        curr->expo = arrL->expo;
        i++;
        arrL = arrL->next;
        k++;
        curr = curr->next;
    }
    while (j < h - m) {
        curr->coef = arrR->coef;
        curr->var = arrR->var;
        curr->expo = arrR->expo;
        j++;
        arrR = arrR->next;
        k++;
        curr = curr->next;
    }
};

void mergeSort(struct node *head, int l, int h) {
    if (l < h) {
        int mid = (l + h) / 2;
        mergeSort(head, l, mid);
        mergeSort(head, mid + 1, h);
        merge(head, l, mid, h);
    }
};

// Count number of terms in given hierarchy
int countTerms(struct node* term){
	struct node* curr = term;
	int num = 0;
	while(curr!=NULL){
		num++;
		curr = curr->next;
	};
	return num;
}



//====================_TOKEN_NODES_PROCESSING_METHOD_=====================//

struct node* setExponent(struct node* f, float n){
	// Initialize nodes with exponents value
	if(f->next == NULL){
		if(f->var == '\0')
			return createNode(pow(f->coef,n),f->var,0);
		else
			return createNode(f->coef, f->var, n);
	}
	// Recursively multiply nodes with exponent expression like (x+1)^2
	else{
		struct node* temp = createNode(0,'x',0);
		struct node* curr = f;
		while(curr != NULL){
			addNode(temp,curr->coef,curr->var,curr->expo);
			curr = curr->next;
		}
		while(n > 1 && floor(n)-n == 0){
			temp->next = multiply(temp->next,f);
			n--;
		}
		return temp->next;
	}
};

struct node* multiply(struct node* a, struct node* b){
	struct node* currNodeA = a;
	struct node* currNodeB = b;
	struct node* newNode = createNode(0,'\0',0);
		while(currNodeA != NULL){
			while(currNodeB != NULL){
				float coef = currNodeA->coef * currNodeB->coef;
				char var = currNodeA->expo != 0 ? currNodeA->var : currNodeB->var;
				float expo = currNodeA->expo + currNodeB->expo;
				addNode(newNode,coef,var,expo);
				currNodeB = currNodeB->next;
			}
			currNodeB = b;
			currNodeA = currNodeA->next;
		}

	return newNode->next;
};

struct node* divide(struct node* a, struct node* b){
	struct node* currNodeA = a;
	struct node* currNodeB = b;
	struct node* newNode = createNode(0,'\0',0);
		while(currNodeA != NULL){
			if (currNodeB != NULL){
				float coef = currNodeA->coef / currNodeB->coef;
				char var = currNodeA->expo != 0 ? currNodeA->var : currNodeB->var;
				float expo = currNodeA->expo - currNodeB->expo;
				addNode(newNode,coef,var,expo);
			}
			currNodeA = currNodeA->next;
		}
	return newNode->next;
};

struct node *add(struct node*a, struct node* b){
	struct node* newNode = createNode(0,'\0',0);
	struct node* currA = a;
	while(currA != NULL){
		addNode(newNode, currA->coef, currA->var, currA->expo);
		currA = currA->next;
	}
	struct node* currB = b;
	while(currB != NULL){
		addNode(newNode, currB->coef, currB->var, currB->expo);
		currB = currB->next;
	}
	return newNode->next;
};

struct node *subtract(struct node*a, struct node* b){
	struct node* newNode = createNode(0,'\0',0);
	struct node* currA = a;
	while(currA != NULL){
		addNode(newNode, currA->coef, currA->var, currA->expo);
		currA = currA->next;
	}
	struct node* currB = b;
	while(currB != NULL){
		addNode(newNode, currB->coef *-1, currB->var, currB->expo);
		currB = currB->next;
	}
	return newNode->next;
};


//=========================_MAIN_FUNCTIONS_============================//

// To display the entire linked list/ equations
void display(struct node* head){
	struct node* term = head;
	
	while(term != NULL){
		if(term->coef != 0){
			if(term->coef != 1.0 || (term->expo == 0 ))
				printf("%.2f",term->coef);
			if(term->var != '\0' && term->expo != 0){
				printf("%c",term->var);
				if(term->expo != 0){
					printf("^%.2f",term->expo);
				}
			}
		}
		// Output zero if it is the only 0 in each hierachy
		if(term->coef == 0 && countTerms(head) < 2 && term->next == NULL)
			printf("%.2f",term->coef);
		if(term->next != NULL && term->next->coef > 0){
			printf(" + ");
		} else if(term->next != NULL && term->next->coef < 0){
			printf(" ");
		}
		
		term = term->next;
	}
}

// A general function to handle simplify process (for addition)
void simplify(struct node *final) {
	
	// Mergesort the exponents in descending orders
	mergeSort(final,0,countTerms(final)-1);

	// Combine all nodes with same exponent
	struct node* current = final;
    while (current != NULL) {
        struct node *prev = current;
        struct node *next = current->next;   
        while (next != NULL) {
            if (current->var == next->var && current->expo == next->expo) {
				current->coef += next->coef;
                prev->next = next->next;
				removeNode(final,next);
				next = prev->next;
            } else {
                prev = next;
                next = next->next;
            }
        }       
        current = current->next;
    }
	
};

void derivative(struct node *equ){
	if (equ == NULL) {
		return;
	}
	derivative(equ->next);
	equ->coef = equ->coef * equ->expo;
	equ->expo--;
}

void integrate(struct node *equ){
	struct node *currNode = equ;
	while(currNode!=NULL){
		currNode->expo++;
		if(currNode->var == '\0') currNode->var = equ->var ;
		currNode->coef = currNode->coef/currNode->expo;
		currNode = currNode->next; 
	};
	addNode(equ,1,'C',1);
};

// Find the result of the polynomial with given value x
double computeNode(struct node* inner, double n){
	double total = 0;
	struct node* curr = inner;
	while(curr != NULL){
		total += curr->coef * pow(n,curr->expo);
		curr = curr->next;
	}
	return total;
}

// Find the solution (root) of the polynomial via formulas
void solve(struct node *f){
	// This solving requires sorted equation
	if(f->expo == 2){
		float a = 0, b = 0, c = 0;
		a = f->coef;
		if(f->next != NULL){
			if(f->next->expo == 1){
				b = f->next->coef;
				c = (f->next->next != NULL) ? f->next->next->coef : 0;
			}else
				c = f->next->coef;
		}
		float x1,x2;
		x1 = ( -1 * b + sqrt( pow(b,2) - 4 * a * c)) / (2 * a);
		x2 = ( -1 * b - sqrt( pow(b,2) - 4 * a * c)) / (2 * a);
		printf("The roots of the equation: %.2f %.2f \n",x1,x2);
		//printf("Compute node: %f\n", computeNode(f,3));
	}else{
	
		// Newton Raphson Method
		struct node* currf = f;
		struct node* df = createNode(0,'x',0); // dummy value
		while(currf != NULL){
			addNode(df,currf->coef,currf->var,currf->expo);
			currf = currf->next;
		}

		derivative(df);
		
		double x1=0, x0 = 1.111; // x0 could be any guess
		double tol = 0.000001;
		double fx, dfx;
		double tri;
		int n = 0, N = 100, solution = 0;
		
		for(n=0; n<N; n++){   
			fx = 0; 
			dfx = 0;
			fx = computeNode(f,x0);
			dfx = computeNode(df,x0);
			
			if(dfx == 0) break;
			x1 = x0 - fx/dfx;
			if(fabs(x1-x0) < tol){  // float absolute
				solution = 1;
				break;
			}
			x0 = x1;
		}

		if(solution)
			printf("The approximate solution of given polynomial is x = %.6f\n",x1);
		else
			printf("The approximate solution after 100 iterations: x = %.6f\n",x1);
	}
};

#endif /* HEADER_H */
