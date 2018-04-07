#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define _ZERO_ CreateNode(NUMBER, NULL, NULL)
#define _ONE_ CreateNode(VAR, NULL, NULL)
#define _TREE_(A, B, C, T) tree = calloc(1, sizeof(struct Node));\
tree->val = calloc(4, sizeof(char));\
tree->val[0] = (A);\
tree->val[1] = (B);\
tree->val[2] = (C);\
tree->val[3] = '\0';\
tree->type = (T);\
tree->left = lf;\
tree->right = rg;\
return tree;
#define _STANDART_OPTIMIZATION_ {\
			root->right = Optimize_One_Zero(root->right, opt_register);\
			root->left = Optimize_One_Zero(root->left, opt_register);\
			return root;\
		}
#define _TRIGONOMETRIC_OPTIMIZATION_ root->right = Optimize_One_Zero(root->right, opt_register);\
		return root;
#define CONST_OPTMIZE(A) { int left = 0;\
int right = 0;\
if(root->left) root->left = Optimize_const(root->left, opt_register);\
	if(root->right) root->right = Optimize_const(root->right, opt_register);\
	if(root->left && root->right)\
	{\
		if(root->left->type == NUMBER && root->right->type == NUMBER)\
		{\
			left = Get_Number(root->left);\
			right = Get_Number(root->right);\
			int sum = left A right;\
			struct Node * tree = Put_Number(sum);\
			root = tree_destroy_optimize(root);\
			(*opt_register)++;\
			return tree;\
		}\
		else \
			return root;\
	}\
	else if(!root->left && root->right)\
	{\
		if(root->right->type == NUMBER)\
		{\
			right = Get_Number(root->right);\
			int sum = left A right;\
			struct Node * tree = Put_Number(sum);\
			root = tree_destroy_optimize(root);\
			(*opt_register)++;\
			return tree;\
		}\
		else \
			return root;\
	}\
	else if(root->left && !root->right)\
	{\
		if(root->left->type == NUMBER)\
		{\
			left = Get_Number(root->left);\
			int sum = left A right;\
			struct Node * tree = Put_Number(sum);\
			root = tree_destroy_optimize(root);\
			(*opt_register)++;\
			return tree;\
		}\
		else \
			return root;\
	}\
	else assert(0);\
}
#define SIN_SH_ATG_OPTIMIZE {\
			assert(root->right);\
			assert(root->right->val);\
			root->right = Optimize_const(root->right, opt_register);\
			assert(root->right);\
			assert(root->right->val);\
			if(root->right->val[0] == '0' && (root->right->val[1] == ' ' || root->right->val[1] == '\0'))\
			{\
				struct Node * tree = root->right; \
				root->right = NULL;\
				root = tree_destroy_optimize(root);\
				(*opt_register)++;\
				return tree;\
			}\
			else return root;\
		}
#define COS_CH_OPTIMIZE {\
			assert(root->right);\
			assert(root->right->val);\
			root->right = Optimize_const(root->right, opt_register);\
			assert(root->right);\
			assert(root->right->val);\
			if(root->right->val[0] == '0' && (root->right->val[1] == ' ' || root->right->val[1] == '\0'))\
			{\
				struct Node * tree = _ONE_;\
				root = tree_destroy_optimize(root);\
				(*opt_register)++;\
				return tree;\
			}\
			else return root;\
		}
#define _CONST_OPTIMIZE_STANDART_ {\
			root->right = Optimize_const(root->right, opt_register);\
			root->left = Optimize_const(root->left, opt_register);\
			return root;\
}

enum Token {
	NUMBER,
	VAR,
	PLUS,
	MINUS,
	MULT,
	DIVIDE,
	POW,
	LOG,
	SIN,
	COS,
	SH,
	CH,
	ATG
};

struct Node
{
	char * val;
	int type;
	struct Node * left;
	struct Node * right;
};

void arr_fill(char * array, FILE * stream, int * number);													//Функции, которые остались от акинатора и нужны для заполнения исходного дерева.
void arr_slash(char * array, int * number);																		//Всего их 9 штук.
struct Node * tree_fill(struct Node * root, char * array, int * number);
struct Node * tree_add_preparation(struct Node * root, char * array, int * depth);
void tree_add(struct Node * root, int * depth, int * count, char * array, int * count_2);
int tab_count(const char * array);
char * spaces(char * array);
int point_finder(char * array);
int type_determinant(char * array);	

struct Node * Diff(const struct Node * root);
struct Node * CreateNode(int fella, struct Node * lf, struct Node * rg);
struct Node * Copy(const struct Node * root);
struct Node * Optimize(struct Node * root);
struct Node * Optimize_One_Zero(struct Node * root, int * opt_register);
struct Node * Optimize_const(struct Node * root, int * opt_register);
int Get_Number(const struct Node * root);
struct Node * Put_Number(int number);

void tree_destroy(struct Node * root);
void tree_destroy_diff(struct Node * root);
struct Node * tree_destroy_optimize(struct Node * root);

void tree_png(struct Node * root, FILE * stream, int lab, int * lab_count);
void digraph(FILE * stream, int * label);

int main()
{
	FILE * f_in= NULL;
	FILE * f_out_1 = NULL;
	FILE * f_out_2 = NULL;
	FILE * f_out_3 = NULL;
	char strings[1000] = {0};
	char * c = calloc(1, sizeof(char));
	int * n = calloc(1, sizeof(char));
	int * num = calloc(1, sizeof(int));
	struct Node * tree = NULL;
	struct Node * tree_diff = NULL;
	int lab = 0;
	int * lab_count = calloc(1,sizeof(int));
	f_in = fopen("strings", "r");
	f_out_1 = fopen("Tree1.dot", "w");
	f_out_2 = fopen("Tree2.dot", "w");
	f_out_3 = fopen("Tree3.dot", "w");
	assert(f_in);
	assert(f_out_1);
	assert(f_out_2);
	assert(f_out_3);
	arr_fill(strings, f_in, num);
	arr_slash(strings, num);
	tree = tree_fill(tree, strings, num);
	assert(tree);
	tree_diff = Diff(tree);
	digraph(f_out_1, lab_count);
	tree_png(tree, f_out_1, lab, lab_count);
	digraph(f_out_1, lab_count);
	digraph(f_out_2, lab_count);
	tree_png(tree_diff, f_out_2, lab, lab_count);
	digraph(f_out_2, lab_count);
	tree_diff = Optimize(tree_diff);
	digraph(f_out_3, lab_count);
	tree_png(tree_diff, f_out_3, lab, lab_count);
	digraph(f_out_3, lab_count);
	free(c);
	free(n);
	free(num);
	tree_destroy_diff(tree_diff);
	tree_destroy(tree);
	free(lab_count);
	fclose(f_in);
	fclose(f_out_1);
	fclose(f_out_2);
	fclose(f_out_3);
	system("dot -Tpng Tree1.dot -o Tree1.png");
	system("dot -Tpng Tree2.dot -o Tree2.png");
	system("dot -Tpng Tree3.dot -o Tree3.png");
	return 0;
}

int type_determinant(char * array) {
	int type = 0;
	if(array[1] == 'x') type = VAR;
	else if(array[1] == '+') type = PLUS;
	else if(array[1] == '-') type = MINUS;
	else if(array[1] == '*') type = MULT;
	else if(array[1] == '/') type = DIVIDE;
	else if(array[1] == '^') type = POW;
	else if(array[1] == 'l') type = LOG;
	else if(array[1] == 'a') type = ATG;
	else if (array[1] == 's') {
		if(array[2] == 'i') type = SIN;
		else if(array[2] == 'h') type = SH;
	}
	else if (array[1] == 'c') {
		if(array[2] == 'o') type = COS;
		else if(array[2] == 'h') type = CH;
	}
	else type = NUMBER;
	return type;
}

void arr_fill(char * array, FILE * stream, int * number)
{
	assert(array);
	assert(stream);
	int counter = 0;
	int c = 0;
	for(; ; counter++)
	{
		c = fgetc(stream);
		if(c == EOF) break;
		array[counter] = c;
	}
	*number = counter;
}

void arr_slash(char * array, int * number)
{
	assert(array);
	assert(number);
	int counter = 0;
	for(; counter < *number; counter++)
	{
		if(array[counter] == '!')
		{
			array[counter] = '\0';
		}
	}
	array[counter + 1] = '\0';
}

