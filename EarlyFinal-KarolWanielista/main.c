#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

//#pragma warning (ignore : 2220)

unsigned int count_bits(unsigned int a);

typedef struct bstnode {
	int integer;
	struct bstnode* left;
	struct bstnode* right;
} node;

node* stree(node* r, int val)
{
	if (!r)
	{
		r = (node*)malloc(sizeof(node));
		if (!r)
		{
			printf("No memory\n");
			exit(0);
		}
		r->left = NULL;
		r->right = NULL;
		r->integer = val;

		return r;
	}
	if (count_bits(val) < count_bits(r->integer))
		r->left = stree(r->left, val);
	else
		r->right = stree(r->right, val);
	return r;
}

node* clear_tree(node* root)
{
	if (!root)
		return NULL;
	clear_tree(root->left);
	clear_tree(root->right);
	free(root);
	return NULL;
}

unsigned int count_bits(unsigned int a) {
	unsigned int c = 0;
	for (unsigned int i = sizeof(int) * 8; i > 0; i--)
	{
		if (a < pow(2, i - 1)) {}
		else
		{
			c++;
			a -= (int)pow(2, i - 1);
		}
	}
	return c;
}

void print_bits(unsigned int a) {
	for (unsigned int i = sizeof(int)*CHAR_BIT; i>0; i--)
	{
		if (a < pow(2, i - 1))
			printf("0");
		else
		{
			printf("1");
			a -= (int)pow(2, i - 1);
		}
	}
	printf("\n");
}

int print_tree(node* root) {
	int c = 0;
	if (root->right!=NULL)
	{
		c+=print_tree(root->right);
	}
	printf("%d - %d bits\n", root->integer, count_bits(root->integer)); c++;
	if (root->left!=NULL)
	{
		c += print_tree(root->left);
	}
	return c;
}

void print_va(int n, ...) {
	va_list p_args;
	unsigned int z = 0;
	va_start(p_args, n);
	for (int  i = 0; i < n; i++)
	{
		z = va_arg(p_args, unsigned int);
		print_bits(z);
		printf(" = %d\n",z);
	}
}

int main(int argc, char** argv)
{	
	unsigned value;
	node* root = (node*)malloc(sizeof(node));

	//printf("%d", atoi("ccc"));



	puts("Part 1\n");
	value = 123456;
	print_bits(value);
	printf(" has %d bits set.\n", count_bits(value));
	value = 3;
	print_bits(value);
	printf(" has %d bits set.\n", count_bits(value));


	puts("\nPart 2");

	if (argc <= 1)
	{
		printf("invalid no. of console args");
		return -1;
	}

	root->integer = atoi(argv[1]);
	root->left = NULL;
	root->right = NULL;
	printf("inserting %d (has %d bits set)\n", atoi(argv[1]), count_bits(atoi(argv[1])));
	for (int i = 2; i < argc; i++)
	{
		printf("inserting %d (has %d bits set)\n", atoi(argv[i]), count_bits(atoi(argv[i])));
		stree(root, atoi(argv[i]));
	}

	//printf("%d", root->integer);

	printf("\nPart 3\nPrinting tree:\n");
	
	print_tree(root);
	
	clear_tree(root);

	printf("\nPart 4\n");
	
	print_va(5,'K','a','r','o','l');
	
	printf("\nBye\n");

	return 0;
}
