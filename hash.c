#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

}
struct _Hash
{
	pNode *hash_table;///check
	int size_of_arr;

	int (*HashFunc) (pKey key, int size);
	Result(*PrintFunc) (pElement element);
	CompResult(*CompareFunc) (pKey key1, pKey key2);
	pKey(*GetKeyFunc) (pElement element);
	void (*DestroyFunc)(pElement element);
};

struct _Node
{
	pElement p_elem;
	pNode next_node;
};
//------------------------------------------------hash functions----------------------------------------------------//
pHash HashCreate(int arr_size , HashFunc HashF, PrintFunc PrintF, CompareFunc CompareF, GetKeyFunc GetKeyF, DestroyFunc DestroyF)
{
	if (arr_size <= 0 || HashF == NULL || PrintF == NULL || CompareF == NULL || GetKeyF == NULL || DestroyF == NULL) return NULL;
	pHash ph;
	if (ph = (pHash)malloc(sizeof(struct _Hash)) == NULL)
	{
		printf("Error Allocation Memory\n");
		return NULL;
	}
	pNode* hash_table;
	if (hash_table = (pNode*)malloc(sizeof(pNode) * arr_size) == NULL)
	{
		printf("Error Allocation Memory\n");
		free(ph);
		return NULL;
	}
	for (int i = 0; i < arr_size; i++)
	{
		hash_table[i] = NULL;
	}

	ph->hash_table = hash_table;
	ph->size_of_arr = arr_size;
	ph->HashFunc = HashF;
	ph->PrintFunc = PrintF;
	ph->CompareFunc = CompareF;
	ph->GetKeyFunc = GetKeyF;
	ph->DestroyFunc = DestroyF;
	
	return ph;
}

Result HashAdd(pHash ph, pElement p_elem)
{
	if (ph == NULL || p_elem == NULL) return FAIL;
	pKey pk = ph->GetKeyFunc(p_elem);
	int index = ph->HashFunc(pk, ph->size_of_arr);
	pNode pn;
	if ((pn = CreateNode(p_elem)) == NULL)return FAIL;
	pNode head_of_list = ph->hash_table[index];
	ph->hash_table[index] = pn;
	pn->next_node = head_of_list;
	return SUCCESS;
}

pElement HashFind(pHash ph, pKey pk)
{
	int index = ph->HashFunc(pk, ph->size_of_arr);
	pElement p_elem = GetELementByKey(ph, ph->hash_table[index], pk);
	return p_elem;
}

Result HashRemove(pHash ph, pKey pk)
{
	if (ph == NULL || pk == NULL)return FAIL;
	int index = ph->HashFunc(pk, ph->size_of_arr);//what if index < 0
	pNode pn = GetNodeByKey(ph, ph->hash_table[index], pk);
	if (pn == NULL)return FAIL;
	ph->DestroyFunc(pn->p_elem);
	free(pn);
	return SUCCESS;
}

Result HashPrint(pHash ph)
{
	if (ph == NULL)return FAIL;
	for (int i = 0; i < ph->size_of_arr; i++)
	{
		if (ph->hash_table[i] == NULL)continue;
		else if(PrintListElements(ph, ph->hash_table[i]) == FAIL)return FAIL;
	}
	return SUCCESS;
}

Result HashDestroy(pHash ph)
{
	if (ph == NULL)return FAIL;
	for (int i = 0; i < ph->size_of_arr; i++)
	{
		if (ph->hash_table[i] == NULL)continue;
		else if (DestroyListAndElements(ph, ph->hash_table[i]) == FAIL)return FAIL;
	}
	free(ph->hash_table);
	return SUCCESS;
}

//------------------------------------------------internal use----------------------------------------------------//
pNode CreateNode(pElement p)
{
	if (p == NULL)return NULL;
	pNode pn;
	if (pn = (pNode)malloc(sizeof(struct _Node)) == NULL)
	{
		printf("Error Allocation Memory\n");
		return NULL;
	}
	pn->p_elem = p;
	pn->next_node = NULL;
	return pn;
}
Result setNodeElement(pNode pn, pElement p_elem)
{
	if (p_elem == NULL || pn == NULL)return FAIL;
	pn->p_elem = p_elem;
}
pElement GetNodeElemnt(pNode p)
{
	if (p == NULL)return NULL;
	return p->p_elem;
}
pNode GetNextNode(pNode p)
{
	if (p == NULL)return NULL;
	return p->next_node;
}
pElement GetELementByKey(pHash ph, pNode head_of_list, pKey pk)
{
	if (ph == NULL || head_of_list == NULL || pk == NULL)return NULL;
	pNode pn = head_of_list;
	while (pn)
	{
		if (ph->CompareFunc(ph->GetKeyFunc(pn->p_elem), pk) == SAME)return (pn->p_elem);
		else pn = pn->next_node;
	}
	return NULL; // didnt find the key
}

pNode GetNodeByKey(pHash ph, pNode head_of_list, pKey pk)
{
	if (ph == NULL || head_of_list == NULL || pk == NULL)return NULL;
	pNode pn = head_of_list;
	while (pn)
	{
		if (ph->CompareFunc(ph->GetKeyFunc(pn->p_elem), pk) == SAME)return (pn);
		else pn = pn->next_node;
	}
	return NULL; // didnt find the key
}

Result PrintListElements(pHash ph, pNode head_of_list)
{
	if (ph == NULL || head_of_list == NULL)return FAIL;
	pNode pn = head_of_list;
	while (pn)
	{
		ph->PrintFunc(pn->p_elem);
		pn = pn->next_node;
	}
	return SUCCESS;
}

Result DestroyListAndElements(pHash ph, pNode head_of_list)
{
	if (ph == NULL || head_of_list == NULL)return FAIL;
	pNode pn = head_of_list;
	pNode tmp;
	while (pn)
	{
		ph->DestroyFunc(pn->p_elem);
		tmp = pn->next_node;
		free(pn);
		pn = tmp;
	}
	return SUCCESS;
}