struct Node * tree_fill(struct Node * root, char  * array, int * number)
{
	int counter = 0;
	int * depth = calloc(1, sizeof(int));
	for(; counter < *number; counter++)
	{
		if(array[counter] == '\0')
		{
			counter++;
			root = tree_add_preparation(root, array + counter, depth);
			assert(root);
		}
	}
	free(depth);
	return root;
}

struct Node * tree_add_preparation(struct Node * root, char * array, int * depth)
{
	assert(array);
	if(root == NULL)
	{
		root = calloc(1, sizeof(struct Node));
		root->val = (array + 1);
		root->type = type_determinant(array);
		return root;
	}
	int * count = calloc(1, sizeof(int));
	int * count_2 = calloc(1, sizeof(int));
	*depth = tab_count(array);
	if(*depth) tree_add(root, depth, count, array, count_2);
	free(count);
	free(count_2);
	return root;
}

void tree_add(struct Node * root, int * depth, int * count, char * array, int * count_2)
{
	assert(depth && count);
	if(*count < (*depth - 1) && root)
	{
		(*count)++;
		tree_add(root->right, depth, count, array, count_2);
		tree_add(root->left, depth, count, array, count_2);
		(*count)--;
	}	
	if(root)
	{
		if((*count == (*depth - 1)) && (!root->right || !root->left) && (root) && !(*count_2))
		{
			(*count_2)++;
			array = spaces(array);
			assert(array[0] == '(' || array[0] == ')' || array[0] == '\0');
			if(!point_finder(root->val))
			{
				if(array[0] == '(') 
				{
					assert(!root->right);
					root->right = calloc(1, sizeof(struct Node));
					root->right->val = (array + 1);
					root->right->type = type_determinant(array);
				}
				else if(array[0] == ')')
				{
					assert(!root->left);
					root->left = calloc(1, sizeof(struct Node));
					root->left->val = (array + 1);
					root->left->type = type_determinant(array);
				}
			}
			else
				(*count_2)--;
		}
	}
}

int tab_count(const char * array)
{
	assert(array);
	int counter = 0;
	int depth = 0;
	for(; array[counter] != '\0'; counter++)
	{
		if(array[counter] == '\t') 
		{	
			depth++;
		}
	}
	return depth;
}

char * spaces(char * array)
{
	assert(array);
	int counter = 0;
	int space = 0;
	for(; array[counter] != '\0'; counter++)
	{
		if(array[counter] == '\t' || array[counter] == '\n')
		{
			space++;
		}
	}
	return (array + space);
}

int point_finder(char * array)
{
	assert(array);
	int counter = 0;
	int i = 0;
	for(i = 0; array[i] != '\0'; i++)
	{
		if(array[i] == ' ') counter++;
	}
	return counter;
}

void tree_png(struct Node * root, FILE * stream, int lab, int * lab_count)
{
	assert(stream);
	if(root) 
	{
		fprintf(stream, "n%03d ", lab);
		fprintf(stream, "[label=\"%s\"] ;\n", root->val);
		assert(lab < 990 && (*lab_count) < 990);
		if(root->left) fprintf(stream, "n%03d -> n%03d;\n", lab, (lab + 1));
		(*lab_count)++;
		tree_png(root->left, stream, (lab + 1), lab_count);
		assert(lab < 990 && (*lab_count) < 990);
		if(root->right) fprintf(stream, "n%03d -> n%03d;\n", lab, (*lab_count));
		tree_png(root->right, stream, *lab_count, lab_count);
	}
}

