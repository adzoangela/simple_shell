#include "main.h"

/**
 * add_list_node - Adds a node.
 * @head: Address of the pointer.
 * @str: Text field of the node.
 * @num: Node index.
 * Return: Size of the list.
 */
list_struct *add_list_node(list_struct **head, const char *str, int num)
{
	list_struct *nh;

	if (!head)
		return (NULL);
	nh = malloc(sizeof(list_struct));
	if (!nh)
		return (NULL);
	mem_init((void *)nh, 0, sizeof(list_struct));
	nh->num = num;
	if (str)
	{
		nh->str = custom_strdup(str);
		if (!nh->str)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *head;
	*head = nh;
	return (nh);
}

/**
 * append_list_node - Adds a node.
 * @head: Address of the pointer.
 * @str: Text field.
 * @num: Node index.
 * Return: Size of the list.
 */
list_struct *append_list_node(list_struct **head, const char *str, int num)
{
	list_struct *nn, *node;

	if (!head)
		return (NULL);
	node = *head;
	nn = malloc(sizeof(list_struct));
	if (!nn)
		return (NULL);
	mem_init((void *)nn, 0, sizeof(list_struct));
	nn->num = num;
	if (str)
	{
		nn->str = custom_strdup(str);
		if (!nn->str)
		{
			free(nn);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nn;
	}
	else
		*head = nn;
	return (nn);
}

/**
 * print_text_list - Prints string  element of list_t
 * @n: Pointer
 * Return: Size
 */
size_t print_text_list(const list_struct *n)
{
	size_t count = 0;

	while (n)
	{
		custom_puts(n->str ? n->str : "(nil)");
		custom_puts("\n");
		n = n->next;
		count++;
	}
	return (count);
}

/**
 * delete_n_by_index - Deletes node.
 * @head: Address of the pointer.
 * @index: Index of the node.
 * Return: 1 or 0
 */
int delete_n_by_index(list_struct **head, unsigned int index)
{
	list_struct *node, *pn;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			pn->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		pn = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_text_list - Frees nodes.
 * @head_pointer: Address of the pointer.
 * Return: Nothing
 */
void free_text_list(list_struct **head_pointer)
{
	list_struct *node, *nn, *head;

	if (!head_pointer || !*head_pointer)
		return;
	head = *head_pointer;
	node = head;
	while (node)
	{
		nn = node->next;
		free(node->str);
		free(node);
		node = nn;
	}
	*head_pointer = NULL;
}
