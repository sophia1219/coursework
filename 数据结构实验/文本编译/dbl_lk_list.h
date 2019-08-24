#ifndef __CIRC_LK_LIST_H__
#define __CIRC_LK_LIST_H__

// �����
template <class ElemType>
struct DblNode 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	DblNode<ElemType> *back;	// ָ��ǰ����ָ����
	DblNode<ElemType> *next;	// ָ���̵�ָ����

// ���캯��:
	DblNode();						// �����ݵĹ��캯��
	DblNode(ElemType item, 
	DblNode<ElemType> *linkBack = NULL,
	DblNode<ElemType> *linkNext = NULL);// ��֪���������ָ�������ṹ
};


// ѭ��������
template <class ElemType>
class DblLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	DblNode<ElemType> *head;		// ͷ���ָ��

// ��������
	DblNode<ElemType> *GetElemPtr(int position) const;	// ����ָ��position������ָ��
	void Init();				// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	DblLinkList();				// �޲����Ĺ��캯��
	~DblLinkList();			// ��������
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*Visit)(ElemType &)) ;	// �������Ա�
	Status_code GetElem(int position, ElemType &e) const;// ��ָ��λ�õ�Ԫ��	
	Status_code SetElem(int position, const ElemType &e);// ����ָ��λ�õ�Ԫ��ֵ
	Status_code Delete(int position, ElemType &e);// ɾ��Ԫ��		
	Status_code Insert(int position, const ElemType &e); // ����Ԫ��
	DblLinkList(const DblLinkList<ElemType> &copy); // ���ƹ��캯��
	DblLinkList<ElemType> &operator =(const DblLinkList<ElemType> &copy); // ��ֵ�������
};


// ������ʵ�ֲ���

template<class ElemType>
DblNode<ElemType>::DblNode()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,
			DblNode<ElemType> *linkBack,
			DblNode<ElemType> *linkNext)
// �������������һ��������Ϊitem��ָ����ΪlinkBack��linkNext�Ľ��
{
   data = item;
   back = linkBack;
   next = linkNext;
}



// �������ʵ�ֲ���

template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ��position������ָ��
{
	if (position == 0)
	{	// ͷ�������Ϊ0
		return head;
	}

	DblNode<ElemType> *tmpPtr = head->next;// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int curPosition = 1;				// tmpPtr��ָ����λ�� 

	while (tmpPtr != head && curPosition < position)
	// ˳ָ�������ң�ֱ��tmpPtrָ���position�����
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != head && curPosition == position)
	{	// ���ҳɹ�
		return tmpPtr;	
	}
	else
	{	// ����ʧ��
		return NULL;	
	}

}

template <class ElemType>
void DblLinkList<ElemType>::Init()
// �����������ʼ�����Ա�
{
	head = new DblNode<ElemType>;		// ����ͷָ��
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList()
// �������������һ��������
{
	Init();
}

template <class ElemType>
DblLinkList<ElemType>::~DblLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int DblLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

template <class ElemType>
bool DblLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void DblLinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void DblLinkList<ElemType>::Traverse(void (*Visit)(ElemType &)) 
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*Visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
Status_code DblLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա�ĵ�position����ʱ����e������ֵ����������ENTRY_FOUND,
//			 ����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

template <class ElemType>
Status_code DblLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//			 position�ĺϷ�ֵΪ1��position��Length(),
//			 position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}

template <class ElemType>
Status_code DblLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ǰ��e������ֵ,
//			 position�ĺϷ�ֵΪ1��position��Length(),
//			 position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);			// ȡ��ָ���position������ָ��
		tmpPtr->back->next = tmpPtr->next;		// �޸����ҵ�ָ��
		tmpPtr->next->back = tmpPtr->back;		// �޸������ָ��
		e = tmpPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
		delete tmpPtr;							// �ͷű�ɾ���
		return SUCCESS;
	}
}

template <class ElemType>
Status_code DblLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//			 position�ĺϷ�ֵΪ1��position��Length()+1
//			 position�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return RANGE_ERROR; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		nextPtr = tmpPtr->next;				// nextPtrָ���position�����	
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);// �����½��
		tmpPtr->next = newPtr;				// �޸����ҵ�ָ��
		nextPtr->back = newPtr;				// �޸������ָ��
		return SUCCESS;
	}
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();		// copy�ĳ���
	ElemType e;
	Init();								// ��ʼ�����Ա�

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
DblLinkList<ElemType> &DblLinkList<ElemType>::operator =(const DblLinkList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		ElemType e;
		Clear();							// ��յ�ǰ���Ա�

		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// ��������Ԫ��
			copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif