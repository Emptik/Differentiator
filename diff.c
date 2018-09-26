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
			root = tree_destroy(root);\
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
			root = tree_destroy(root);\
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
			root = tree_destroy(root);\
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
				root = tree_destroy(root);\
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
				root = tree_destroy(root);\
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
#define _LEFT_CONDITION_ if(root->left->type == NUMBER || root->left->type == MINUS || root->left->type == PLUS || root->left->type == VAR)
#define _RIGHT_CONDITION_ if(root->right->type == NUMBER || root->right->type == MINUS || root->right->type == PLUS || root->right->type == VAR)

char * s;
int p;
int check_bracket;

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

struct Node * G(char * str);
struct Node * GetE();
struct Node * GetT();
struct Node * GetPow();
struct Node * GetP();
struct Node * GetSin();
struct Node * GetCos();
struct Node * GetSh();
struct Node * GetCh();
struct Node * GetLog();
struct Node * GetAtg();
struct Node * GetN();
struct Node * GetVar();
void user_helper();

struct Node * Diff(const struct Node * root);
struct Node * CreateNode(int fella, struct Node * lf, struct Node * rg);
struct Node * Copy(const struct Node * root);
struct Node * Optimize(struct Node * root);
struct Node * Optimize_One_Zero(struct Node * root, int * opt_register);
struct Node * Optimize_const(struct Node * root, int * opt_register);
int Get_Number(const struct Node * root);
struct Node * Put_Number(int number);

void Dot_print(struct Node * root, FILE * stream, int lab, int * lab_count);
void tree_png(struct Node * root, FILE * stream, int lab, int * lab_count);
void digraph(FILE * stream, int * lab_count);
void Tex(FILE * stream, const struct Node * root, int bull);
void Tex_make(FILE * stream, const struct Node * root);

struct Node * tree_destroy(struct Node * root);

int main()
{
	FILE * f_in = stdin;
	FILE * f_out_1 = NULL;
	FILE * f_out_2 = NULL;
	FILE * f_out_3 = NULL;
	FILE * f_out_tex = NULL;
	char string[1000] = {0};
	struct Node * tree = NULL;
	struct Node * tree_diff = NULL;
	int lab = 0;
	int * lab_count = calloc(1,sizeof(int));
	f_out_1 = fopen("Tree1.dot", "w");
	f_out_2 = fopen("Tree2.dot", "w");
	f_out_3 = fopen("Tree3.dot", "w");
	f_out_tex = fopen("Texmake.tex", "w");
	assert(f_out_1);
	assert(f_out_2);
	assert(f_out_3);
	assert(f_out_tex);
	fgets(string, 1000, f_in);
	tree = G(string);
	assert(tree);
	tree_diff = Diff(tree);
	assert(tree_diff);
	Dot_print(tree, f_out_1, lab, lab_count);
	Dot_print(tree_diff, f_out_2, lab, lab_count);
	tree_diff = Optimize(tree_diff);
	assert(tree_diff);
	Dot_print(tree_diff, f_out_3, lab, lab_count);
	Tex(f_out_tex, tree, 1);
	Tex(f_out_tex, tree_diff, 0);
	tree = tree_destroy(tree);
	tree_diff = tree_destroy(tree_diff);
	free(lab_count);
	fclose(f_out_1);
	fclose(f_out_2);
	fclose(f_out_3);
	fclose(f_out_tex);
	system("dot -Tpng Tree1.dot -o Tree1.png");
	system("dot -Tpng Tree2.dot -o Tree2.png");
	system("dot -Tpng Tree3.dot -o Tree3.png");
	system("pdflatex Texmake > Texmake_console");
	return 0;
}

struct Node * G(char * str)
{
	s = str;
	p = 0;
	struct Node * root = NULL;
	root = GetE();
	assert(s[p] == '\n');
	return root;
}

struct Node * GetE()
{
	struct Node * root_left = NULL;
	 root_left = GetT();
	 if(!root_left) assert(0);
	int counter = 0;
	struct Node * root = NULL;
	if( s[p] == '+' || s[p] == '-')
	{
		char operator = s[p];
		p++;
		assert(0);
		struct Node * root_right = GetE();
		if(!root_right)
		{
			printf("I need a subtrahend or a second term\n");
			abort();
		}
		if( operator == '+') 
		{
			root = CreateNode(PLUS, root_left, root_right);
			counter++;
		}
		else if( operator == '-')
		{
			root = CreateNode(MINUS, root_left, root_right);
			counter++;
		}
		assert(counter);
	}
	else
	{
		root = root_left;
	}
	return root;
}

struct Node * GetT()
{
	struct Node * root_left = NULL;
	root_left = GetPow();
	if(!root_left) assert(0);
	int counter = 0;
	struct Node * root = NULL;
	if( s[p] == '*' || s[p] == '/')
	{
		char operator = s[p];
		p++;
		struct Node * root_right = GetPow();
		if(!root_right)
		{
			printf("I need a divider or a second factor\n");
			abort();
		}
		if( operator == '*') 
		{
			if(!check_bracket)
			{
				printf("Try to use a such kind of expression: '(EXPRESSION*EXPRESSION)'\n");
				abort();
			}
			root = CreateNode(MULT, root_left, root_right);
			counter++;
		}
		else if( operator == '/')
		{
			if(!check_bracket)
			{
				printf("Try to use a such kind of expression: '(EXPRESSION/EXPRESSION)'\n");
				abort();
			}
			root = CreateNode(DIVIDE, root_left, root_right);
			counter++;
		}
		assert(counter);
	}
	else
	{
		root = root_left;
	}
	return root;
}

struct Node * GetPow()
{
	struct Node * root_left = NULL;
	root_left = GetP();
	if(!root_left) assert(0);
	int counter = 0;
	struct Node * root = NULL;
	if( s[p] == '^')
	{
		char operator = s[p];
		p++;
		struct Node * root_right = GetP();
		if(!root_right)
		{
			printf("I need a degree\n");
			abort();
		}
		if( operator == '^') 
		{
			if(!check_bracket)
			{
				printf("Try to use a such kind of expression: '(EXPRESSION^EXPRESSION)'\n");
				abort();
			}
			root = CreateNode(POW, root_left, root_right);
			counter++;
		}
		assert(counter);
	}
	else
	{
		root = root_left;
	}
	return root;
}

struct Node * GetP()
{
	if(s[p] == '(')
	{
		p++;
		check_bracket++;
		struct Node * root = GetE();
		if(s[p] != ')')
		{
			user_helper();
			printf("Each opening bracket must have an ending bracket\n");
			abort();
		}
		check_bracket--;
		p++;
		return root;
	}
	else if(s[p] == 's' && s[p+1] == 'i' && s[p+2] == 'n')
		return GetSin();
	else if(s[p] == 'x' || s[p] == 'X') 
		return GetVar();
	else if(s[p] == 'l' && s[p+1] == 'o' && s[p+2] == 'g')
		return GetLog();
	else if(s[p] == 'c' && s[p+1] == 'o' && s[p+2] == 's')
		return GetCos();
	else if(s[p] == 's' && s[p+1] == 'h')
		return GetSh();
	else if(s[p] == 'c' && s[p+1] == 'h')
		return GetCh();
	else if(s[p] == 'a' && s[p+1] == 't' && s[p+2] == 'g')
		return GetAtg();
	else
		return GetN();
	assert(0);
}

struct Node * GetLog()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(4, sizeof(struct Node));
	root->type = LOG;
	root->val[0] = 'l';
	root->val[1] = 'o';
	root->val[2] = 'g';
	root->val[3] = '\0';
	p += 3;
	if(s[p] != '[')
	{
		printf("Try to use a such kind of expression: 'log[NUMBER,EXPRESSION]'\n");
		abort();
	}
	p++;
	if(s[p] == 'e')
	{
		root->left = calloc(1, sizeof(struct Node));
		root->left->val = calloc(2, sizeof(struct Node));
		root->left->type = NUMBER;
		root->left->val[0] = 'e';
		root->left->val[1] = '\0';
		p++;
	}
	else root->left = GetN();
	if(s[p] != ',')
	{
		printf("Try to use a such kind of expression: 'log[NUMBER,EXPRESSION]'\n");
		abort();
	}
	p++;
	root->right = GetE();
	if(s[p] != ']')
	{
		printf("Try to use a such kind of expression: 'log[NUMBER,EXPRESSION]'\n");
		abort();
	}
	p++;
	return root;
}

struct Node * GetSin()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(4, sizeof(struct Node));
	root->type = SIN;
	root->val[0] = 's';
	root->val[1] = 'i';
	root->val[2] = 'n';
	root->val[3] = '\0';
	p += 3;
	if(s[p] != '(')
	{
		printf("Try to use a such kind of expression: 'sin(EXPRESSION)'\n");
		abort();
	}
	root->right = GetP();
	return root;
}

struct Node * GetCos()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(4, sizeof(struct Node));
	root->type = COS;
	root->val[0] = 'c';
	root->val[1] = 'o';
	root->val[2] = 's';
	root->val[3] = '\0';
	p += 3;
	if(s[p] != '(')
	{
		printf("Try to use a such kind of expression: 'cos(EXPRESSION)'\n");
		abort();
	}
	root->right = GetP();
	return root;
}

struct Node * GetSh()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(3, sizeof(struct Node));
	root->type = SH;
	root->val[0] = 's';
	root->val[1] = 'h';
	root->val[2] = '\0';
	p += 2;
	if(s[p] != '(')
	{
		printf("Try to use a such kind of expression: 'sh(EXPRESSION)'\n");
		abort();
	}
	root->right = GetP();
	return root;
}

struct Node * GetCh()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(3, sizeof(struct Node));
	root->type = CH;
	root->val[0] = 'c';
	root->val[1] = 'h';
	root->val[2] = '\0';
	p += 2;
	if(s[p] != '(')
	{
		printf("Try to use a such kind of expression: 'ch(EXPRESSION)'\n");
		abort();
	}
	root->right = GetP();
	return root;
}

struct Node * GetAtg()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(4, sizeof(struct Node));
	root->type = ATG;
	root->val[0] = 'a';
	root->val[1] = 't';
	root->val[2] = 'g';
	root->val[3] = '\0';
	p += 3;
	if(s[p] != '(')
	{
		printf("Try to use a such kind of expression: 'atg(EXPRESSION)'\n");
		abort();
	}
	root->right = GetP();
	return root;
}

struct Node * GetN()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(10, sizeof(struct Node));
	root->type = NUMBER;
	int counter = 0;
	while('0' <= s[p] && s[p] <= '9')
	{
		if(counter == 8)
		{
			printf("You have too big number in initial function\n");
			abort();
		}
		root->val[counter] = s[p];
		p++;
		counter++;
	}
	root->val[++counter] = '\0';
	if(counter == 1) 
	{
		user_helper();
		printf("There is not a number in GetN().\n");
		abort();
	}
	return root;
}

struct Node * GetVar()
{
	struct Node * root = calloc(1, sizeof(struct Node));
	root->val = calloc(2, sizeof(struct Node));
	root->type = VAR;
	root->val[0] = 'x';
	root->val[1] = '\0';
	p++;
	return root;
}

void user_helper()
{
	int counter = p;
	while(counter > 0)
	{
		printf(" ");
		counter--;
	}
	printf("^\n");
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
		default: 
			printf("Wrong type in Diff\n");
			exit(11);
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
		default: 
			printf("Wrong Type in CreateNode\n");
			exit(12);
	}
	return NULL;
}

struct Node * Optimize(struct Node * root)
{
	int * opt_register = calloc(1, sizeof(int));
	do
	{
		(*opt_register) = 0;
		root = Optimize_One_Zero(root, opt_register);
		root = Optimize_const(root, opt_register);
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
				root = tree_destroy(root);
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
					root = tree_destroy(root);
					(*opt_register)++;
					return u;
				}
				else if (root->right->val[0] == '0')
				{
					(*opt_register)++;
					root->right = tree_destroy(root->right);
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
					root = tree_destroy(root);
					(*opt_register)++;
					return u;
				}
				else if(root->left->val[0] == '0')
				{
					(*opt_register)++;
					root->left = tree_destroy(root->left);
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
					root = tree_destroy(root);
					(*opt_register)++;
					return u;
				}
				else
				{ 
					assert(root->right->val);
					if(root->right->val[0] == '0')
					{
						(*opt_register)++;
						root->right = tree_destroy(root->right);
						if(root->left) root->left = tree_destroy(root->left);
						struct Node * tree = calloc(1, sizeof(struct Node));
						tree->val = calloc(2, sizeof(char));
						tree->val[0] = '0';
						tree->val[1] = '\0';
						tree->type = NUMBER;
						root = tree_destroy(root);
						return tree;
					}
					else if(root->right->val[0] == '1' && root->right->val[1] == '\0')
					{
						(*opt_register)++;
						root->right = tree_destroy(root->right);
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
					root = tree_destroy(root);
					(*opt_register)++;
					return u;
				}
				else
				{
					if(root->left->val[0] == '0')
					{
						(*opt_register)++;
						root->left = tree_destroy(root->left);
						if(root->right) root->right = tree_destroy(root->right);
						struct Node * tree = calloc(1, sizeof(struct Node));
						tree->val = calloc(2, sizeof(char));
						tree->val[0] = '0';
						tree->val[1] = '\0';
						tree->type = NUMBER;
						root = tree_destroy(root);
						return tree;
					}
					else if(root->left->val[0] == '1' && root->left->val[1] == '\0')
					{
						(*opt_register)++;
						root->left = tree_destroy(root->left);
					}
					else
						root->left = Optimize_One_Zero(root->left, opt_register);
					}
			}
			return root;
		}
		default: 
			printf("Wrong Type in Optimize_One_Zero\n");
			exit(13);
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
					root = tree_destroy(root);
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
						root = tree_destroy(root);
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
						root = tree_destroy(root);
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
		default:
		printf("Wrong type in Optimize_const\n");
		exit(14);
	}
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

