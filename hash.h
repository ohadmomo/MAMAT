#ifndef _HASH_H_
#define _HASH_H_
#include <stdbool.h>
typedef enum {FAIL = 0, SUCCESS} Result;
typedef enum {SAME = 0, DIFFERENT} CompResult;

typedef struct _Hash *pHash;

typedef void* pElement;
typedef void* pKey;

typedef struct _Node *pNode;



typedef int (*HashFunc) (pKey key, int size);
typedef Result (*PrintFunc) (pElement element);
typedef CompResult (*CompareFunc) (pKey key1, pKey key2);
typedef pKey (*GetKeyFunc) (pElement element);
typedef void (*DestroyFunc)(pElement element);

pHash HashCreate(int arr_size, HashFunc HashF, PrintFunc PrintF, CompareFunc CompareF, GetKeyFunc GetKeyF, DestroyFunc DestroyF);
Result HashAdd(pHash ph, pElement p_elem);
pElement HashFind(pHash ph, pKey pk);
Result HashRemove(pHash ph, pKey pk);
Result HashPrint(pHash ph);
Result HashDestroy(pHash ph);

//----------------internal use---------------//
pNode CreateNode(pElement p);
pElement GetELementByKey(pHash ph, pNode head_of_list, pKey pk);
Result setNodeElement(pNode pn, pElement p_elem);
pElement GetNodeElemnt(pNode p);
pNode GetNextNode(pNode p);
pNode GetNodeByKey(pHash ph, pNode head_of_list, pKey pk);
Result PrintListElements(pHash ph, pNode head_of_list);
Result DestroyListAndElements(pHash ph, pNode head_of_list);
bool isKeyExist(pHash ph, pKey pk);





#endif
