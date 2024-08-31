#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (*head)
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - Deletes the node at a given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node = NULL;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	node = *head;

	if (index == 0)
	{
		*head = node->next;
		free(node->str);
		free(node);
		return (1);
	}

	while (node && i < index)
	{
		prev_node = node;
		node = node->next;
		i++;
	}

	if (node)
	{
		prev_node->next = node->next;
		free(node->str);
		free(node);
		return (1);
	}

	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node;

	if (!head_ptr || !*head_ptr)
		return;

	node = *head_ptr;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