struct Node * Diff(const struct Node * root)
{
	switch(root->type)
	{
		case NUMBER: return _ZERO_ ;
		case VAR: return _ONE_ ;
		case PLUS: return CreateNode(PLUS, Diff(root->left), Diff(root->right));
		case MINUS: return CreateNode(MINUS, Diff(root->left), Diff(root->right));
		case MULT: 
		{
			struct Node * f_factor = CreateNode(MULT, Diff(root->left), Copy(root->right));
			struct Node * s_factor = CreateNode(MULT, Copy(root->left), Diff(root->right));
			return CreateNode(PLUS, f_factor, s_factor);
		}
		case DIVIDE:
		{
			struct Node * du = Diff(root->left);
			struct Node * dv = Diff(root->right);
			struct Node * u = Copy(root->left);
			struct Node * v = Copy(root->right);
			struct Node * nom = CreateNode(MINUS, CreateNode(MULT, du, v), CreateNode(MULT, u, dv));
			struct Node * denom = CreateNode(MULT, Copy(v), Copy(v));
			return CreateNode(DIVIDE, nom, denom);
		}
		case POW:
		{
			struct Node * u = Copy(root->left); 
			struct Node * v = Copy(root->right);			//u^v
			struct Node * exp = _ZERO_ ;
			exp->val[0] = 'e';
			struct Node * first_factor = CreateNode(POW, u, CreateNode(MINUS, v, _ONE_));
			struct Node * second_factor_2 = CreateNode(MULT, Copy(root->left), CreateNode(MULT, CreateNode(LOG, exp, Copy(root->left)), Diff(root->right)));
			struct Node * second_factor_1 = CreateNode(MULT, Copy(root->right), Diff(root->left));
			return CreateNode(MULT, first_factor, CreateNode(PLUS, second_factor_1, second_factor_2));
		}
		case LOG:
		{
			struct Node * fd = Copy(root->left);
			struct Node * u = Copy(root->right);			//log[fd, u];
			struct Node * exp = _ZERO_ ;
			exp->val[0] = 'e';
			struct Node * den = CreateNode(MULT, CreateNode(LOG, exp, fd), u);
			return CreateNode(DIVIDE, Diff(root->right), den);
		}
		case SIN:
		{
			struct Node * a = Copy(root->right);		//sin(a)
			struct Node * cos = CreateNode(COS, NULL, a);
			return CreateNode(MULT, cos, Diff(root->right));
		}
		case COS:
		{
			struct Node * first_factor = CreateNode(MINUS, _ZERO_, CreateNode(SIN, NULL, Copy(root->right)));
			struct Node * second_factor = Diff(root->right);
			return CreateNode(MULT, first_factor, second_factor);
		}
		case SH:
		{
			return CreateNode(MULT, CreateNode(CH, NULL, Copy(root->right)), Diff(root->right));
		}
		case CH:
		{
			return CreateNode(MULT, CreateNode(SH, NULL, Copy(root->right)), Diff(root->right));
		}
		case ATG:
		{
			struct Node * division = CreateNode(DIVIDE, _ONE_, CreateNode(PLUS, _ONE_, CreateNode(MULT, Copy(root->right), Copy(root->right))));
			return CreateNode(MULT, division, Diff(root->right));
		}
		default: printf("Wrong type");
		assert(0);
	}
	return NULL;
}

struct Node * CreateNode(int fella, struct Node * lf, struct Node * rg)
{
	switch(fella)
	{
		struct Node * tree = NULL;
		case NUMBER:
			_TREE_('0', '\0', '\0', NUMBER)
		case VAR:
			_TREE_('1', '\0', '\0', NUMBER)
		case PLUS:
			_TREE_('+', '\0', '\0', PLUS)
		case MINUS:
			_TREE_('-', '\0', '\0', MINUS)
		case MULT:
			_TREE_('*', '\0', '\0', MULT)
		case DIVIDE:
			_TREE_('/', '\0', '\0', DIVIDE)
		case POW:
			_TREE_('^', '\0', '\0', POW)
		case LOG:
			_TREE_('l', 'o', 'g', LOG)
		case COS:
			_TREE_('c', 'o', 's', COS)
		case SIN:
			_TREE_('s', 'i', 'n', SIN)
		case CH:
			_TREE_('c', 'h', '\0', CH)
		case SH:
			_TREE_('s', 'h', '\0', SH)
		default: printf("Wrong Type");
		assert(0);
	}
	return NULL;
}

struct Node * Optimize(struct Node * root)
{
	int i = 0;
	int * opt_register = calloc(1, sizeof(int));
	do
	{
		(*opt_register) = 0;
		root = Optimize_One_Zero(root, opt_register);
		root = Optimize_const(root, opt_register);
		i++;
	}
	while((*opt_register));
	free(opt_register);
	return root;
}

