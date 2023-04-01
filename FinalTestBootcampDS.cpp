#include <stdio.h> // BeeAero Database System
#include <stdlib.h>
#include <string.h>

struct Planet{
	char name[100];
	double temperature;
	int height;
	
	Planet *left;
	Planet *right;
};

Planet *createPlanet(char name[], double temperature){
	Planet *newPlanet = (Planet*) malloc(sizeof(Planet));
	
	newPlanet->temperature = temperature;
	strcpy(newPlanet->name, name);
	newPlanet->height = 1;
	newPlanet->left = NULL;
	newPlanet->right = NULL;
	
	return newPlanet;
}

int greatest(int x, int y){
	if(x > y){
		return x;
	}
	else{
		return y;
	}
}

int height(Planet *root){
	return (root == NULL) ? 0 : root->height;
}

int bf(Planet *p){
	return (p == NULL) ? 0 : height(p->left)-height(p->right);
}

Planet *rightRtt(Planet *p){
	Planet *a = p->left;
	Planet *b = a->right;
	a->right = p;
	p->left = b;
	
	p->height = greatest(height(p->left), height(p->right))+1;
	a->height = greatest(height(a->left), height(a->right))+1;
	
	return a;
}

Planet *leftRtt(Planet *p){
	Planet *a = p->right;
	Planet *b = a->left;
	a->left = p;
	p->right = b;
	
	p->height = greatest(height(p->left), height(p->right))+1;
	a->height = greatest(height(a->left), height(a->right))+1;
	
	return a;
}

Planet *insert(Planet *planet, double temperature){
	if(planet == NULL){
		return planet;
	}
	
	if(temperature < planet->temperature){
		planet->left = insert(planet->left, temperature);
	}
	else if(temperature > planet->temperature){
		planet->right = insert(planet->right, temperature);
	}
	else{
		return planet;
	}
	
	planet->height = greatest(height(planet->left), height(planet->right))+1;
	
	int blnc = bf(planet);
	
	if(blnc > 1 && temperature < planet->left->temperature){
		return rightRtt(planet);
	}
	if(blnc < -1 && temperature > planet->right->temperature){
		return leftRtt(planet);
	}
	if(blnc > 1 && temperature > planet->left->temperature){
		planet->left = leftRtt(planet->left);
		return rightRtt(planet);
	}
	if(blnc < -1 && temperature < planet->right->temperature){
		planet->right = rightRtt(planet->right);
		return leftRtt(planet);
	}
	
	return planet;
}

void show(Planet *asteroid){
	if(asteroid != NULL){
		printf("%d\n", asteroid->temperature);
		show(asteroid->left);
		show(asteroid->right);
	}
	else{
		printf("no planet here...");
	}
	getchar();
}

void menu(){
	puts("BeeAero Database System");
	puts("=====================================");
	puts("1. Insert new planet/asteroid");
	puts("2. Delete planet/asteroid");
	puts("3. Find similiar planet/asteroid");
	puts("4. Show planet/asteroid");
	printf(">> ");
}

int main(){
	
	int in = 0;
	
	while(in < 1 || in > 4){
		menu();
		scanf("%d", &in); getchar();
		
		struct Planet *asteroid = NULL;
		
		if(in == 1){
			double temp = 0;
			
			printf("Input temperature: ");
			scanf("%lf", &temp);
			
			asteroid = insert(asteroid, temp);
			
			printf("Planet has been successfully added! "); getchar();
		}
			
		else if(in == 2){
				
		}
				
		else if(in == 3){
				
		}
				
		else if(in == 4){
			show(asteroid);
		}
		
	}
	
	return 0;
}