void Dot_print(struct Node * root, FILE * stream, int lab, int * lab_count)
{
	digraph(stream, lab_count);
	tree_png(root, stream, lab, lab_count);
	digraph(stream, lab_count);
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

void digraph(FILE * stream, int * lab_count)
{
	assert(lab_count);
	if(!(*lab_count)) {
		fprintf(stream, "digraph G{\n");
		fprintf(stream, "node [style=filled, color=azure3];\n");
	}
	else {
		fprintf(stream,"}\n");
		(*lab_count) = 0;
	}
}

void Tex(FILE * stream, const struct Node * root, int bull)
{
	if(bull)
	{
		fprintf(stream, "\\documentclass[a4, 12pt]{article}\n");
		fprintf(stream, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
		fprintf(stream, "\\usepackage[english]{babel}\n");
		fprintf(stream, "\\begin{document}\nYou wanted the derivative of this expression:\n");
	}
	fprintf(stream, "\\[");
	Tex_make(stream, root);
	if(bull)
	{
		fprintf(stream, "\\]\n I succeeded:\n");
	}
	if(!bull)
	{
		fprintf(stream, "\\]\n\\end{document}\n");
	}
}

void Tex_make(FILE * stream, const struct Node * root)
{
	assert(root);
	switch(root->type)
	{
		case NUMBER:
			if (root->val[0] == '-') fprintf(stream, "(%s)", root->val);
			else fprintf(stream, "%s", root->val);
			break;
		case VAR:
			fprintf(stream, "%s", root->val);
			break;
		case PLUS:
			fprintf(stream, "(");
			Tex_make(stream, root->left);
			fprintf(stream, "+");
			Tex_make(stream, root->right);
			fprintf(stream, ")");
			break;
		case MINUS:
			fprintf(stream, "(");
			Tex_make(stream, root->left);
			fprintf(stream, "-");
			Tex_make(stream, root->right);
			fprintf(stream, ")");
			break;
		case MULT:
			Tex_make(stream, root->left);
			fprintf(stream, "\\cdot{");
			Tex_make(stream, root->right);
			fprintf(stream, "}");
			break;
		case DIVIDE:
			fprintf(stream, "\\frac{");
			Tex_make(stream, root->left);
			fprintf(stream, "}{");
			Tex_make(stream, root->right);
			fprintf(stream, "}");
			break;
		case POW:
			assert(root->left);
			assert(root->right);
			_LEFT_CONDITION_ fprintf(stream, "{");
			else fprintf(stream, "(");
			Tex_make(stream, root->left);
			_LEFT_CONDITION_  fprintf(stream, "}^{");
			else fprintf(stream, ")^{");
			Tex_make(stream, root->right);
			fprintf(stream, "}");
			break;
		case LOG:
			assert(root->left);
			assert(root->right);
			fprintf(stream, "\\log_{");
			Tex_make(stream, root->left);
			_RIGHT_CONDITION_ fprintf(stream, "}{");
			else fprintf(stream, "}(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_  fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
		case SIN:
			assert(root->right);
			_RIGHT_CONDITION_  fprintf(stream, "\\sin{");
			else fprintf(stream, "\\sin(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_ fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
		case COS:
			assert(root->right);
			_RIGHT_CONDITION_  fprintf(stream, "\\cos{");
			else fprintf(stream, "\\cos(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_ fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
		case SH:
			assert(root->right);
			_RIGHT_CONDITION_  fprintf(stream, "\\sinh{");
			else fprintf(stream, "\\sinh(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_ fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
		case CH:
			assert(root->right);
			_RIGHT_CONDITION_  fprintf(stream, "\\cosh{");
			else fprintf(stream, "\\cosh(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_ fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
		case ATG:
			assert(root->right);
			_RIGHT_CONDITION_  fprintf(stream, "\\arctan{");
			else fprintf(stream, "\\arctan(");
			Tex_make(stream, root->right);
			_RIGHT_CONDITION_ fprintf(stream, "}");
			else fprintf(stream, ")");
			break;
	}
}

struct Node * tree_destroy(struct Node * root)
{
	if(root)
	{
		tree_destroy(root->left);
		tree_destroy(root->right);
		if(root->val) free(root->val);
		else
		{
			printf("There is a tree without tree->val\n");
			abort();
		}
		free(root);
	}
	return NULL;
}