struct Node * Optimize_One_Zero(struct Node * root, int * opt_register)
{
	assert(opt_register);
	if(!root) return NULL;
	assert(root->type <= 12);
	switch(root->type)
	{
		case NUMBER: return root;
		case VAR: return root;
		case SIN: _TRIGONOMETRIC_OPTIMIZATION_
		case COS: _TRIGONOMETRIC_OPTIMIZATION_
		case SH: _TRIGONOMETRIC_OPTIMIZATION_
		case CH: _TRIGONOMETRIC_OPTIMIZATION_
		case POW: _STANDART_OPTIMIZATION_
		case LOG: _STANDART_OPTIMIZATION_
		case DIVIDE: _STANDART_OPTIMIZATION_
		case ATG: _TRIGONOMETRIC_OPTIMIZATION_
		case MINUS: _STANDART_OPTIMIZATION_
		case PLUS:
		{
			if(!root->right && !root->left)
			{
				assert(root->val);
				root = tree_destroy_optimize(root);
				struct Node * tree = calloc(1, sizeof(struct Node));
				tree->val = calloc(2, sizeof(char));
				tree->val[0] = '0';
				tree->val[1] = '\0';
				tree->type = NUMBER;
				(*opt_register)++;
				return tree;
			}
			assert(root->right || root->left);
			if(root->right)
			{
				assert(root->right->val);
				if(!root->left)
				{
					struct Node * u = root->right;
					root->right = NULL;
					root = tree_destroy_optimize(root);
					(*opt_register)++;
					return u;
				}
				else if (root->right->val[0] == '0')
				{
					(*opt_register)++;
					root->right = tree_destroy_optimize(root->right);
				}
				else root->right = Optimize_One_Zero(root->right, opt_register);
			}
			if(root->left)
			{
				assert(root->left->val);
				if(!root->right)
				{
					struct Node * u = root->left;
					root->left = NULL;
					root = tree_destroy_optimize(root);
					(*opt_register)++;
					return u;
				}
				else if(root->left->val[0] == '0')
				{
					(*opt_register)++;
					root->left = tree_destroy_optimize(root->left);
				}
				else root->left = Optimize_One_Zero(root->left, opt_register);
			}
			return root;
		}
		case MULT:
		{
			assert(root);
			assert(root->right || root->left);
			if(root->right)
			{
				assert(root->right->val);
				if(!root->left)
				{
					struct Node * u = root->right;
					root->right = NULL;
					root = tree_destroy_optimize(root);
					(*opt_register)++;
					return u;
				}
				else
				{ 
					assert(root->right->val);
					if(root->right->val[0] == '0')
					{
						(*opt_register)++;
						root->right = tree_destroy_optimize(root->right);
						if(root->left) root->left = tree_destroy_optimize(root->left);
						struct Node * tree = calloc(1, sizeof(struct Node));
						tree->val = calloc(2, sizeof(char));
						tree->val[0] = '0';
						tree->val[1] = '\0';
						tree->type = NUMBER;
						root = tree_destroy_optimize(root);
						return tree;
					}
					else if(root->right->val[0] == '1' && root->right->val[1] == '\0')
					{
						(*opt_register)++;
						root->right = tree_destroy_optimize(root->right);
					}
					else root->right = Optimize_One_Zero(root->right, opt_register);
				}
			}
			if(root->left)
			{
				assert(root->left->val);
				if(!root->right)
				{
					struct Node * u = root->left;
					root->left = NULL;
					root = tree_destroy_optimize(root);
					(*opt_register)++;
					return u;
				}
				else
				{
					if(root->left->val[0] == '0')
					{
						(*opt_register)++;
						root->left = tree_destroy_optimize(root->left);
						if(root->right) root->right = tree_destroy_optimize(root->right);
						struct Node * tree = calloc(1, sizeof(struct Node));
						tree->val = calloc(2, sizeof(char));
						tree->val[0] = '0';
						tree->val[1] = '\0';
						tree->type = NUMBER;
						root = tree_destroy_optimize(root);
						return tree;
					}
					else if(root->left->val[0] == '1' && root->left->val[1] == '\0')
					{
						(*opt_register)++;
						root->left = tree_destroy_optimize(root->left);
					}
					else
						root->left = Optimize_One_Zero(root->left, opt_register);
					}
			}
			return root;
		}
		default: printf("Wrong Type! Type is %d\n", root->type);
		assert(0);
	}
}

struct Node * Optimize_const(struct Node * root, int * opt_register)
{
	assert(root);
	assert(opt_register);
	assert(root->type <= 12);
	switch(root->type)
	{
		case NUMBER:
		{
			return root;
		}
		case VAR:
		{
			return root;
		}
		case PLUS: CONST_OPTMIZE(+)
		case MINUS: CONST_OPTMIZE(-)
		case MULT: 
		{
			int left = 0;
			int right = 0;
			if(root->left) root->left = Optimize_const(root->left, opt_register);
			if(root->right) root->right = Optimize_const(root->right, opt_register);
			if(root->left && root->right)
			{
				if(root->left->type == NUMBER && root->right->type == NUMBER)
				{
					left = Get_Number(root->left);
					right = Get_Number(root->right);
					int sum = left * right;
					struct Node * tree = Put_Number(sum);
					root = tree_destroy_optimize(root);
					(*opt_register)++;
					return tree;
				}
				else return root;
			}
			else if (!root->left || !root->right)
			{
				if(!root->left && root->right)
				{
					if(root->right->type == NUMBER)
					{
						right = Get_Number(root->right); 
						struct Node * tree = Put_Number(right);
						root = tree_destroy_optimize(root);
						(*opt_register)++;
						return tree;
					}
					else
					{
						struct Node * tree = Copy(root->right);
						root->right = NULL;
						(*opt_register)++;
						return tree;
					}
				}
				else if(!root->right && root->left)
				{
					if(root->left->type == NUMBER)
					{
						left = Get_Number(root->left); 
						struct Node * tree = Put_Number(left);
						root = tree_destroy_optimize(root);
						(*opt_register)++;
						return tree;
					}
					else
					{
						struct Node * tree = Copy(root->left);
						root->left = NULL;
						(*opt_register)++;
						return tree;
					}
				}
				else assert(0);
			}
		}
		case SIN: SIN_SH_ATG_OPTIMIZE
		case SH: SIN_SH_ATG_OPTIMIZE
		case ATG: SIN_SH_ATG_OPTIMIZE
		case COS: COS_CH_OPTIMIZE
		case CH: COS_CH_OPTIMIZE
		case DIVIDE: _CONST_OPTIMIZE_STANDART_
		case POW: _CONST_OPTIMIZE_STANDART_
		case LOG: _CONST_OPTIMIZE_STANDART_
	}
	assert(0);
}

int Get_Number(const struct Node * root)
{
	assert(root);
	assert(root->val);
	return atoi(root->val);
}

struct Node * Put_Number(int number)
{
	int value = number;
	int p = 0;
	int counter = 0;
	int p_0 = 0;
	struct Node * tree = calloc(1, sizeof(struct Node));
	tree->val = calloc(12, sizeof(char));
	tree->type = NUMBER;
	if(number < 0)
	{
		tree->val[p] = '-';
		p++;
		number = -number;
	}
	while(value != 0)
	{
		value = value / 10;
		counter++;
	}
	if(counter == 0) 
	{
		tree->val[p] = '0';
		p++;
	}
	else
	{
		p_0 = counter;
		for( ; counter >= 1; counter--)
		{
			tree->val[p + counter - 1] = (number % 10) + '0';
			number /= 10;
		}
	}
	tree->val[p+p_0] = '\0';
	return tree;
}

struct Node * Copy(const struct Node * root)
{
	if(root)
	{
		struct Node * tree = calloc(1, sizeof(struct Node));
		tree->val = calloc(10, sizeof(char));
		tree->val = strncpy(tree->val, root->val, 10);
		tree->type = root->type;
		tree->left = Copy(root->left);
		tree->right = Copy(root->right);
		return tree;
	}
	return NULL;
}

void digraph(FILE * stream, int * label)
{
	assert(label);
	if(!(*label)) {
		fprintf(stream, "digraph G{\n");
		fprintf(stream, "node [style=filled, color=azure3];\n");
	}
	else {
		fprintf(stream,"}\n");
		(*label) = 0;
	}
}

void tree_destroy(struct Node * root)
{
	if(root)
    {
		tree_destroy(root->left);
		tree_destroy(root->right);
		free(root);
    }
}

void tree_destroy_diff(struct Node * root)
{
	if(root)
	{
		tree_destroy_diff(root->left);
		tree_destroy_diff(root->right);
		free(root->val);
		free(root);
	}
}

struct Node * tree_destroy_optimize(struct Node * root)
{
	if(root)
	{
		tree_destroy_diff(root->left);
		tree_destroy_diff(root->right);
		if(root->val) free(root->val);
		free(root);
	}
	return NULL;
}
